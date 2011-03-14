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

#ifndef _RAW_DATA_H_
#define _RAW_DATA_H_

#include <stdio.h>
#include <stdlib.h>

struct raw_data {
    unsigned char *data;
    size_t capacity;
    size_t used;
};

struct raw_data* raw_data_new(size_t size);
struct raw_data* raw_data_realloc(struct raw_data *rd, size_t size);
void raw_data_destroy(struct raw_data **data);

#endif /* _RAW_DATA_H_ */
