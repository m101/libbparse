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

#ifndef _ELF_ANALYSE_H
#define _ELF_ANALYSE_H

#include <stdio.h>
#include <stdlib.h>

#include <elf.h>

#include "filemap.h"

#define	ELF_MAGIC		0x464c457f
#define ELF_MAX_SIZE 	1024*1024*1024

typedef struct ELF_FILE32 {
    //
    FILE *fp;
    char *filename;
	struct filemap_t *fmap;
} ELF_FILE;

// init elf object
ELF_FILE* ElfLoad (char *filename);
void ElfUnload (ELF_FILE **elf);
// check file type
int ElfCheck (FILE *fp);
// check if we parse architecture
int ElfCheckArchitecture (ELF_FILE *elffile);
// get elf header
Elf32_Ehdr* ElfGetHeader (ELF_FILE *elffile);
// get sections table
Elf32_Shdr* ElfGetSectionHeadersTable (ELF_FILE *elffile);
// get section table with all names
char** ElfGetSectionNamesTable (ELF_FILE *elffile);

void elf_header_get_symbols (char *binaryName);

#endif
