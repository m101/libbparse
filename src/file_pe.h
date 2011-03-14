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

#ifndef _FILE_PE_H_
#define _FILE_PE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#if defined (WIN32) || defined (_WIN32_)
#include <windows.h>
#else
#include "file_pe_defs.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "filemap.h"

#include "file_generic.h"

    struct list_exports
    {
        char **names;
        size_t *szNames, nNames;
        uint64_t *functions;
        size_t nFunctions;
        WORD *ordinals;
    };

    struct list_imports
    {
        //
        char **libraries;
        size_t nLibraries;
        //
        size_t **hints;
        char ***functions;
        size_t *nFunctions;
    };

    typedef struct _PE_FILE32
    {
        //
        char *filename;
        size_t szFilename;
        FILE *fp;

        //
        uint64_t entry_point;

        //
        struct filemap_t *fmap;
        //
        struct list_exports *exports;
        struct list_imports *imports;

        //
        union {
            IMAGE_DATA_DIRECTORY *directories_first, *directories_start;
        };
        IMAGE_DATA_DIRECTORY *directories_last, *directories_end;
        //
        void **directory_data;
    } PE_FILE;


    // check if PE FILE
    int PeCheck (FILE *fp);
    // parse PE file
    PE_FILE* PeLoad (char *filename);
    // get dos header
    PIMAGE_DOS_HEADER PeGetDosHeader (PE_FILE *pefile);
    // get nt header
    PIMAGE_NT_HEADERS PeGetNtHeader (PE_FILE *pefile);
    //  Get section header table
    IMAGE_SECTION_HEADER* PeGetSectionHeaderTable (PE_FILE *pefile);
    // free loaded pe file
    void PeUnload(PE_FILE **pefile);


    // convert a relative virtual address into a virtual address
    uint64_t RvaToVa (PE_FILE *pefile, uint64_t dwRVA);
    // convert a file offset into a RVA
    uint64_t OffsetToRva (PE_FILE *pefile, uint64_t dwOffset);
    // convert a RVA into a file offset
    uint64_t RvaToOffset (PE_FILE *pefile, uint64_t dwRVA);

#ifdef __cplusplus
}
#endif

#endif /* _FILE_PE_H_ */
