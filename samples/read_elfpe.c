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

#include "file_elf.h"
#include <file_pe.h>
#include <file_pe_view.h>

void usage (int argc, char *argv[]) {
	printf("Usage: %s program\n", argv[0]);
}

int checkFile (FILE *fp) {
	int check;

	// file handle check
	if (!fp) {
		fprintf(stderr, "Error: Not a valid file handle\n");
		return -1;
	}
	
	if (PeCheck(fp) == 0 || ElfCheck(fp) == 0) {
		fprintf(stderr, "Error: Not a valid executable file\n");
		return -1;
	}

	printf("Valid executable file\n");

	check = ElfCheckArchitecture(fp);
	if (check == 0 || check == -1) {
		fprintf(stderr, "Error: Architecture isn't supported\n");
		return -1;
	}

	return 0;
}

int pe_dump (FILE *fp) {
    PE_FILE *pefile;

	// file handle check
	if (!fp) {
		fprintf(stderr, "Error: Not a valid file handle\n");
		return -1;
	}

	show_infos(fp);
    show_section_headers (fp);
	show_libraries (fp);
	show_exports (fp);
	show_imports (fp);

	return 0;
}

int elf_dump (char *filename) {
    FILE *fp;
	Elf32_Ehdr *elf_header = NULL;

    if (!filename) {
        return -1;
    }

	// file handle check
    fp = fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "Error: Not a valid file handle\n");
		return -2;
	}

	elf_header = ElfGetHeader(fp);
	elf_header_print_info(elf_header);
	elf_header_print_section_info(filename);
	elf_header_get_symbols (filename);

	return 0;
}

int main (int argc, char *argv[]) {
    FILE *fp;
    char *filename;

	//
	if (argc < 2) {
		usage (argc, argv);
		exit(1);
	}

    filename = argv[1];
	fp = fopen (filename, "rb");
    if (!fp) {
        fprintf (stderr, "Error: Failed opening %s\n", argv[1]);
        return 1;
    }

	// file checks
	if (checkFile (fp) < 0) {
		fprintf(stderr, "Error: File analysis failed\n");
		exit(1);
	}

	// dump file :)
	if (PeCheck(fp)) {
		pe_dump(fp);
	}
	else if (ElfCheck(fp)) {
		elf_dump(fp);
	}

	fclose(fp);	

	return 0;
}
