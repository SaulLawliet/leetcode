/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#ifndef C_DATA_STRUCTURES_ARRAY_H_
#define C_DATA_STRUCTURES_ARRAY_H_

typedef struct arrayEntry arrayEntry;

typedef enum {
  ARRAY_INT,
  ARRAY_CHAR,
  ARRAY_DOUBLE,
  ARRAY_STRING,
} arrayType;

arrayEntry *arrayNew(arrayType type);
arrayEntry *arrayParse(const char *str, arrayType type);
arrayEntry *arrayParse1D(const char *str, arrayType type);
arrayEntry *arrayParse2D(const char *str, arrayType type);

arrayEntry *arrayFrom1D(void *v, int size, arrayType type);
arrayEntry *arrayFrom2D(void *v, int row, int *cols, arrayType type);
arrayEntry *arrayFrom2DSameCol(void *v, int row, int col, arrayType type);

void arrayFree(arrayEntry *entry);

char *arrayToString(arrayEntry *entry);
char *arrayToString1D(void *v, int size, arrayType type);
char *arrayToString2D(void *v, int row, int *cols, arrayType type);
char *arrayToString2DSameCol(void *v, int row, int col, arrayType type);

/* getter, setter */
void *arrayValue(arrayEntry *entry);
int arraySize(arrayEntry *entry);
void arraySetSize(arrayEntry *entry, int size);

void arraySetPrecision(arrayEntry *entry, int precision);

int arrayRow(arrayEntry *entry);
int *arrayCols(arrayEntry *entry);
int arrayCol(arrayEntry *entry);

#endif /* C_DATA_STRUCTURES_ARRAY_H_ */
