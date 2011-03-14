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

#ifndef _FILE_PE_INTERNAL_H_
#define _FILE_PE_INTERNAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "file_pe.h"

// create a new and empty PE_FILE struct :)
PE_FILE* PeNew(void);
// read first section header
PIMAGE_SECTION_HEADER PeGetSectionHeaderFirst (PE_FILE *pefile);
// read last section header
PIMAGE_SECTION_HEADER PeGetSectionHeaderLast (PE_FILE *pefile);
// read data directories
uint64_t PeReadDataDirectories (PE_FILE *pefile, uint64_t data);
// read exports directory
uint64_t PeReadDataDirectoryExports (PE_FILE *pefile, uint64_t data);
// count number of imported libraries
size_t PeGetDataDirectoryImportsCount (PE_FILE *pefile);
// read imports directory
uint64_t PeReadDataDirectoryImports (PE_FILE *pefile, uint64_t data);
// count number of import functions you have in a library
uint64_t PeGetDataDirectoryImportThunksCount (PE_FILE *pefile, uint64_t offsetThunks);
// read imports thunk data
uint64_t PeReadDataDirectoryImportThunks (PE_FILE *pefile, uint64_t data, size_t idxLibrary, uint64_t dwRVA);
// read resources directory
uint64_t PeReadDataDirectoryResources (PE_FILE *pefile, uint64_t data);
// generic data directory handler
uint64_t PeReadDataDirectoryGeneric (PE_FILE *pefile, uint64_t data);



struct list_imports* list_imports_new (PE_FILE *pefile);
struct list_imports* list_imports_delete (struct list_imports **imports);
struct list_exports* list_exports_delete (struct list_exports **exports);

#endif /* _FILE_PE_INTERNAL_H_ */
