
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "url.h"
#include "common.h"
#include "encode.h"
#include "parser.h"

char *
url_percent_encode (char *str, int set) {
  char *ret = NULL;
  char *byte = NULL;
  char *bytes = NULL;
  int len = strlen(str);
  int i = 0;

  bytes = malloc(sizeof(char) * len);

  for (; i < len; ++i) {
    byte = url_percent_encode_byte(str[i], set);
    strcat(bytes, byte);
  }

  ret = strdup(bytes);
  free(bytes);
  return ret;
}

char *
url_percent_encode_byte (char byte, int set) {
  char enc[64];
  char *c = &byte;

  switch (set) {
    case URL_SIMPLE_ENCODE_SET:
      if (0 == IN_SIMPLE_ENCODE_SET(byte)) {
        goto noset;
      }

      break;

    case URL_DEFAULT_ENCODE_SET:
      if (0 == IN_DEFAULT_ENCODE_SET(byte)) {
        goto noset;
      }

      break;

    case URL_PASSWORD_ENCODE_SET:
      if (0 == IN_PASSWORD_ENCODE_SET(byte)) {
        goto noset;
      }

      break;

    case URL_USERNAME_ENCODE_SET:
      if (0 == IN_USERNAME_ENCODE_SET(byte)) {
        goto noset;
      }

      break;

    default: goto noset;
  }

  if (byte >= 0x041 && byte <= 0x07a) {
    byte = TO_UPPER(byte);
  }

  sprintf(enc, "%s%02X", "%", byte);
  return strdup(enc);

noset:
  c[1] = '\0';
  return c;
}
