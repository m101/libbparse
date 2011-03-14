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

#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include <stdint.h>

#include "file_pe.h"
#include "file_pe_internal.h"
#include "filemap.h"
#include "raw_data.h"

// create a new and empty PE_FILE struct :)
PE_FILE* PeNew(void) {
    PE_FILE *pefile;

    pefile = calloc(1, sizeof(*pefile));

    return pefile;
}

// destroy a pefile file structure
void PeDelete(PE_FILE **pefile) {
    if (!pefile)
        return;

    filemap_destroy(&((*pefile)->fmap));
    free(*pefile);
    *pefile = NULL;
}

// init pefile : private
PE_FILE* PeInit (FILE *fp) {
    PE_FILE *pefile;

    // check pointer validity
    if (!fp)
        return NULL;

	// allocate pe file object
    pefile = PeNew();
    if (!pefile)
        return NULL;

	pefile->fp = fp;
	pefile->fmap = filemap_create (fp);
	pefile->directory_data = calloc(IMAGE_NUMBEROF_DIRECTORY_ENTRIES, sizeof(void *));
	pefile->directory_data[IMAGE_DIRECTORY_ENTRY_EXPORT] = calloc(1, sizeof(struct list_exports));
	pefile->directory_data[IMAGE_DIRECTORY_ENTRY_IMPORT] = calloc(1, sizeof(struct list_imports));

    // pefile
    return pefile;
}

// parse PE file
PE_FILE* PeLoad (char *filename) {
    long success = -1;
	FILE *fp;
    PE_FILE *pefile = NULL;
	IMAGE_NT_HEADERS *ntHeaders;
    IMAGE_SECTION_HEADER *sectionHeaderTable;

	if (!filename) {
        fprintf(stderr, "PeLoad(): Bad filename\n");
		return NULL;
    }

	// open file
	fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "PeLoad(): Failed opening '%s'\n", filename);
        return NULL;
    }

	// check file type
	if (PeCheck(fp) == 0) {
        fprintf(stderr, "PeLoad(): Not a PE file\n");
		goto peload_cleanup;
    }

	// pefile init
    pefile = PeInit (fp);
	if (!pefile) {
        fprintf(stderr, "PeLoad(): Init failed\n");
		goto peload_cleanup;
    }
    pefile->filename = strdup(filename);
    pefile->szFilename = strlen(pefile->filename);

	// get nt headers
	ntHeaders = PeGetNtHeader (pefile);
	if (!ntHeaders) {
        fprintf(stderr, "PeLoad(): Failed reading NtHeaders\n");
		goto peload_cleanup;
    }

    // get section headers
    sectionHeaderTable = PeGetSectionHeaderTable (pefile);
	if (!sectionHeaderTable) {
        fprintf(stderr, "PeLoad(): Failed getting Section Headers Table\n");
		goto peload_cleanup;
    }

    // if we have an optionnal header
    // then we continue parsing the PE file
    if (ntHeaders->FileHeader.SizeOfOptionalHeader != 0)
        success = PeReadDataDirectories (pefile, 0);

peload_cleanup:
    fclose(fp);
    if (success > 0 || pefile)
        return pefile;
    else
        return NULL;
}

// free loaded pe file
void PeUnload(PE_FILE **pefile) {
    size_t idxDirectoryEntry;

    if (!pefile)
        return;
    if (!*pefile)
        return;

    if ((*pefile)->directory_data) {
        for (idxDirectoryEntry = 0; idxDirectoryEntry < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; idxDirectoryEntry++) {
            if (idxDirectoryEntry == IMAGE_DIRECTORY_ENTRY_IMPORT)
                list_imports_delete (&((*pefile)->imports));
            else if (idxDirectoryEntry == IMAGE_DIRECTORY_ENTRY_EXPORT)
                list_exports_delete (&((*pefile)->exports));
            if (idxDirectoryEntry != IMAGE_DIRECTORY_ENTRY_IMPORT
                    && idxDirectoryEntry != IMAGE_DIRECTORY_ENTRY_EXPORT)
                free((*pefile)->directory_data[idxDirectoryEntry]);
        }
        free((*pefile)->directory_data);
    }

    filemap_destroy(&((*pefile)->fmap));
    free((*pefile)->filename);
    free(*pefile);

    *pefile = NULL;
}

// convert a relative virtual address into a virtual address
uint64_t RvaToVa (PE_FILE *pefile, uint64_t dwRVA) {
    IMAGE_NT_HEADERS *ntHeaders;

    // invalid file pointer
    if (!pefile)
        return -1;

    // get nt header
    ntHeaders = PeGetNtHeader (pefile);
    if (!ntHeaders)
        return -1;

    return ntHeaders->OptionalHeader.ImageBase + dwRVA;
}

// convert a RVA into a file offset
uint64_t RvaToOffset (PE_FILE *pefile, uint64_t dwRVA) {
    size_t i;
    IMAGE_NT_HEADERS *ntHeaders;
    IMAGE_SECTION_HEADER *sectionHeaders;

    // invalid file pointer
    if (!pefile)
        return -1;

    // get nt header
    ntHeaders = PeGetNtHeader (pefile);
    if (!ntHeaders)
        return -1;

    // get section header table
    sectionHeaders = PeGetSectionHeaderTable (pefile);
    if (!sectionHeaders)
        return -1;

    // we search for section appartenance
    for (i = 0; i < ntHeaders->FileHeader.NumberOfSections; i++) {
        // if rva is in current section
        // then we convert it to file offset
        if ( dwRVA >= sectionHeaders[i].VirtualAddress
                && (dwRVA < sectionHeaders[i].VirtualAddress
                    + sectionHeaders[i].Misc.VirtualSize) ) {
            // we get the offset from the beginning of the section
            dwRVA -= sectionHeaders[i].VirtualAddress;
            // we get the file offset
            dwRVA += sectionHeaders[i].PointerToRawData;
            return dwRVA;
        }
    }

    // didn't find the specified rva
    return -1;
}

// convert a file offset into a RVA
uint64_t OffsetToRva (PE_FILE *pefile, uint64_t dwOffset) {
    size_t i;
    uint64_t dwRVA;
    IMAGE_NT_HEADERS *ntHeaders;
    IMAGE_SECTION_HEADER *sectionHeaders;

    // incorrect file pointer
    if (!pefile)
        return -1;

    // get nt header
    ntHeaders = PeGetNtHeader (pefile);
    if (!ntHeaders)
        return -1;

    // get section header table
    sectionHeaders = PeGetSectionHeaderTable (pefile);
    if (!sectionHeaders)
        return -1;

    dwRVA = 0;
    // we search for section appartenance
    for (i = 0; i < ntHeaders->FileHeader.NumberOfSections; i++) {
        // if rva is in current section = good rva
        // then we return it
        if ( dwOffset >= sectionHeaders[i].PointerToRawData
                && dwOffset < sectionHeaders[i].PointerToRawData
                + sectionHeaders[i].SizeOfRawData ) {
            // start of section in VM space
            dwRVA += sectionHeaders[i].VirtualAddress;
            // start of section in file
            dwRVA += sectionHeaders[i].PointerToRawData;
            // offset to convert to RVA
            dwRVA += dwOffset;
            // converted offset
            return dwRVA;
        }
    }

    // didn't find a corresponding rva to the specified offset
    return -1;
}

// check if PE FILE
int PeCheck (FILE *fp) {
    PE_FILE *pefile;
    int check;

    if (!fp)
        return 0;

    pefile = PeInit(fp);
    check = PeGetDosHeader (pefile) && PeGetNtHeader (pefile);
    PeUnload(&pefile);

    return check;
}

// get dos header
PIMAGE_DOS_HEADER PeGetDosHeader (PE_FILE *pefile) {
    PIMAGE_DOS_HEADER dosHeader;

    if (!pefile)
        return NULL;

    // check pointer validity
    if (!pefile->fp)
        return NULL;

    // create filemap
    if (!pefile->fmap)
        pefile->fmap = filemap_create (pefile->fp);
    if (!pefile->fmap)
        return NULL;

    // alloc memory
    dosHeader = pefile->fmap->map;
    if (!dosHeader)
        return NULL;

    // check DOS file magic number
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
        return NULL;

    return dosHeader;
}

// get nt header
PIMAGE_NT_HEADERS PeGetNtHeader (PE_FILE *pefile) {
    PIMAGE_DOS_HEADER dosHeader;
    PIMAGE_NT_HEADERS ntHeader;

    if (!pefile)
        return NULL;

    // check validity
    if (!pefile->fp)
        return NULL;

    // create filemap
    if (!pefile->fmap)
        pefile->fmap = filemap_create (pefile->fp);
    if (!pefile->fmap)
        return NULL;

    // get dos header
    dosHeader = PeGetDosHeader (pefile);
    if (!dosHeader)
        return NULL;

    // alloc memory
    ntHeader = pefile->fmap->map + dosHeader->e_lfanew;
    if (!ntHeader)
        return NULL;

    // check NT file magic number
    if (ntHeader->Signature != IMAGE_NT_SIGNATURE)
        return NULL;

    return ntHeader;
}

// read first section header
PIMAGE_SECTION_HEADER PeGetSectionHeaderFirst (PE_FILE *pefile) {
    uint64_t offset;
    PIMAGE_DOS_HEADER dosHeader;
    PIMAGE_NT_HEADERS ntHeader;

    if (!pefile)
        return NULL;

    // check pointers
    if (!pefile->fp)
        return NULL;

    // get DOS and NT headers
    dosHeader = PeGetDosHeader (pefile);
    ntHeader = PeGetNtHeader (pefile);
    // check validity
    if (!dosHeader || !ntHeader)
        return NULL;

    if (!pefile->fmap)
        pefile->fmap = filemap_create (pefile->fp);
    if (!pefile->fmap)
        return NULL;

    // read section if not null
    // first section header file offset
    offset =  dosHeader->e_lfanew
        + sizeof (ntHeader->FileHeader) + 4 // jump signature
        + ntHeader->FileHeader.SizeOfOptionalHeader;

    // first section header address :)
    return pefile->fmap->map + offset;
}

// read last section header
PIMAGE_SECTION_HEADER PeGetSectionHeaderLast (PE_FILE *pefile) {
    PIMAGE_NT_HEADERS ntHeader;
    PIMAGE_SECTION_HEADER pLastSectionHeader;

    if (!pefile)
        return NULL;

    // get first offset
    pLastSectionHeader = PeGetSectionHeaderFirst (pefile);
    if (!pLastSectionHeader)
        return NULL;

    // get nt header
    ntHeader = PeGetNtHeader (pefile);
    if (!ntHeader)
        return NULL;

    // we shift n-1 so it points to last section header
    pLastSectionHeader += (ntHeader->FileHeader.NumberOfSections - 1) * sizeof(IMAGE_SECTION_HEADER);

    return pLastSectionHeader;
}

/*! @brief  Get section header table
*/
    IMAGE_SECTION_HEADER* PeGetSectionHeaderTable (PE_FILE *pefile) {
        if (!pefile)
            return NULL;
        return PeGetSectionHeaderFirst (pefile);
    }

// add a section header to file
char* PeAddSection (PE_FILE *pefile,
        char *name, size_t namelen,
        unsigned char *data, size_t szData) {
    IMAGE_NT_HEADERS *ntHeader;
    IMAGE_SECTION_HEADER *sectionHeaderLast;

    if (!pefile || !name || !namelen || !data || !szData)
        return FALSE;

    ntHeader = PeGetNtHeader (pefile->fp);
    sectionHeaderLast = PeGetSectionHeaderFirst (pefile->fp)
        + ntHeader->FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER);

    return sectionHeaderLast;
}

// read data directories
// return 0 for success
// return a positive value corresponding to faulty data directory parsing
// return negative value for system errors
uint64_t PeReadDataDirectories (PE_FILE *pefile, uint64_t data) {
    size_t i;
    uint64_t success = 0;
    // function call table
    uint64_t (*read_data_directory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES])() = { NULL };

    // bad file pointer
    if (!pefile)
        return -1;

    // we fill table with generic handler for unhandled data directories
    for (i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
        read_data_directory[i] = PeReadDataDirectoryGeneric;

    // fill table with implemented handlers
    read_data_directory[IMAGE_DIRECTORY_ENTRY_EXPORT] = PeReadDataDirectoryExports;
    read_data_directory[IMAGE_DIRECTORY_ENTRY_IMPORT] = PeReadDataDirectoryImports;
    read_data_directory[IMAGE_DIRECTORY_ENTRY_RESOURCE] = PeReadDataDirectoryResources;

    // we go for all data directories
    // we'll use a function call table to avoid an if forest
    for (i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++) {
        success = read_data_directory[i] (pefile, data);
        if (success == -1)
            return i;
    }

    return 0;
}

// read exports directory
uint64_t PeReadDataDirectoryExports (PE_FILE *pefile, uint64_t data) {
    size_t nbExports;
    struct list_exports *exports;
    uint64_t offsetExportDirectory;
    WORD *functionOrdinal;
    uint64_t *rvaAddressOfNames, *rvaAddressOfFunctions;
    unsigned char *functionName;
    IMAGE_NT_HEADERS *ntHeaders;
    IMAGE_EXPORT_DIRECTORY *exportDirectory;

    // bad file pointer
    if (!pefile)
        return -1;

    // get nt header
    ntHeaders = PeGetNtHeader (pefile);
    if (!ntHeaders)
        return -1;

    // compute import file offset
    offsetExportDirectory = RvaToOffset (pefile, ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
    if (offsetExportDirectory == -1)
        return -1;

    // file map
    if (!pefile->fmap)
        pefile->fmap = filemap_create (pefile->fp);
    if (!pefile->fmap)
        return -1;

    // get export directory
    exportDirectory = pefile->fmap->map + offsetExportDirectory;

    // get exports
    exports = pefile->directory_data[IMAGE_DIRECTORY_ENTRY_EXPORT];
    exports->nNames = exportDirectory->NumberOfNames;
    exports->names = calloc(exportDirectory->NumberOfNames, sizeof(char *));
    exports->nFunctions = exportDirectory->NumberOfFunctions;
    exports->functions = calloc(exportDirectory->NumberOfFunctions, sizeof(uint64_t ));
    exports->ordinals = calloc(exportDirectory->NumberOfFunctions, sizeof(size_t));

    for (nbExports = 0; nbExports < exportDirectory->NumberOfNames; nbExports++) {
        // get function name
        rvaAddressOfNames = pefile->fmap->map + RvaToOffset (pefile, exportDirectory->AddressOfNames + (sizeof(uint64_t) * nbExports));
        functionName = pefile->fmap->map + RvaToOffset (pefile, *rvaAddressOfNames);

        // get corresponding ordinal
        functionOrdinal = pefile->fmap->map + RvaToOffset (pefile, exportDirectory->AddressOfNameOrdinals + (sizeof(WORD) * nbExports));

        // get function name (if it has one)
        if ( (*functionOrdinal) < exportDirectory->NumberOfNames) {
            exports->names[nbExports] = functionName;
        }

        // get function RVA
        rvaAddressOfFunctions = pefile->fmap->map + RvaToOffset (pefile, exportDirectory->AddressOfFunctions + (sizeof(uint64_t) * (*functionOrdinal)));

        // address + ordinal :)
        exports->functions[*functionOrdinal] = RvaToVa (pefile, *rvaAddressOfFunctions);
        exports->ordinals[nbExports] = *functionOrdinal;
    }

    pefile->exports = exports;

    return exports;
}

struct list_imports* list_imports_new (PE_FILE *pefile) {
    size_t nFunctions;
    struct list_imports *imports;

    imports = calloc(1, sizeof(*imports));
    if (!imports)
        return NULL;

    nFunctions = PeGetDataDirectoryImportThunksCount (pefile, 0);

    return imports;
}

struct list_imports* list_imports_delete (struct list_imports **imports) {
    size_t idxLibraries;

    if (!imports)
        return NULL;

    if (!*imports)
        return NULL;

    for (idxLibraries = 0; idxLibraries < (*imports)->nLibraries; idxLibraries++) {
        //free((*imports)->hints[idxLibraries]);
        //free((*imports)->functions[idxLibraries]);
    }
    free((*imports)->nFunctions);
    free((*imports)->libraries);
    free((*imports)->hints);
    free((*imports)->functions);

    free(*imports);
    *imports = NULL;
}

    struct list_exports* list_exports_delete (struct list_exports **exports) {
        if (!exports)
            return NULL;

        if (!*exports)
            return NULL;

        free((*exports)->names);
        free((*exports)->functions);
        free((*exports)->ordinals);

        free(*exports);
        *exports = NULL;
    }


// count number of imported libraries
size_t PeGetDataDirectoryImportsCount (PE_FILE *pefile) {
    size_t nbImports;
    uint64_t offsetImports;
    IMAGE_NT_HEADERS *ntHeaders;
    IMAGE_IMPORT_DESCRIPTOR importTableTerminator = { {0} };
    IMAGE_IMPORT_DESCRIPTOR *import;

    // check file pointer
    if (!pefile)
        return -1;

    // get nt headers
    ntHeaders = PeGetNtHeader (pefile);
    if (!ntHeaders)
        return -1;

    // compute import file offset
    offsetImports = RvaToOffset (pefile, ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
    if (offsetImports == -1)
        return -1;

    // check filemap validity
    if (!pefile->fmap)
        return -1;

    import = pefile->fmap->map + offsetImports;
    for (nbImports = 0; memcmp(import, &importTableTerminator, sizeof(*import)); nbImports++) {
        import = pefile->fmap->map + sizeof(*import) * nbImports;
    }

    return nbImports;
}

// read imports directory
uint64_t PeReadDataDirectoryImports (PE_FILE *pefile, uint64_t data) {
    size_t nbImports, idxImport;
    struct list_imports *imports;
    uint64_t offsetName, offsetImports, vaThunk;
    IMAGE_NT_HEADERS *ntHeaders;
    PIMAGE_IMPORT_DESCRIPTOR import;

    // bad file pointer
    if (!pefile)
        return -1;

    // get nt header
    ntHeaders = PeGetNtHeader (pefile);
    if (!ntHeaders)
        return -1;

    // compute import file offset
    offsetImports = RvaToOffset (pefile, ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
    if (offsetImports == -1)
        return -1;

    // set up filemap
    if (!pefile->fmap)
        pefile->fmap = filemap_create (pefile->fp);
    if (!pefile->fmap)
        return -1;

    // get number of imports
    nbImports = PeGetDataDirectoryImportsCount (pefile);
    if (nbImports == -1)
        return -1;

    // get
    imports = pefile->directory_data[IMAGE_DIRECTORY_ENTRY_IMPORT];
    imports->libraries = calloc(nbImports, sizeof(*imports));
    imports->nLibraries = nbImports;
    // functions imported
    imports->hints = calloc(nbImports, sizeof(size_t *));
    imports->functions = calloc(nbImports, sizeof(char **));
    imports->nFunctions = calloc(nbImports, sizeof(size_t));

    //
    idxImport = 0;
    while (nbImports--) {
        // get import
        import = pefile->fmap->map + offsetImports;
        offsetImports += sizeof(*import);

        // read import name
        offsetName = RvaToOffset (pefile, import->Name);

        // which one is valid? :)
        if ( import->OriginalFirstThunk )
            vaThunk = (uint64_t) import->OriginalFirstThunk;
        else
            vaThunk = (uint64_t) import->FirstThunk;

        PeReadDataDirectoryImportThunks (pefile, imports, idxImport, vaThunk);
        imports->libraries[idxImport] = pefile->fmap->map + offsetName;

        idxImport++;
    }

    pefile->imports = imports;

    return imports;
}

// count number of import functions you have in a library
uint64_t PeGetDataDirectoryImportThunksCount (PE_FILE *pefile, uint64_t offsetThunks) {
    uint64_t nbImports;
    uint64_t offsetImports;
    IMAGE_NT_HEADERS *ntHeaders;
    IMAGE_THUNK_DATA32 importThunkTableTerminator = { {0} };
    IMAGE_THUNK_DATA32 *import;

    // check file pointer
    if (!pefile)
        return -1;

    // get nt headers
    ntHeaders = PeGetNtHeader (pefile);
    if (!ntHeaders)
        return -1;

    // compute import file offset
    offsetImports = RvaToOffset (pefile, ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
    if (offsetImports == -1)
        return -1;

    // check filemap validity
    if (!pefile->fmap)
        return -1;

    import = pefile->fmap->map + offsetThunks;
    for (nbImports = 0; memcmp(import, &importThunkTableTerminator, sizeof(*import)); nbImports++) {
        import = pefile->fmap->map + offsetThunks;
        offsetThunks += sizeof(*import);
    }

    // we remove the count of thunk table terminator
    return nbImports - 1;
}

// read imports thunk data
uint64_t PeReadDataDirectoryImportThunks (PE_FILE *pefile, uint64_t data, size_t idxLibrary, uint64_t dwRVA) {
    struct list_imports *imports = data;
    size_t nThunks, idxThunks;
    uint64_t dwOffsetThunk;
    IMAGE_THUNK_DATA32 *thunkData, thunkDataTerminator = { {0} };
    IMAGE_IMPORT_BY_NAME *importByName;

    // bad pointer
    if (!pefile)
        return -1;

    if (!pefile->fmap)
        pefile->fmap = filemap_create (pefile->fp);
    if (!pefile->fmap)
        return -1;

    // set offset to thunk data structure
    dwOffsetThunk = RvaToOffset (pefile, dwRVA);
    if (dwOffsetThunk == -1)
        return -1;

    // get thunk count
    nThunks = PeGetDataDirectoryImportThunksCount (pefile, dwOffsetThunk);
    if (nThunks == -1)
        return -1;

    imports->functions[idxLibrary] = calloc(nThunks, sizeof(char *));
    imports->hints[idxLibrary] = calloc(nThunks, sizeof(size_t));
    imports->nFunctions[idxLibrary] = nThunks;

    idxThunks = 0;
    do {
        // read thunk
        thunkData = pefile->fmap->map + dwOffsetThunk;

        // keep track of actual thunk
        dwOffsetThunk += sizeof(*thunkData);

        // if we have an ordinal
        // then we print it
        if ( thunkData->u1.AddressOfData & IMAGE_ORDINAL_FLAG32 ) {
            // snprintf (buffer, 1024, "%u", dwRVA & ~IMAGE_ORDINAL_FLAG32);
        }
        // else we get the function name
        else {
            // alloc
            if (idxThunks >= nThunks) {
                nThunks *= 2;
                imports->functions[idxLibrary] = calloc(nThunks, sizeof(char *));
                imports->hints[idxLibrary] = calloc(nThunks, sizeof(size_t));
                imports->nFunctions[idxLibrary] = nThunks;
            }
            // we get name
            importByName = pefile->fmap->map + RvaToOffset(pefile, thunkData->u1.AddressOfData);
            if (importByName != -1 && importByName != 0 && importByName < (pefile->fmap->map + pefile->fmap->szMap)) {
                imports->hints[idxLibrary][idxThunks] = importByName->Hint;
                imports->functions[idxLibrary][idxThunks] = importByName->Name;
                idxThunks++;
            }
        }
    }
    while (memcmp(thunkData, &thunkDataTerminator, sizeof(thunkDataTerminator)) != 0);

    return pefile->directory_data[IMAGE_DIRECTORY_ENTRY_IMPORT];
}

// read resources directory
uint64_t PeReadDataDirectoryResources (PE_FILE *pefile, uint64_t data) {
    return 0;
}

// generic data directory handler
uint64_t PeReadDataDirectoryGeneric (PE_FILE *pefile, uint64_t data) {
    printf("[-] Data directory handler not implemented\n");

    return 0;
}

// resolve an exported function
uint64_t PeResolveExportHash (uint64_t base, uint64_t hash) {
    return 0;
}

// resolve an exported function
uint64_t PeResolveImportHash (uint64_t base, uint64_t hash) {
    return 0;
}

// resolve an exported function
uint64_t PeResolveExportName (uint64_t base, char *function) {
    return 0;
}

// resolve an imported function
uint64_t PeResolveImportName (uint64_t base, char *function) {
    return 0;
}

// resolve a function
uint64_t PeResolveSymbols (uint64_t base, char **functions, uint64_t nFunctions) {
    return 0;
}

