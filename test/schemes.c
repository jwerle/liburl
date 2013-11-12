
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <url.h>
#include <assert.h>
#include "test.h"

// implements http://url.spec.whatwg.org/#relative-scheme
TEST_IMPL(schemes) {
  char **scheme = NULL;

  scheme = url_scheme("ftp");
  assert(0 == strcmp("ftp", scheme[0]));
  assert(0 == strcmp("21", scheme[1]));

  scheme = url_scheme("file");
  assert(0 == strcmp("file", scheme[0]));
  assert(NULL == scheme[1]);

  scheme = url_scheme("gopher");
  assert(0 == strcmp("gopher", scheme[0]));
  assert(0 == strcmp("70", scheme[1]));

  scheme = url_scheme("http");
  assert(0 == strcmp("http", scheme[0]));
  assert(0 == strcmp("80", scheme[1]));

  scheme = url_scheme("https");
  assert(0 == strcmp("https", scheme[0]));
  assert(0 == strcmp("443", scheme[1]));

  scheme = url_scheme("ws");
  assert(0 == strcmp("ws", scheme[0]));
  assert(0 == strcmp("80", scheme[1]));

  scheme = url_scheme("wss");
  assert(0 == strcmp("wss", scheme[0]));
  assert(0 == strcmp("443", scheme[1]));
  return 0;
}
