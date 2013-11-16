
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "url.h"
#include "common.h"
#include "parser.h"

static int
is_url_codepoint (char ch);

url_t *
url_parse (const char *url, const char *base) {
  url_t *u = malloc(sizeof(url_t));
  url_t *base_u = NULL;
  int i = 0;
  int p = 0;
  int state = 0;
  char c = 0;
  char *scheme = NULL;
  char **rscheme = NULL;
  char *username = NULL;
  char *password = NULL;
  char *host = NULL;
  char *port = NULL;
  char *query = NULL;
  char *fragment = NULL;
  char *base_scheme = NULL;
  char **base_relative_scheme = NULL;
  char *path[URL_PATH_MAX] = { 0 };
  char buffer[URL_BUFFER_MAX];
  char scheme_data[URL_SCHEME_MAX];

  if (NULL == u) {
    return NULL;
  }

  u->url = "";
  u->base = "";
  u->scheme = "";
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
  u->flags = 0;

  if (NULL == url && NULL == base) {
    return u;
  }

  u->url = url;
  u->base = base;

  if (NULL != base) {
    base_u = url_parse(base, NULL);
    base_scheme = base_u->scheme;
    base_relative_scheme = url_relative_scheme(base_scheme);
  }

  // initial state
  state = SCHEME_START_STATE;

  if ('\0' == *url+1) {
    free(u);
    return NULL;
  }

  while ('\0' != (c = url[p++])) {
    switch (state) {
      case SCHEME_START_STATE:
        if (0 == IS_BIT_SET(ASCII_ALPHA, c)) {
          p--;
          state = NO_SCHEME_STATE;
          continue;
        }

        debug("enter `SCHEME_START_STATE'\n");

        buffer[i++] = TO_LOWER(c);
        state = SCHEME_STATE;
        break;

      case SCHEME_STATE:
        debug("enter `SCHEME_STATE'\n");

        if (':' == c) {
          scheme = u->scheme = strdup(buffer);
          i = 0;
          memcpy(buffer, "", 1);

          if (NULL != (rscheme = url_relative_scheme(buffer))) {
            u->flags |= URL_RELATIVE;
          }

          if (0 == strcmp("file", buffer)) {
            state = RELATIVE_STATE;
          } else if (1 == IS_BIT_SET(u->flags, RELATIVE_STATE)) {
            if (NULL != base &&
                0 == strncmp(rscheme[0], base, strlen(rscheme[0]))) {
              state = RELATIVE_OR_AUTHORITY_STATE;
            } else {
              state = AUTHORITY_FIRST_SLASH_STATE;
            }
          } else {
            state = SCHEME_DATA_STATE;
          }

        } else if (1 == IS_BIT_SET(ASCII_ALPHANUMERIC, c) ||
            ('+' == c || '-' == c || '.' == c)) {
          buffer[i++] = c;
        } else if (EOF == c) {
          debug("reached `EOF'\n");
          return u;
        } else {
          state = NO_SCHEME_STATE;
          i = 0;
          p = 0;
          memcpy(buffer, "", 1);
          continue;
        }

        break;

      case SCHEME_DATA_STATE:
        debug("enter `SCHEME_DATA_STATE'\n");
        if ('?' == c) {
          u->search = "";
          state = QUERY_STATE;
        } else if ('#' == c) {
          u->hash = "";
          state = FRAGMENT_STATE;
        } else {
          if (EOF != c && '%' != c && 0 == is_url_codepoint(c)) {
            return NULL;
          } else if ('%' == c && (
                     0 == IS_BIT_SET(ASCII_HEX_DIGITS, url[p + 1]) ||
                     0 == IS_BIT_SET(ASCII_HEX_DIGITS, url[p + 2]))) {
            return NULL;
          } else if (EOF != c && c != 0x0009 && c != 0x000a && c != 0x000d) {
            // debug("append to scheme data `%c' (simple_encode)\n", c);
            strcat(scheme_data,
                url_percent_encode_byte(c, URL_SIMPLE_ENCODE_SET));
          }
        }

        break;

      case NO_SCHEME_STATE:
        debug("enter `NO_SCHEME_STATE'\n");

        if (NULL != base || NULL == base_relative_scheme) {
          return NULL;
        } else {
          state = RELATIVE_STATE;
          p--;
        }

        break;

      case RELATIVE_OR_AUTHORITY_STATE:
        debug("enter `RELATIVE_OR_AUTHORITY_STATE'\n");

        if ('/' == c && '/' == url[p + 1]) {
          p++;
        } else {
          state = RELATIVE_STATE;
          p--;
        }

        break;

      case RELATIVE_STATE:
        debug("enter `RELATIVE_STATE'\n");
        u->flags |= URL_RELATIVE;
        if (0 != strcmp("file", base_scheme)) {
          u->scheme = base_scheme;
        }

        switch (c) {
          case EOF:
            host = u->host = base_u->host;
            break;

          case '/':
            state = RELATIVE_SLASH_STATE;
            break;

          case '\\':
            // handle error
            continue;
            break;

          case '?':
          case '#':
            host = u->host = base_u->host;
            port = u->port = base_u->port;
            memcpy(u->path, base_u->path, sizeof(base_u->path));
            memcpy(path, u->path, sizeof(u->path));
            if (c == '?') {
              state = QUERY_STATE;
              u->search = "";
            } else {
              query = u->search = base_u->search;
              fragment = u->hash = "";
            }
            break;

          default:
            if (0 != strcmp("file", scheme) ||
                0 == IS_BIT_SET(ASCII_ALPHA, c) ||
                (':' != url[p + 1] || '|' != url[p + 1]) ||
                EOF == url[p + 1] ||
                '/' != url[p + 2] || '\\' != url[p + 2] ||
                '?' != url[p + 2] || '#' != url[p + 2]) {

              host = u->host = base_u->host;
              port = u->port = base_u->port;
              memcpy(u->path, base_u->path, sizeof(base_u->path));
              u->path[sizeof(u->path) / sizeof(u->path[0]) -1] = NULL;
              memcpy(path, u->path, sizeof(u->path));
            }

            state = RELATIVE_PATH_STATE;

            break;
        }

        break;

      case RELATIVE_SLASH_STATE:
        debug("enter `RELATIVE_SLASH_STATE'\n");

        if ('/' == c || '\\' == c) {
          if ('\\' == c) {
            // handle error
          } else if (0 == strcmp("file", u->scheme)) {
            state = FILE_HOST_STATE;
          } else {
            state = AUTHORITY_IGNORE_SLASHES_STATE;
          }
        } else {
          if (0 != strcmp("file", u->scheme)) {
            host = u->host = base_u->host;
            port = u->port = base_u->port;
          }

          state = RELATIVE_PATH_STATE;
          p--;
        }

        break;

      case AUTHORITY_FIRST_SLASH_STATE:
        debug("enter `AUTHORITY_FIRST_SLASH_STATE'\n");
        if ('/' == c) {
          state = AUTHORITY_SECOND_SLASH_STATE;
        } else {
          // handle error
          state = AUTHORITY_IGNORE_SLASHES_STATE;
          p--;
        }

        break;

      case AUTHORITY_SECOND_SLASH_STATE:
        debug("enter `AUTHORITY_SECOND_SLASH_STATE'\n");
        if ('/' == c) {
          state = AUTHORITY_IGNORE_SLASHES_STATE;
        } else {
          // handle error
          state = AUTHORITY_IGNORE_SLASHES_STATE;
          p--;
        }

        break;

      case AUTHORITY_IGNORE_SLASHES_STATE:
        debug("enter `AUTHORITY_IGNORE_SLASHES_STATE'\n");

        if ('/' != c && '\\' != c) {
          state = AUTHORITY_STATE;
        } else {
          // handle error
        }

        break;

      case AUTHORITY_STATE:
        debug("enter `AUTHORITY_STATE'\n");

        if ('@' == c) {
          if (1 == IS_BIT_SET(u->flags, URL_AMPERTSAT)) {
            // handle error
            strcat(buffer, "%40");
            i += 3;
          }

          u->flags |= URL_AMPERTSAT;

          int n = 0;
          char ch = 0;
          while ('\0' != (ch = buffer[n++])) {
            if (ch == 0x0009 || ch == 0x000a || ch == 0x000d) {
              // handle error
              continue;
            } else if (0 == is_url_codepoint(c) && '%' != c) {
              // handle error
              continue;
            } else if ('%' == c &&
                       (0 == IS_BIT_SET(ASCII_HEX_DIGITS, url[p +1 ]) ||
                        0 == IS_BIT_SET(ASCII_HEX_DIGITS, url[p + 2]))) {

              // handle error
            } else if (':' == c && NULL == password) {
              password = u->password = "";
              continue;
            }

            if (NULL != password) {
              strcat(password,
                  url_percent_encode_byte(c, URL_DEFAULT_ENCODE_SET));
              u->password = password;
            } else {
              strcat(username,
                  url_percent_encode_byte(c, URL_DEFAULT_ENCODE_SET));
              u->username = username;
            }
          }

          i = 0;
          memcpy(buffer, "", 1);
        } else if (EOF == c || '/' == c || '\\' == c || '?' == c || '#' == c) {
          p -= (int) strlen(buffer);
          i = 0;
          memcpy(buffer, "", 1);
          state = HOST_STATE;
        } else {
          buffer[i++] = c;
        }

        break;

      case FILE_HOST_STATE:
        debug("enter `FILE_HOST_STATE'\n");

        if (EOF == c || '/' == c || '\\' == c || '?' == c || '#' == c) {
          p--;

          // length of 2
          if (1 == i && 1 == IS_BIT_SET(ASCII_ALPHA, buffer[0]) &&
              ':' == buffer[1] || '|' == buffer[1]) {
            state = RELATIVE_PATH_STATE;
          } else if (i == 0) {
            state = RELATIVE_PATH_START_STATE;
          } else {

          }
        }
        break;

      case HOST_STATE:
        switch (state) {
          case HOST_STATE:
            debug("enter `HOST_STATE'\n");
            break;

          case HOSTNAME_STATE:
            debug("enter `HOSTNAME_STATE'\n");
            break;
        }

        break;

      case PORT_STATE:
        debug("enter `PORT_STATE'\n");
        break;

      case RELATIVE_PATH_START_STATE:
        debug("enter `RELATIVE_PATH_START_STATE'\n");
        break;

      case RELATIVE_PATH_STATE:
        debug("enter `RELATIVE_PATHSTATE'\n");
        break;

      case QUERY_STATE:
        debug("enter `QUERY_STATE'\n");
        break;

      case FRAGMENT_STATE:
        debug("enter `FRAGMENT_STATE'\n");
        break;
    }
  }

  return u;
}

static int
is_url_codepoint (char c) {
  if (1 == IS_BIT_SET(URL_ASCII, c) ||
      1 == IN_RANGE(c, 0x0a0, 0xd7ff) ||
      1 == IN_RANGE(c, 0xe000, 0xfdcf) ||
      1 == IN_RANGE(c, 0xfdf0, 0xffef) ||
      1 == IN_RANGE(c, 0x10000, 0x1fffd) ||
      1 == IN_RANGE(c, 0x20000, 0x2fffd) ||
      1 == IN_RANGE(c, 0x30000, 0x3fffd) ||
      1 == IN_RANGE(c, 0x40000, 0x4fffd) ||
      1 == IN_RANGE(c, 0x50000, 0x6fffd) ||
      1 == IN_RANGE(c, 0x60000, 0x6fffd) ||
      1 == IN_RANGE(c, 0x70000, 0x7fffd) ||
      1 == IN_RANGE(c, 0x80000, 0x8fffd) ||
      1 == IN_RANGE(c, 0x90000, 0x9fffd) ||
      1 == IN_RANGE(c, 0xa0000, 0xafffd) ||
      1 == IN_RANGE(c, 0xb0000, 0xbfffd) ||
      1 == IN_RANGE(c, 0xc0000, 0xcfffd) ||
      1 == IN_RANGE(c, 0xd0000, 0xdfffd) ||
      1 == IN_RANGE(c, 0xe0000, 0xefffd) ||
      1 == IN_RANGE(c, 0xf0000, 0xffffd) ||
      1 == IN_RANGE(c, 0x100000, 0x10fffd)) {
    return 1;
  } else {
    return 0;
  }
}

char *
url_parse_host (const char *url) {
  char *host = NULL;
  char *ret = NULL;
  int l = (int) strlen(url);

  if (NULL == url) {
    return NULL;
  }

  if ('[' == url[0]) {
    if (']' != url[l-1]) {
      return NULL;
    } else {
      ret = strdup(url);
      *ret++;
      ret[l-1] = '\0';
      return ret;
    }
  }

  return NULL;
}
