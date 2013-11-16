
#include <stdio.h>
#include "schemes.h"

char **
url_relative_scheme (const char *scheme) {
  int i = 0;
  int len = sizeof(_url_relative_schemes) / sizeof(_url_relative_schemes[0]);
  char **item;

  while (i < len && NULL != (item = _url_relative_schemes[i++])) {
    if (0 == strncmp(scheme, item[0], strlen(scheme))) {
      return item;
    }
  }

  return NULL;
}
