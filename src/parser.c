
#include <stdlib.h>
#include <stdio.h>
#include "url.h"
#include "common.h"
#include "parser.h"

url_t *
url_parse (const char *url, const char *base) {
  url_t *u = malloc(sizeof(url_t));
  int i = 0;
  int state = 0;
  char c = 0;
  char buffer[256];

  if (NULL == u) {
    return NULL;
  }

  /**
   * State flags can be stored here and can be
   * retrieved with a bis mask
   */

  u->flags = 0;

  /**
   * If `url' and `base' are both `NULL'
   * then set member properties to an
   * empty string and return `url_t'
   * structure
   */

  if (NULL == url && NULL == base) {
    u->url = "";
    u->base = "";
    u->href = "";
    u->origin = "";
    u->protocol = "";
    u->username = "";
    u->password = "";
    u->host = "";
    u->hostname = "";
    u->port = "";
    u->pathname = "";
    u->search = "";
    u->hash = "";

    return u;
  }

  u->url = url;
  u->base = base;

  // initial state
  state = SCHEME_START_STATE;

  if ('\0' == *url+1) {
    return NULL;
  }

  while ('\0' != (c = *url++)) {
    switch (state) {
      case SCHEME_START_STATE:
        if (0 == IS_BIT_SET(ASCII_ALPHA, c)) {
          debug("bad scheme start state\n");
          return NULL;
        }

        debug("enter `SCHEME_START_STATE'\n");

        buffer[i++] = TO_LOWER(c);
        state = SCHEME_STATE;
        break;

      case SCHEME_STATE:
        if (0 == IS_BIT_SET(ASCII_ALPHANUMERIC, c)) {
          debug("bad scheme state\n");
          return NULL;
        }

        debug("enter `SCHEME_STATE'\n");

        if ('+' == c || '-' == c || '.' == c) {
        }

        break;
    }
  }

  return u;
}
