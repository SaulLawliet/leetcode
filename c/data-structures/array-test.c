#include "array.h"
#include "../test.h"

int type;
int precision = 0;

void testArrayRoundTrip(const char *str) {
  arrayEntry *e = arrayParse(str, type);
  if (type == ARRAY_DOUBLE) arraySetPrecision(e, precision);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(str, arrayToString(e));

  arrayFree(e);
}

int main(void) {
  /* 1 dimensional */
  type = ARRAY_INT;
  testArrayRoundTrip("[]");
  testArrayRoundTrip("[-3,-2,-1,0,1,2,3]");
  testArrayRoundTrip("[2147483647,0,-2147483648]");

  type = ARRAY_DOUBLE;
  testArrayRoundTrip("[]");
  precision = 1;
  testArrayRoundTrip("[1.0,-1.2,0.3]");
  precision = 5;
  testArrayRoundTrip("[1.00002,-1.29393,0.31233]");

  type = ARRAY_CHAR;
  testArrayRoundTrip("[]");
  testArrayRoundTrip("[a,b,c]");
  testArrayRoundTrip("[!,@,#,%]");

  type = ARRAY_STRING;
  testArrayRoundTrip("[]");
  testArrayRoundTrip("[hello,world]");
  testArrayRoundTrip("[h e l l o,w  o  rld]");

  /* 2 dimensional */
  type = ARRAY_INT;
  testArrayRoundTrip("[[]]");
  testArrayRoundTrip("[[1,2],[3,4,5]]");

  type = ARRAY_DOUBLE;
  testArrayRoundTrip("[[]]");
  precision = 1;
  testArrayRoundTrip("[[0.0,1.0],[]]");

  type = ARRAY_CHAR;
  testArrayRoundTrip("[[]]");
  testArrayRoundTrip("[[a,b,c],[1,2,3,4],[),(,*,&,^,)]]");

  type = ARRAY_STRING;
  testArrayRoundTrip("[[]]");
  testArrayRoundTrip("[[hello],[world],[1234567890,!@#$%^&*()]]");

  return testOutput();
}
