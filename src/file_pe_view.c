/*
    libbparse - Binary file parser library
    Copyright (C) 2010  m_101

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <ctype.h>

#include "file_pe_defs.h"
#include "file_pe_internal.h"
#include "file_pe.h"

// check str printability
int str_is_printable (char *str, size_t szStr)
{
    if (!str || !szStr)
        return 0;
    if (*str == '\0')
        return 0;

    while (szStr && *str)
    {
        if (!isprint (*str))
            return 0;
        str++;
        szStr--;
    }

    return 1;
}

//
int show_infos (char *filename) {
    FILE *fp;
    IMAGE_NT_HEADERS *ntHeaders;
    PE_FILE *pefile;

    //
    fp = fopen(filename, "r");
    if (!fp)
        return -1;

    if (PeCheck(fp) == 0) {
        fprintf(stderr, "Error: Not a valid PE file\n");
        fclose (fp);
        exit(1);
    }

    pefile = PeInit(fp);
	ntHeaders = PeGetNtHeader (pefile);

	printf ("== INFOS\n");
	printf("Image base         : 0x%08x\n", ntHeaders->OptionalHeader.ImageBase);
	printf("Number of sections : %u\n", ntHeaders->FileHeader.NumberOfSections);
	printf ("== INFOS END\n\n");

    PeDelete(&pefile);

    fclose(fp);

	return 0;
}

// show all section header name and VA range
int show_section_headers (char *filename)
{
    FILE *fp;
    size_t i;
    unsigned long imageBase, VA;
    IMAGE_NT_HEADERS *ntHeaders;
    IMAGE_SECTION_HEADER *sectionHeaderTable;
    PE_FILE *pefile;

    //
    fp = fopen(filename, "r");
    if (!fp)
        return -1;

    if (PeCheck(fp) == 0) {
        fprintf(stderr, "Error: Not a valid PE file\n");
        fclose (fp);
        exit(1);
    }

    pefile = PeInit(fp);

    ntHeaders = PeGetNtHeader (pefile);
    sectionHeaderTable = PeGetSectionHeaderTable (pefile);

    imageBase = ntHeaders->OptionalHeader.ImageBase;

    printf ("== SECTIONS\n");
    for (i = 0; i < ntHeaders->FileHeader.NumberOfSections; i++)
    {
        VA = imageBase + sectionHeaderTable[i].VirtualAddress;
        printf ("%s\t: 0x%08lx-0x%08lx\n", sectionHeaderTable[i].Name, VA, VA + sectionHeaderTable[i].SizeOfRawData);
    }
	printf ("== SECTIONS END\n\n");

    PeDelete(&pefile);
    fclose(fp);

    return 0;
}

// show all named imported functions
int show_libraries (char *filename)
{
    FILE *fp;
    size_t idxLibrary;
    struct list_imports *libraries;
    PE_FILE *pefile;

    fp = fopen(filename, "r");
    if (!fp)
        return -1;

    if (PeCheck(fp) == 0) {
        fprintf(stderr, "Error: Not a valid PE file\n");
        fclose (fp);
        exit(1);
    }

    pefile = PeInit (fp);
    libraries = PeReadDataDirectoryImports (pefile, fp);
	if (libraries == -1u || libraries == 0)
		return -1;

    // show imports
    printf ("== LIBRARIES\n");
	for (idxLibrary = 0; idxLibrary < libraries->nLibraries; idxLibrary++) {
		printf("%s\n", libraries->libraries[idxLibrary]);
	}
	printf ("== LIBRARIES END\n\n");

    fclose(fp);

    return 0;
}

// show all named imported functions
int show_imports (char *filename)
{
    FILE *fp;
    size_t idxLibrary, idxImport;
    struct list_imports *libraries;
    PE_FILE *pefile;

    fp = fopen(filename, "r");
    if (!fp)
        return -1;

    if (PeCheck(fp) == 0) {
        fprintf(stderr, "Error: Not a valid PE file\n");
        fclose (fp);
        exit(1);
    }

    pefile = PeInit (fp);
    libraries = PeReadDataDirectoryImports (pefile, fp);
	if (libraries == -1u || libraries == 0)
		return -1;

    // show imports
    printf ("== IMPORTS");
	for (idxLibrary = 0; idxLibrary < libraries->nLibraries; idxLibrary++) {
		printf("\nLibrary : %s\n", libraries->libraries[idxLibrary]);		
		printf("Number of functions : %lu\n", libraries->nFunctions[idxLibrary]);
        printf("Functions :\n");
		for (idxImport = 0; idxImport < libraries->nFunctions[idxLibrary]; idxImport++) {
			if (libraries->functions[idxImport]) {
				printf("    %5u - %s\n", libraries->hints[idxLibrary][idxImport],
				       			   libraries->functions[idxLibrary][idxImport]);
			}
		}
	}
	printf ("== IMPORTS END\n\n");

    fclose(fp);

    return 0;
}


int show_exports (char *filename)
{
    FILE *fp;
	size_t idxExport, ordinal;
    struct list_exports *exports;
    PE_FILE *pefile;

    if (!filename)
        return -1;

    fp = fopen(filename, "r");
    if (!fp)
        return -1;
    
    if (PeCheck(fp) == 0) {
        fprintf(stderr, "Error: Not a valid PE file\n");
        fclose (fp);
        exit(1);
    }

    pefile = PeInit (fp);
    exports = PeReadDataDirectoryExports (pefile, fp);
    if (!exports) {
        fprintf(stderr, "Failed: Reading exports\n");
        return 1;
    }

    if (exports == -1u) {
        fprintf(stderr, "No export section\n");
        return 1;
    }

    if (exports->nNames <= 0) {
        printf("There isn't any named exports\n");
        printf("but there are %lu numbered exports\n", exports->nFunctions);
        return 0;
    }
	
	printf ("== EXPORTS\n");
	for (idxExport = 0; idxExport < exports->nNames; idxExport++) {
		ordinal = exports->ordinals[idxExport];
        if (idxExport < exports->nNames)
    		printf ("%5u - 0x%x : %s\n", ordinal, exports->functions[ordinal], exports->names[idxExport]);
        else
    		printf ("%5u - 0x%x\n", ordinal, exports->functions[ordinal]);
	}
	printf ("We readed %lu named exports\n", idxExport);
	printf ("== EXPORTS END\n\n");

    fclose(fp);
	
    return 0;
}
