#include "linked-list.h"
#include "../test.h"

int main(void) {
  char *str = "2147483647 -> 0 -> -2147483648";

  struct ListNode* node = linkedlistNewByStr(str);
  char *node_str = linkedlistToString(node);
  EXPECT_EQ_STRING(str, node_str);

  free(node_str);
  linkedlistFree(node);
  return testOutput();
}
