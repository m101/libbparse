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

#include "file_elf.h"
#include "filemap.h"

//
ELF_FILE* ElfLoad (char *filename) {
    FILE *fp;
    ELF_FILE *elf;

    fp = fopen(filename, "r");
    if (!fp)
        return NULL;
    elf = calloc(1, sizeof(*elf));
    if (!elf) {
        fclose(fp);
        return NULL;
    }
    elf->filename = strdup(filename);
    elf->fp = fp;
    elf->fmap = filemap_create(elf->fp);

    return elf;
}

//
void ElfUnload (ELF_FILE **elf) {
    if (!elf)
        return;
    if (!*elf)
        return;
    free((*elf)->filename);
    filemap_destroy(&((*elf)->fmap));
    fclose((*elf)->fp);
    free(*elf);
    *elf = NULL;
}

// check file type
int ElfCheck (FILE *fp) {
	unsigned int magic = 0;

	// check file pointer
	if (!fp)
		return 0;

	fseek(fp, 0, SEEK_SET);
	fread(&magic, 4, 1, fp);

	if (magic == ELF_MAGIC)
		return 1;
	else
		return 0;
}

// check if we parse architecture
int ElfCheckArchitecture (ELF_FILE *elffile) {
	Elf32_Ehdr* elfHeader;

    if (!elffile)
        return -1;

	// get elf header
	elfHeader = ElfGetHeader (elffile->fp);
	if (!elfHeader)
		return -1;

	if (elfHeader->e_machine == EM_386)
		return 1;
	else
		return 0;	
}

// get elf header
Elf32_Ehdr* ElfGetHeader (ELF_FILE *elffile) {
	struct filemap_t *fmap;

    if (!elffile)
        return -1;

	// create filemap
	fmap = filemap_create (elffile->fp);
	if (!fmap)
		return NULL;

	return fmap->map;
}

// get program headers table
Elf32_Phdr* ElfGetProgramHeadersTable (ELF_FILE *elffile) {
	struct filemap_t *fmap;	
	Elf32_Ehdr *elfHeader;
	Elf32_Phdr *programHeadersTable;

    if (!elffile)
        return NULL;

	// create filemap
	fmap = filemap_create (elffile->fp);
	if (!fmap)
		return NULL;

	// get elf header
	elfHeader = ElfGetHeader(elffile->fp);
	if (!elfHeader)
		return NULL;

	// if no program headers table
	if (elfHeader->e_phnum == 0)
		return NULL;
	// else we have one
	programHeadersTable = fmap->map + elfHeader->e_phoff;

	return programHeadersTable;
}

// get sections table
Elf32_Shdr* ElfGetSectionHeadersTable (ELF_FILE *elffile) {
	struct filemap_t *fmap;
	Elf32_Ehdr *elfHeader;
	Elf32_Shdr *sectionsTable;

    if (!elffile)
        return NULL;
    if (!elffile->fp)
        return NULL;

	// create filemap
	fmap = filemap_create (elffile->fp);
	if (!fmap)
		return NULL;
	
	// get elf header
	elfHeader = ElfGetHeader(elffile->fp);
	if (!elfHeader)
		return NULL;
	
	// if no section headers table
	if (elfHeader->e_shnum == 0)
		return NULL;
	// else we have one
	sectionsTable = fmap->map + elfHeader->e_shoff;

	return sectionsTable;
}

// get section table with all names
char** ElfGetSectionNamesTable (ELF_FILE *elffile) {
	struct filemap_t *fmap;
	Elf32_Ehdr *elfHeader;
	Elf32_Shdr *sectionNamesTableHeader;
	char *name, **sectionNamesTable;
	size_t idxName, offsetName, offsetSectionNamesHeader;

    if (!elffile)
        return NULL;

	// create filemap
	fmap = filemap_create (elffile->fp);
	if (!fmap)
		return NULL;
	
	// get elf header
	elfHeader = ElfGetHeader(elffile->fp);
	if (!elfHeader)
		return NULL;

	// if no section names table
	if (elfHeader->e_shstrndx == SHN_UNDEF)
		return NULL;
	// else we have one
	Elf32_Shdr* sectionNamesTableHeader2 = ElfGetSectionHeadersTable (elffile->fp);
	sectionNamesTableHeader2 += (elfHeader->e_shstrndx * elfHeader->e_shentsize);
	sectionNamesTableHeader = &(ElfGetSectionHeadersTable (elffile->fp)[elfHeader->e_shstrndx]);	

	offsetSectionNamesHeader = elfHeader->e_shstrndx * elfHeader->e_shentsize;
	/*
	printf("section names table header entry (bad) : 0x%x + 0x%x = 0x%x\n", ElfGetSectionHeadersTable (elffile->fp), offsetSectionNamesHeader,
	       													   ElfGetSectionHeadersTable (elffile->fp) + offsetSectionNamesHeader);
	printf("section names table header entry (good): 0x%x + 0x%x = 0x%x\n", ElfGetSectionHeadersTable (elffile->fp), offsetSectionNamesHeader, sectionNamesTableHeader);
	*/

	sectionNamesTable = calloc(elfHeader->e_shnum, sizeof(*sectionNamesTable));
	for (idxName = 0, offsetName = 1; idxName < elfHeader->e_shnum; idxName++) {
		name = fmap->map + sectionNamesTableHeader->sh_offset + offsetName;
		sectionNamesTable[idxName] = name;
		offsetName += strlen(name) + 1;
	}

	return sectionNamesTable;
}

void elf_header_get_imports (char *binaryName) {
}

void elf_header_get_symbols (char *binaryName) {
}
