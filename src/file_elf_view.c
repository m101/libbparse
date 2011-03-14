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

#include <elf.h>

#include "file_elf.h"

char* GetSectionTypeName (int type) {
	char *names[] = {
		"SHT_NULL",
		"SHT_PROGBITS",
		"SHT_SYMTAB",
		"SHT_STRTAB",
		"SHT_RELA",
		"SHT_HASH",
		"SHT_DYNAMIC",
		"SHT_NOTE",
		"SHT_NOBITS",
		"SHT_REL",
		"SHT_SHLIB",
		"SHT_DYNSIM"
	};

	if (type < 12)
		return names[type];

	switch (type) {
		case SHT_LOPROC:
			return "SHT_LOPROC";
			break;
		case SHT_HIPROC:
			return "SHT_HIPROC";
			break;
		case SHT_LOUSER:
			return "SHT_LOUSER";
			break;
		case SHT_HIUSER:
			return "SHT_HIUSER";
			break;
	}

	// haven't found a suitable type
	return NULL;
}

void elf_header_print_info (Elf32_Ehdr *elf_header)
{
    if (!elf_header)
        fprintf(stderr, "Error: No elf header\n");
    else
    {
        printf("[+] Elf header size      : %d\n", elf_header->e_ehsize);
		printf("[+] Elf object type      : %x\n", elf_header->e_type);
		printf("[+] Machine              : %x\n", elf_header->e_machine);
		printf("[+] Elf version          : %x\n", elf_header->e_version);
		printf("[+] Program entry point  : 0x%08x\n", elf_header->e_entry);
        printf("[+] Program header count : %d\n", elf_header->e_phnum);
        printf("[+] Program header size  : %d\n", elf_header->e_phentsize);
        printf("[+] Section header count : %d\n", elf_header->e_shnum);
        printf("[+] Section header size  : %d\n", elf_header->e_shentsize);
        printf("[+] Section offset       : %d\n", elf_header->e_shoff);
        putchar('\n');
    }
}

void elf_header_print_section_info (char *binaryName)
{
    struct filemap_t *fmap;
    size_t idx, offName;
    char **sectionNamesTable;
    // section names length
    size_t maxSectionNameLength = 0, sectionNameLength;
    // number of spaces to print
    size_t numSpaces, iSpace;
	FILE *fp;
	Elf32_Ehdr *elfHeader;
	Elf32_Shdr *sectionsHeadersTable;
    Elf32_Shdr *sectionNamesTableHeader;

	if (!binaryName)
		return;
	
	//
	fp = fopen(binaryName, "r");
	if (!fp)
		return;

    // create filemap
	fmap = filemap_create (fp);
	if (!fmap)
		return;

	// get elf header
	elfHeader = ElfGetHeader (fp);
	if(!elfHeader)
		return;
		
	// get sections headers
	sectionsHeadersTable = ElfGetSectionHeadersTable (fp);
	if (!sectionsHeadersTable) {
	    fprintf(stderr, "Error: elf_section_names_print: No section headers table\n");
	    return;
	}
	
    // get section names table
	sectionNamesTable = ElfGetSectionNamesTable (fp);
    if (!sectionNamesTable) {
        fprintf(stderr, "Error: elf_section_names_print: No section names table\n");
        return;
    }

    // get section names table start
    sectionNamesTableHeader = &(ElfGetSectionHeadersTable (fp)[elfHeader->e_shstrndx]);

    // we search longest section name length
    for (idx = 0; idx < elfHeader->e_shnum; idx++) {
	    offName = sectionsHeadersTable[idx].sh_name;

        sectionNameLength = strlen(sectionNamesTable[idx]);
        if (sectionNameLength > maxSectionNameLength)
            maxSectionNameLength = sectionNameLength;
    }

    // print section names
    printf("== SECTIONS\n");
    printf("   Idx\tName");
    // print spaces
    for (iSpace = 0; iSpace < maxSectionNameLength; iSpace++)
        putchar(' ');
    printf("\tSize\t      VMA\tLMA  File Off     Algn\n");
	for (idx = 0; idx < elfHeader->e_shnum; idx++) {
        // index of name in section names table, offName = offset from beginning of table
	    offName = sectionsHeadersTable[idx].sh_name;
        //
        //printf("%6u\t%s", idx, sectionNamesTable[idx]);
        printf("%6u\t%s", idx, fmap->map + sectionNamesTableHeader->sh_offset + offName);
        // get number of spaces to print
        numSpaces = maxSectionNameLength - strlen(fmap->map + sectionNamesTableHeader->sh_offset + offName);
        // print spaces
        for (iSpace = 0; iSpace < numSpaces; iSpace++)
            putchar(' ');
        printf("\t%u\t   0x%08x\n", sectionsHeadersTable[idx].sh_size, sectionsHeadersTable[idx].sh_addr);
    }
    printf("== SECTIONS END\n\n");

	free(sectionNamesTable);
}
