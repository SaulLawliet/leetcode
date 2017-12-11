/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#ifndef __DATA_STRUCTURES_ARRAY_H
#define __DATA_STRUCTURES_ARRAY_H

/* FORMAT: [%d,%d,%d] */
int* arrayNewByStr(const char* str, int* size);
char* arrayToString(const int* array, int size);
int* arrayCopy(const int* array, int size);

void array2DFree(void** array, int row);

/* FORMAT: [[%d,%d,%d],[%d,%d,%d]] */
int** array2DNewByStr(const char* str, int* row, int** cols);
char* array2DToString(int** arrays, int row, int* cols);
int** array2DNewByStrSameCol(const char* str, int* row, int* col);
char* array2DToStringSameCol(int** arrays, int row, int col);

/* FORMAT: [%s,%s,%s] */
char** sarrayNewByStr(const char* str, int* size);
char* sarrayToString(char** strs, int size);

/* FORMAT: [%f,%f,%f] */
double* darrayNewByStr(const char* str, int* size);
char* darrayToString(const double* array, int size, int precision);

#endif  /* __DATA_STRUCTURES_ARRAY_H */
