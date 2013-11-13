
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <url.h>
#include "test.h"

int
main (void) {
  printf("\n");

  TEST_RUN(version);
  TEST_RUN(common);
  TEST_RUN(relative_schemes);
  TEST_RUN(parser);

  return 0;
}


