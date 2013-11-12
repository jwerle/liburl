
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <url.h>
#include <assert.h>
#include "test.h"

TEST_IMPL(version) {
  assert(0 != url_version());
  assert(url_version_string());
  printf("liburl version: `%d' (v%s)\n", url_version(), url_version_string());
  return 0;
}
