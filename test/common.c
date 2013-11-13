
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <url.h>
#include <assert.h>
#include "../src/common.h"
#include "test.h"

TEST_IMPL(common) {
  int i = 0;
  i |= 5;

  assert(1 == IS_BIT_SET(i, 5));
  assert(0 == IS_BIT_SET(i, 15));

  assert('A' == TO_UPPER('a'));
  assert('b' == TO_LOWER('B'));

  return 0;
}
