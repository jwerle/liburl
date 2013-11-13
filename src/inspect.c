
#include <stdio.h>
#include "url.h"

void
url_inspect (url_t *url) {
  printf("#url('%s') =>\n", url->url);
  printf("  base: '%s'\n", url->base);
  printf("  href: '%s'\n", url->href);
  printf("  origin: '%s'\n", url->origin);
  printf("  protocol: '%s'\n", url->protocol);
  printf("  username: '%s'\n", url->username);
  printf("  password: '%s'\n", url->password);
  printf("  host: '%s'\n", url->host);
  printf("  hostname: '%s'\n", url->hostname);
  printf("  port: '%s'\n", url->port);
  printf("  pathname: '%s'\n", url->pathname);
  printf("  search: '%s'\n", url->search);
  printf("  hash: '%s'\n", url->hash);
  //printf("  scheme[2]: {'%s', '%s'}\n", url->scheme[0], url->scheme[1]);

  printf("\n");
}
