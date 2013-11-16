
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <url.h>
#include <assert.h>
#include "test.h"

TEST_IMPL(encode) {
  char *enc = url_percent_encode("encode=this&encode that&don't forget this",
              URL_DEFAULT_ENCODE_SET);

  assert(enc);

  assert(0 == strcmp(enc,
        "encode=this&encode%20that&don\'t%20forget%20this"));

  assert(0 ==
      strcmp("%20", url_percent_encode_byte(' ', URL_DEFAULT_ENCODE_SET)));

  return 0;
}
