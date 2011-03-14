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

#ifndef _FILE_PATCHING_H_
#define _FILE_PATCHING_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <stdio.h>

	struct file_binary {
		//
		char *name;
		size_t szName;
		//
		int type;
		//
	};

    // check file existence
    // 0 = file doesn't exist
    // other = file exist
    long file_exist (char *filename);
    // file patching
    int file_patch (char *filename,
                            char *original, size_t szOriginal,
                            char *patch, size_t szPatch);
    // check for wildcard
    int iswildcard (char c);
    // search needle in haystack
    char* binary_search_bytes (char *haystack, const size_t szHaystack,
            char *needle, const size_t szNeedle);
    // search needle in haystack
    // return offset in file
    long binary_search_bytes_in_file (FILE *fp,
            char *needle, const size_t szNeedle);

    // read file in binary mode
    char* bin_to_str (char *filename, char* (*func)(char *, size_t));

    // get c representation of bytes
    char* str_to_c (char *bytes, size_t szBytes);

    // get nasm representation of bytes
    char* str_to_nasm (char *bytes, size_t szBytes);

    // get file size
    int file_size (char *filename);
    // read ascii string from file
    char* file_read_str_ascii (FILE *fp);

#ifdef __cplusplus
}
#endif

#endif /* _FILE_PATCHING_H_ */
