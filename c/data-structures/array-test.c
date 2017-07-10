#include <stdlib.h>  /* free() */
#include "array.h"
#include "../test.h"

int main(void) {
  size_t size;
  char *str = "[2147483647, 0, -2147483648]";

  int *array = arrayNewByStr(str, &size);
  EXPECT_EQ_INT(3, (int)size);
  char *array_str = arrayToString(array, size);
  EXPECT_EQ_STRING(str, array_str);

  int *array2 = arrayCopy(array, size);
  EXPECT_EQ_INT(3, (int)size);

  free(array);
  free(array_str);

  array_str = arrayToString(array2, size);
  EXPECT_EQ_STRING(str, array_str);

  free(array2);
  free(array_str);

  array_str = arrayToString(NULL, 0);
  EXPECT_EQ_STRING("[]", array_str);
  free(array_str);

  return testOutput();
}
