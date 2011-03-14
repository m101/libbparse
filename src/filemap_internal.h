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

#ifndef _FILEMAP_INTERNAL_H_
#define _FILEMAP_INTERNAL_H_

#include <stdio.h>
#include <stdlib.h>
#include "filemap.h"

struct filemap_list_t
{
    struct filemap_t *filemap;
    struct filemap_list_t *next, *prev;
};

// add filemap in tree
struct filemap_t* filemap_add_fmap (struct filemap_list_t **root, struct filemap_t *filemap);
// remove filemap from tree
void filemap_remove_fmap (struct filemap_list_t **root, struct filemap_t *filemap);
// search file pointer in tree
struct filemap_t* filemap_search (struct filemap_list_t *root, FILE *fp);
// check if file was loaded in memory
struct filemap_t* filemap_exist (FILE *fp);

#endif /* _FILEMAP_INTERNAL_H_ */
