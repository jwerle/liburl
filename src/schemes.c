
#include "common.h"
#include "schemes.h"

char **
url_scheme (const char *scheme) {
  int i = 0;
  char **item;

  while (NULL != (item = _url_schemes[i++])) {
    if (0 == strncmp(scheme, item[0], strlen(scheme))) {
      return item;
    }
  }

  return NULL;
}
