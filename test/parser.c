
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <url.h>
#include <assert.h>
#include "test.h"

TEST_IMPL(parser) {
  char *url =
    "http://user:pass@subdomain.host.com:8080/p/a/t/h?query=string#hash";

  url_t *u = url_parse(url, NULL);
  assert(u);

  //url_inspect(u);

  return 0;
}
