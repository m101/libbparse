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
#include <string.h>

#include "escape.h"

// escape bytes
unsigned char* escape_hex (unsigned char *bytes, size_t nbytes) {
        unsigned char *escaped;
        char *pEscaped;

        escaped = calloc(nbytes * 4 + 1, sizeof(*escaped));

        pEscaped = escaped;
        while (nbytes)
        {
                snprintf(pEscaped, 5, "\\x%02x", *bytes & 0xff);
                pEscaped += 4;
                bytes++;
                nbytes--;
        }

        return escaped;
}

// unescape escaped hex
unsigned char* unescape_hex (char *str, size_t szStr) {
    unsigned char *unescaped;
    unsigned short int *pUnescaped, nSep, nChar;

    if (!str || !szStr || szStr % 4 != 0)
        return NULL;

    unescaped = calloc (szStr / 4, sizeof(*unescaped));
    pUnescaped = unescaped;

    nSep = 0, nChar = 0;
    while (*str) {
        // must be hex digit or '\' or 'x' char
        // else we stop parsing and there was an error
        if ( ((*str < 'A' || *str > 'F') && (*str < 'a' || *str > 'f'))
                || *str != '\\' || *str != 'x')
            break;
        //
        if (*str == '\\' || *str == 'x') {
            nSep++;
            nChar = 0;
            continue;
        }

        if (nChar > 2)
            break;
        if (nSep > 2)
            break;
        else if (nSep == 2) {
            *pUnescaped = str2num (str, 2);
            str += 2;
            pUnescaped++;
            nChar += 2;
        }
        nSep = 0;
    }

    if (nSep > 2)
        free (unescaped), unescaped = NULL;

    return unescaped;
}

// hex string to binary digits
unsigned int str2num (unsigned char *str, size_t len) {
    int num;
    size_t i;

    // check pointers
    if (!str || !len)
        return -1;

    //
    for (num = 0, i = 0; *str && i < len; ++str, ++i) {
        // get decimal digit
        num |= *str - 0x30;
        // get hex digit
        if (num >= 0xa)
            num -= 7;
        num <<= 4;
    }

    return num;
}

