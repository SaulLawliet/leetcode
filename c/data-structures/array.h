/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#ifndef __DATA_STRUCTURES_ARRAY_H
#define __DATA_STRUCTURES_ARRAY_H

#include <stddef.h>  /* size_t */

/* FORMAT: [%d, %d, %d] */
int* arrayNewByStr(const char* str, size_t* size);
char* arrayToString(const int* array, size_t size);
int* arrayCopy(const int* array, size_t size);

void array2DFree(void** array, size_t row);

/* FORMAT: [[%d, %d, %d], [%d, %d, %]] */
int** array2DNewByStr(const char* str, size_t* row, size_t* col);
char* array2DToString(int** arrays, size_t row, size_t col);
/* FORMAT: [%s, %s, %s] */
char** sarrayNewByStr(const char* str, size_t* size);
char* sarrayToString(char** strs, size_t size);


#endif  /* __DATA_STRUCTURES_ARRAY_H */
