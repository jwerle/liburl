
#ifndef __URL_H__
#define __URL_H__ 1

#if __GNUC__ >= 4
# define URL_EXTERN __attribute__((visibility("default")))
#else
# define URL_EXTERN
#endif

#define URL_STRINGIFY_HELPER(x) #x
#define URL_STRINGIFY(x) URL_STRINGIFY_HELPER(x)

URL_EXTERN char **
url_scheme (const char *scheme);

URL_EXTERN unsigned int
url_version ();

URL_EXTERN const char *
url_version_string ();

#endif
