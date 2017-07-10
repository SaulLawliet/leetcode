/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#ifndef __DATA_STRUCTURES_ARRAY_H
#define __DATA_STRUCTURES_ARRAY_H

#include <stddef.h>  /* size_t */

/* STRING FORMAT: [%d, %d, %d] */
int* arrayNewByStr(const char* str, size_t* size);
char* arrayToString(const int* array, size_t size);
int* arrayCopy(const int* array, size_t size);

/** TODO: 单元测试 */
int** array2DNewByStr(const char* str, size_t* row, size_t* col);
void array2DFree(int** array, size_t row);

#endif  /* __DATA_STRUCTURES_ARRAY_H */
