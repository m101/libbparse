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
#include <unistd.h>
#include <getopt.h>

#include <file_pe.h>
#include <file_pe_view.h>

struct option opts[] = {
    { "imports", no_argument, NULL, 'a' },
    { "exports", no_argument, NULL, 'b' },
    { "infos", no_argument, NULL, 'c' },
    { "sections", no_argument, NULL, 'd' },
    { "libraries", no_argument, NULL, 'e' },
    { "file", required_argument, NULL, 'f' },
    { "all", no_argument, NULL, 'g' },
    { NULL, 0, NULL, 0 }
};

void usage (void) {
    printf("Read PE\n");
    printf("--imports show imports\n");
    printf("--exports show exports\n");
    printf("--infos show infos\n");
    printf("--sections show sections\n");
    printf("--libraries show used libraries\n");
    printf("--all show all infos\n");
    printf("--file [file] file to analyze (required)\n");
}

int main (int argc, char *argv[])
{
    PE_FILE *pefile;
    char *filename = NULL;
    int option, opt_idx = 0;
    // flags
    int flag_info = 0, flag_import = 0, flag_export = 0,
        flag_sections = 0, flag_lib = 0;

    if (argc < 2) {
        usage();
        return 1;
    }

    // parse options
    while (1) {
        option = getopt_long(argc, argv, "",
                opts, &opt_idx);

        if (option == -1)
            break;

        switch (option) {
            case 'c':
                flag_info = 1;
                break;

            case 'd':
                flag_sections = 1;
                break;

            case 'e':
                flag_lib = 1;
                break;

            case 'b':
                flag_export = 1;
                break;

            case 'a':
                flag_import = 1;
                break;

            case 'g':
                flag_info = 1;
                flag_sections = 1;
                flag_lib = 1;
                flag_export = 1;
                flag_import = 1;
                break;

            case 'f':
                if (optarg)
                    filename = optarg;
                else
                    filename = NULL;
                break;

            default:
                break;
        }
    }

    if (filename == NULL) {
        fprintf(stderr, "Error: No file inputted\n");
        exit(1);
    }

    if (flag_info)
        show_infos(filename);

    if (flag_sections)
        show_section_headers (filename);

    if (flag_lib)
        show_libraries (filename);

    if (flag_export)
        show_exports (filename);

    if (flag_import)
        show_imports (filename);

    return 0;
}

