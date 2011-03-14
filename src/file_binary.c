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

#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include "escape.h"
#include "file_binary.h"

// check file existence
// 0 = file doesn't exist
// other = file exist
long file_exist (char *filename) {
    FILE *fp;

    if (!filename)
        return 0;

    fp = fopen(filename, "r");
    fclose(fp);

    return (long) fp;
}

// file patching
int file_patch (char *filename,
        char *original, size_t szOriginal,
        char *patch, size_t szPatch) {
    long offsetOriginal, writtenBytes;
    FILE *fp;

    // bad file pointer
    if (!filename)
        return -1;

    // open file for update
    fp = fopen(filename, "r+");
    if (!fp)
        return -1;

    // search offset to patch
    offsetOriginal = binary_search_bytes_in_file (fp, original, szOriginal);
    if (!offsetOriginal)
        return -1;

    // we patch file
    writtenBytes = fwrite (patch, szPatch, 1, fp);

    // we close file
    fclose(fp);

    return writtenBytes;
}

// check for wildcard
int iswildcard (char c) {
    // wildcards table
    char *wildcards = "*?";

    // we search for wildcard correspondance
    while (*wildcards)
    {
        if (c == *wildcards)
            return 1;
        wildcards++;
    }

    // it is not a wildcard
    return 0;
}

// compare bytes taking into accounts wildcards
// wildcards are ignored
int binary_cmp_with_wildcards (void *mem1, void *mem2, size_t n) {
    char *block1, *block2;

    block1 = mem1;
    block2 = mem2;

    while (n)
    {
        if ( !iswildcard(*block2) )
        {
            if (*block1 != *block2)
                return *block1 - *block2;
        }

        block1++;
        block2++;
        n--;
    }

    return 0;
}

// search needle in haystack
char* binary_search_bytes (char *haystack, const size_t szHaystack,
        char *needle, const size_t szNeedle) {
    char *traverse;
    int found;

    traverse = haystack;
    while (traverse + szNeedle <= haystack + szHaystack) {
        // possible match
        if ( *traverse == *needle ) {
            // searching if it's a match
            found = binary_cmp_with_wildcards(traverse, needle, szNeedle);

            // it match
            if (found == 0)
                return traverse;
        }

        // we continue traversing the haystack
        traverse++;
    }

    // we didn't find anything
    return 0;
}

// search needle in haystack
// return offset in file
long binary_search_bytes_in_file (FILE *fp,
        char *needle, const size_t szNeedle) {
    int c, found;
    char *str;

    // file pointer is not valid
    if (!fp)
        return -1;

    // we allocate enough memory for working buffer
    str = calloc(szNeedle + 1, sizeof(*str));

    // we go through the file
    while ( (c = fgetc(fp)) && (c != EOF) ) {
        // possible match
        if ( c == *needle ) {
            // we go one character backward
            fseek(fp, -1, SEEK_SET);
            // we get the string
            fgets(str, szNeedle, fp);
            // searching if it's a match
            found = binary_cmp_with_wildcards(str, needle, szNeedle);

            // it match
            if (found == 0)
                return ftell(fp) - szNeedle;
        }
    }

    // we didn't find anything
    return -1;
}

// get nasm representation of bytes
char* str_to_nasm (char *bytes, size_t szBytes) {
    char *buffer, *backup;

    buffer = calloc (strlen("payload db ")
            + szBytes * 5 + 2,
            sizeof(*buffer) );

    backup = buffer;
    strcpy (buffer, "payload db ");
    buffer += strlen("payload db ");
    while (szBytes) {
        snprintf(buffer, 6, "0x%02x,", *bytes & 0xff);
        buffer += 5;
        bytes++;
        szBytes--;
    }
    strcat(buffer, "0");

    return backup;
}

// get c representation of bytes
char* str_to_c (char *bytes, size_t szBytes) {
    char *encoded, *buffer;
    size_t szEncoded;

    szEncoded = strlen("char payload[] = \"\"") + szBytes * 4 + 1;
    encoded = calloc (szEncoded, sizeof(*encoded));
    if (!encoded)
        return NULL;

    strncpy (encoded, "char payload[] = \"", szEncoded);

    // hex escape payload (with error check)
    buffer = escape_hex (bytes, szBytes);
    if (!buffer) {
        free (encoded);
        return NULL;
    }

    strncat (encoded, buffer, szEncoded - strlen(encoded));
    strncat (encoded, "\"", szEncoded - strlen(encoded));
    // we ensure we cleanly end the string
    encoded[szEncoded - 1] = '\0';

    // cleanup
    free(buffer);

    return encoded;
}

// read file in binary mode
char* bin_to_str (char *filename, char* (*func)(char *, size_t)) {
    size_t szBytes;
    char *bytes, *buffer;
    int c;
    FILE *fp;

    // arguments check
    if (!filename)
        return NULL;

    fp = fopen (filename, "rb");
    if (!fp)
        return NULL;

    // get file size
    fseek(fp, 0, SEEK_END);
    szBytes = ftell(fp);
    // alloc
    buffer = calloc (szBytes + 1, sizeof(*buffer));
    if (!buffer)
        return NULL;

    fseek(fp, 0, SEEK_SET);

    // fill buffer with file content
    bytes = buffer;
    while ( (c = fgetc(fp)) != EOF && bytes < buffer + szBytes ) {
        *bytes = c;
        bytes++;
    }

    fclose(fp);

    // don't call any callback function
    // return read bytes
    if (func == NULL)
        return buffer;
    // callback function result
    else {
        bytes = func (buffer, szBytes);
        free(buffer);

        return bytes;
    }
}

// get file size
int file_size (char *filename) {
    FILE *fp;
    size_t szBytes;

    // check pointer
    if (!filename)
        return -1;

    // open file
    fp = fopen (filename, "r");
    if (!fp)
        return -1;
    // go end of file
    fseek (fp, 0, SEEK_END);
    // get file size
    szBytes = ftell (fp);
    // close file
    fclose (fp);

    return szBytes;
}

void bytes_show (char *bytes, size_t szBytes) {
    while (szBytes) {
        fprintf(stdout, "\\x%2x", *bytes & 0xff);
        bytes++;
        szBytes--;
    }
}

// read ascii string from file
char* file_read_str_ascii (FILE *fp) {
    int c;
    char *str, *buffer;
    size_t szStr;

    szStr = 256;
    str = malloc (sizeof(*str) * szStr);
    buffer = str;

    while ( (c = fgetc (fp)) != EOF ) {
        if (szStr == 10240) {
            printf ("max string size\n");
            return NULL;
        }

        if (buffer - str <= szStr) {
            str = realloc (str, szStr * 2);
            buffer = str + szStr;
            szStr *= 2;
        }

        *buffer = c;
        buffer++;
    }

    return str;
}

