
#ifndef __URL_SCHEME_H__
#define __URL_SCHEME_H__ 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

static char *_url_relative_schemes[][2] = {
    {"ftp", "21"}
  , {"file", NULL}
  , {"gopher", "70"}
  , {"http", "80"}
  , {"https", "443"}
  , {"ws", "80"}
  , {"wss", "443"}
};

#endif
