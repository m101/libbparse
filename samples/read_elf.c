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

#include <elf.h>

#include "file_elf.h"

int main (int argc, char *argv[])
{
    int check;
    FILE *fp;
    Elf32_Ehdr *elf_header = NULL;

    if (!(argc > 1))
        return 0;

    // open file
    fp = fopen(argv[1], "rb");
    if (!fp)
        return 1;

    // check elf file
    if(!ElfCheck(fp)) {
        fprintf(stderr, "Error: Not an ELF file\n");
        exit (1);
    }

    check = ElfCheckArchitecture(fp);
    if (check == 0 || check == -1) {
        fprintf(stderr, "Error: Architecture isn't taken into account\n");
        exit (1);
    }

    elf_header = ElfGetHeader(fp);
    elf_header_print_info(elf_header);
    elf_header_print_section_info(argv[1]);
    elf_header_get_symbols (argv[1]);

    return 0;
}
