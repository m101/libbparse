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
#include <ctype.h>

#include "escape.h"

// escape bytes
unsigned char* escape_hex (unsigned char *bytes, int nbytes) {
        unsigned char *escaped;
        char *pEscaped;

        if (!bytes || nbytes <= 0) {
            fprintf(stderr, "Error: escape_hex(): Arguments are not init correctly\n");
            return NULL;
        }

        escaped = calloc(nbytes * 4 + 1, sizeof(*escaped));
        if (!escaped) {
            fprintf(stderr, "Error: escape_hex(): Could not alloc() buffer\n");
            return NULL;
        }

        pEscaped = escaped;
        while (nbytes) {
                snprintf(pEscaped, 5, "\\x%02x", *bytes & 0xff);
                pEscaped += 4;
                bytes++;
                nbytes--;
        }

        return escaped;
}

// unescape escaped hex
unsigned char* unescape_hex (char *str, int szStr) {
    unsigned char *unescaped;
    unsigned short int nSep, nChar;
    unsigned char *pUnescaped;
    // work str
    char *ptr;

    // check arguments
    if (!str || szStr <= 0 || szStr % 4 != 0)
        return NULL;

    // alloc
    unescaped = calloc (szStr / 4, sizeof(*unescaped));
    if (!unescaped)
        return NULL;
    pUnescaped = unescaped;

    nSep = 0, nChar = 0;
    ptr = str;
    while (*ptr && ptr < str + szStr) {
        printf("\n*ptr: %c\n", *ptr);
        // must be hex digit or '\' or 'x' char
        // else we stop parsing and there was an error
        if ( ((*ptr < 'A' && *ptr > 'F') && (*ptr < 'a' && *ptr > 'f'))
                && (*ptr != '\\' && *ptr != 'x') )
            break;
        printf("ptr - str: %d\n", ptr - str);
        //
        if (*ptr == '\\' || *ptr == 'x') {
            nSep++;
            nChar = 0;
        }

        if (nChar > 2)
            break;
        if (nSep > 2)
            break;
        else if (nSep == 2) {
            ptr++;
            *pUnescaped = hexstr2num (ptr, 2);
            printf("ptr: '%c.%c'\n", *ptr, ptr[1]);
            printf("ptr: '%x.%x'\n", *ptr, ptr[1]);
            printf("*pUnescaped: %x\n", *pUnescaped);
            pUnescaped++;
            nChar += 2;
            nSep = 0;
            // skip
            ptr++;
        }
        ptr++;
    }

    if (nSep > 2)
        free (unescaped), unescaped = NULL;

    return unescaped;
}

// unescape any c escaped string '\r', '\n', '\b', ... '\xHH', '\000'
unsigned char* unescape_c (char *str, int len) {
    int c;
    int escaped;
    int offset;
    // remaining length
    int rlen;
    char *ptr;

    // check parameters
    if (!str || len <= 0)
        return NULL;

    for (ptr = str; *ptr != 0 && offset < len; ptr++) {
        offset = ptr - str;
        rlen = len - offset;

        if (*ptr != '\\')
            continue;

        switch (*ptr) {
            case 'a':
                c = '\007'; 
                break;
            case 'b':
                c = '\b';   
                break;
            case 'f':
                c = '\f';   
                break;
            case 'n':
                c = '\n';   
                break;
            case 'r':
                c = '\r';   
                break;
            case 't':
                c = '\t';  
                break;
            case 'v':
                c = '\013';
                break;
            case '\\': 
                c = '\\';   
                break;
            case '?':
                c = '?';
                break;
            case '\'':
                c = '\'';  
                break;
            case '"':
                c = '\"';    
                break;

            // hexadecimal
            case 'x':

                break;

            default:
                break;
        }
    }

}

unsigned char hexchar2num (unsigned char c) {
    if ( !(('a' <= c && c <= 'f') || ('A' <= c && c <= 'F') || isdigit(c)) )
        return 0;

    printf("before: %c (%d)\n", c, c);

    c = toupper(c);
    // get decimal digit
    c -= 0x30;
    // get hex digit
    if (c >= 0xa)
        c -= 7;
    printf("after : %c (%d)\n", c, c);

    return c;
}

// hex string to binary digits
unsigned int hexstr2num (unsigned char *str, int len) {
    int num;
    int c;
    int i;

    // check pointers
    if (!str || len <= 0)
        return -1;

    //
    for (num = 0, i = 0; *str && i < len; ++str, ++i) {
        c = hexchar2num(*str);
        //c = *str;
        num = (num << 4) | c;
        printf("num: %x(h) %d\n", num, num);
        printf("c  : %x(h) %d\n", c, c);
    }

    return num;
}

