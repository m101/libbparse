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

#ifndef _FILE_PE_VIEW_H_
#define _FILE_PE_VIEW_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <file_pe.h>

#include <stdio.h>
#include <stdlib.h>

	int show_infos (char *filename);
    int show_section_headers (char *filename);
	int show_libraries (char *filename);
    int show_imports (char *filename);
    int show_exports (char *filename);

#ifdef __cplusplus
}
#endif

#endif /* _FILE_PE_VIEW_H_ */
