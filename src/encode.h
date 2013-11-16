
#ifndef __URL_ENCODE_H__
#define __URL_ENCODE_H__ 1

#define URL_PERCENT_ENCODE_BYTE 0x025

#define IN_SIMPLE_ENCODE_SET(c) (                                              \
  (c < 0x020) || (c > 0x07e)                                                   \
) ? 1 : 0

#define IN_DEFAULT_ENCODE_SET(c) (                                             \
  (IN_SIMPLE_ENCODE_SET(c)) || (c == 0x020) ||                                 \
  (c == '"') || (c == '#') || (c == '<') ||                                    \
  (c == '>') || (c == '?') || (c == '`')                                       \
) ? 1 : 0

#define IN_PASSWORD_ENCODE_SET(c) (                                            \
  (IN_DEFAULT_ENCODE_SET(c)) ||                                                \
  (c == '/') || (c == '@') || (c == '\\')                                      \
) ? 1 : 0

#define IN_USERNAME_ENCODE_SET(c) (                                            \
  (IN_PASSWORD_ENCODE_SET(c)) || (c == ':')                                    \
) ? 1 : 0

#endif
