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

#ifndef _FILE_GENERIC_H_
#define _FILE_GENERIC_H_

	// function structure
	struct function_info {
		// 
		int ordinal;
		// name
		char *name;
		size_t szName;
        
        // approximated size
        size_t guessed_size;
        // delta between 2 functions addresses in the same sections
        size_t delta_size;

        // location (useless for imports)
		// virtual address memory (VA)
		int address;
        // file offset
        int foffset;
        // memory offset (RVA)
        int moffset;

		//
		int *argsType;
		size_t nArguments;
		//
		int convention;
	};

	// library structure
	struct library_info {
		// base address of module
		int base;
		// library name
		char *name;
		size_t szName;
		//
		size_t nExport, nImport;
		//
		struct function_info *exports;
		struct function_info *imports;
	};

    // section of data
    struct section_info {
        // section name
        char *name;
        size_t szName;

        // determine read, write, etc type of section
        int flags;

        // section characteristics
        size_t size;

        // location
		// virtual address memory (VA)
		int address;
        // file offset
        int foffset;
        // memory offset (RVA)
        int moffset;
    };

#endif /* _FILE_GENERIC_H_ */
