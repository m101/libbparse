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
int ElfCheckArchitecture (FILE *fp) {
	Elf32_Ehdr* elfHeader;

	// get elf header
	elfHeader = ElfGetHeader (fp);
	if (!elfHeader)
		return -1;

	if (elfHeader->e_machine == EM_386)
		return 1;
	else
		return 0;	
}

// get elf header
Elf32_Ehdr* ElfGetHeader (FILE *fp) {
	struct filemap_t *fmap;

	// check file pointer
	if (!fp)
		return NULL;

	// create filemap
	fmap = filemap_create (fp);
	if (!fmap)
		return NULL;

	return fmap->map;
}

// get program headers table
Elf32_Phdr* ElfGetProgramHeadersTable (FILE *fp) {
	struct filemap_t *fmap;	
	Elf32_Ehdr *elfHeader;
	Elf32_Phdr *programHeadersTable;

	// check file pointer
	if (!fp)
		return NULL;

	// create filemap
	fmap = filemap_create (fp);
	if (!fmap)
		return NULL;

	// get elf header
	elfHeader = ElfGetHeader(fp);
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
Elf32_Shdr* ElfGetSectionHeadersTable (FILE *fp) {
	struct filemap_t *fmap;
	Elf32_Ehdr *elfHeader;
	Elf32_Shdr *sectionsTable;

	// check file pointer
	if (!fp)
		return NULL;

	// create filemap
	fmap = filemap_create (fp);
	if (!fmap)
		return NULL;
	
	// get elf header
	elfHeader = ElfGetHeader(fp);
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
char** ElfGetSectionNamesTable (FILE *fp) {
	struct filemap_t *fmap;
	Elf32_Ehdr *elfHeader;
	Elf32_Shdr *sectionNamesTableHeader;
	char *name, **sectionNamesTable;
	size_t idxName, offsetName, offsetSectionNamesHeader;

	// check file pointer
	if (!fp)
		return NULL;

	// create filemap
	fmap = filemap_create (fp);
	if (!fmap)
		return NULL;
	
	// get elf header
	elfHeader = ElfGetHeader(fp);
	if (!elfHeader)
		return NULL;

	// if no section names table
	if (elfHeader->e_shstrndx == SHN_UNDEF)
		return NULL;
	// else we have one
	Elf32_Shdr* sectionNamesTableHeader2 = ElfGetSectionHeadersTable (fp);
	sectionNamesTableHeader2 += (elfHeader->e_shstrndx * elfHeader->e_shentsize);
	sectionNamesTableHeader = &(ElfGetSectionHeadersTable (fp)[elfHeader->e_shstrndx]);	

	offsetSectionNamesHeader = elfHeader->e_shstrndx * elfHeader->e_shentsize;
	/*
	printf("section names table header entry (bad) : 0x%x + 0x%x = 0x%x\n", ElfGetSectionHeadersTable (fp), offsetSectionNamesHeader,
	       													   ElfGetSectionHeadersTable (fp) + offsetSectionNamesHeader);
	printf("section names table header entry (good): 0x%x + 0x%x = 0x%x\n", ElfGetSectionHeadersTable (fp), offsetSectionNamesHeader, sectionNamesTableHeader);
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
