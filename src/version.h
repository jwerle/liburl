
#ifndef __URL_VERSION_H__
#define __URL_VERSION_H__ 1

#include "url.h"

#define URL_VERSION_MAJOR 0
#define URL_VERSION_MINOR 0
#define URL_VERSION_PATCH 1

#define URL_VERSION (                                                          \
    (URL_VERSION_MAJOR << 16) |                                                \
    (URL_VERSION_MINOR << 8) |                                                 \
    (URL_VERSION_PATCH)                                                        \
)

#define URL_VERSION_STRING (                                                   \
    URL_STRINGIFY(URL_VERSION_MAJOR) "."                                       \
    URL_STRINGIFY(URL_VERSION_MINOR) "."                                       \
    URL_STRINGIFY(URL_VERSION_PATCH)                                           \
)

#if URL_IS_RELEASE
#define URL_VERSION_RELEASE URL_VERSION_STRING
#else
#define URL_VERSION_RELEASE URL_VERSION_STRING "-pre"
#endif

#endif
