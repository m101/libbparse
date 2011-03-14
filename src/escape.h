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

#ifndef _ESCAPE_H_
#define _ESCAPE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char* escape_hex (unsigned char *bytes, size_t nbytes);
// unescape escaped hex
unsigned char* unescape_hex (char *str, size_t szStr);
unsigned int str2num (unsigned char *str, size_t len);

#endif
