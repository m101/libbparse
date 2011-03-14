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

#ifndef _TYPE_WINDOWS_H_
#define _TYPE_WINDOWS_H_

#ifndef WIN32
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#define TRUE    1;
#define FALSE   0;

    typedef unsigned int DWORD;
    typedef unsigned short int WORD;
    typedef unsigned char BYTE;
    typedef long LONG;

    typedef uint64_t __uint64; /* <stdint.h> */
    typedef uint64_t __u64;
    typedef int64_t __int64;
    typedef int64_t __s64; /* <stdint.h>, <sys/types.h> */

#if !defined(_M_IX86)
    //    typedef unsigned __int64 ULONGLONG;
    typedef uint64_t ULONGLONG;
#else
    typedef double ULONGLONG;
#endif

#ifdef __cplusplus
}
#endif
#endif // end WIN32

#endif /* _TYPE_WINDOWS_H_ */
