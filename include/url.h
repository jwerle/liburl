
#ifndef __URL_H__
#define __URL_H__ 1

#if __GNUC__ >= 4
# define URL_EXTERN __attribute__((visibility("default")))
#else
# define URL_EXTERN
#endif

#define URL_STRINGIFY_HELPER(x) #x
#define URL_STRINGIFY(x) URL_STRINGIFY_HELPER(x)


/**
 * Defines the `URLUtils' interface
 * which implements 'http://url.spec.whatwg.org/#api'
 */

#define IURL_FIELDS                                                            \
  const char *href;                                                            \
  const char *origin;                                                          \
  const char *protocol;                                                        \
  const char *username;                                                        \
  const char *password;                                                        \
  const char *host;                                                            \
  const char *hostname;                                                        \
  const char *port;                                                            \
  const char *pathname;                                                        \
  const char *search;                                                          \
  const char *hash;                                                            \

/**
 * Defines a `url_t' type that implements the `URL' interface
 */

typedef struct url_s {
  IURL_FIELDS
  const char *url;
  const char *base;
  char **scheme;
  int flags;
} url_t;

/**
 * Returns an array containing a relative scheme where the name is
 * at subscript '0' and the port is at subscript '1'
 *
 * The following example will print the scheme name for 'https' and
 * its associated default port '443':
 *
 * char **https = url_relative_scheme("https");
 * printf("%s %d\n", https[0], https[1]);
 */

URL_EXTERN char **
url_relative_scheme (const char *scheme);

/**
 * This will return an `unsigned int' representing the
 * version of the library
 */

URL_EXTERN unsigned int
url_version ();

/**
 * This will return the string representation of the
 * version of the library in the following format:
 *
 * `MAJOR.MINOR.PATCH'
 */

URL_EXTERN const char *
url_version_string ();

/**
 * Parses a given url string into a `url_t' structure
 */

URL_EXTERN url_t *
url_parse (const char *url, const char *base);

/**
 * Serializes a given `url_t' structure into a valid
 * url
 */

URL_EXTERN char *
url_serialize (url_t *url);

/**
 * Frees a `url_t'
 */

URL_EXTERN void
url_free (url_t *url);

/**
 * Prints useful information to
 * stdout about a `url_t' structure
 */

URL_EXTERN void
url_inspect (url_t *url);

#endif
