
#ifndef __URL_PARSER_H__
#define __URL_PARSER_H__ 1

/**
 * Defines code points for ASCII whitespace characters
 * http://encoding.spec.whatwg.org/#ascii-whitespace
 */

#define ASCII_WHITESPACE (                                                     \
  (0x09) | (0x0a) | (0x0c) | (0x0d) | (0x020)                                  \
)

/**
 * Defines code points for ASCII digits
 * http://encoding.spec.whatwg.org/#ascii-digits
 */

#define ASCII_DIGITS (                                                         \
  (0x030) | (0x031) | (0x032) | (0x033) | (0x034) | (0x035) | (0x036) |        \
  (0x037) | (0x038) | (0x039)                                                  \
)

/**
 * Defines code points for ASCII hex digits
 * http://url.spec.whatwg.org/#ascii-hex-digits
 */

#define ASCII_HEX_DIGITS (                                                     \
  (ASCII_DIGITS) |                                                             \
  (0x041) | (0x042) | (0x043) | (0x44) | (0x045) | (0x046) |                   \
  (0x061) | (0x062) | (0x063) | (0x64) | (0x065) | (0x066)                     \
)

/**
 * Defines code points for ASCII alpha
 * http://url.spec.whatwg.org/#ascii-alpha
 */

#define ASCII_ALPHA (                                                          \
  (0x041) | (0x042) | (0x043) | (0x044) |                                      \
  (0x045) | (0x046) | (0x047) | (0x046) |                                      \
  (0x047) | (0x048) | (0x049) | (0x050) |                                      \
  (0x051) | (0x052) | (0x053) | (0x054) |                                      \
  (0x055) | (0x056) | (0x057) | (0x058) |                                      \
  (0x059) | (0x05a) | (0x061) | (0x062) |                                      \
  (0x063) | (0x064) | (0x065) | (0x066) |                                      \
  (0x067) | (0x068) | (0x069) | (0x070) |                                      \
  (0x071) | (0x072) | (0x073) | (0x074) |                                      \
  (0x075) | (0x076) | (0x077) | (0x078) |                                      \
  (0x079) | (0x07a)                                                            \
)

/**
 * Defines code points for ASCII alphanumeric
 * http://url.spec.whatwg.org/#ascii-alphanumeric
 */

#define ASCII_ALPHANUMERIC (                                                   \
  (ASCII_DIGITS) | (ASCII_ALPHA)                                               \
)

/**
 * Defines code points for domain label separators
 * http://url.spec.whatwg.org/#domain-label-separators
 */

#define DOMAIN_LEVEL_SEPARATORS (                                              \
  (0x02e) | (0x3002) | (0xff0e) | (0xff61)                                     \
)

/**
 * Defines code points for a url
 * http://url.spec.whatwg.org/#url-code-points
 */

#define URL_ASCII (                                                            \
  (ASCII_ALPHANUMERIC) |                                                       \
  '!' | '$' | '&' | '\''| '(' | ')' | '*' |                                    \
  '+' | ',' | '-' | '.' | '/' | ':' | ';' |                                    \
  '=' | '?' | '@' | '_' | '~'                                                  \
)


/**
 * Defines the scheme start state
 * http://url.spec.whatwg.org/#scheme-start-state
 */

#define SCHEME_START_STATE 0x01

/**
 * Defines the scheme state
 * http://url.spec.whatwg.org/#scheme-state
 */

#define SCHEME_STATE 0x02

/**
 * Defines the scheme data state
 * http://url.spec.whatwg.org/#scheme-data-state
 */

#define SCHEME_DATA_STATE 0x03

/**
 * Defines the no scheme state
 * http://url.spec.whatwg.org/#scheme-data-state
 */

#define NO_SCHEME_STATE 0x04

/**
 * Defines the relative or authority state
 * http://url.spec.whatwg.org/#relative-or-authority-state
 */
#define RELATIVE_OR_AUTHORITY_STATE 0x05

/**
 * Defines the relative state
 * http://url.spec.whatwg.org/#relative-state
 */

#define RELATIVE_STATE 0x06

/**
 * Defines the relative slash state
 * http://url.spec.whatwg.org/#relative-slash-state
 */

#define RELATIVE_SLASH_STATE 0x07

/**
 * Defines the authority first slash state
 * http://url.spec.whatwg.org/#authority-first-slash-state
 */

#define AUTHORITY_FIRST_SLASH_STATE 0x08

/**
 * Defines the authority second slash state
 * http://url.spec.whatwg.org/#authority-second-slash-state
 */

#define AUTHORITY_SECOND_SLASH_STATE 0x09

/**
 * Defines the authority ignore slashes state
 * http://url.spec.whatwg.org/#authority-ignore-slashes-state
 */

#define AUTHORITY_IGNORE_SLASHES_STATE 0x0a

/**
 * Defines the authority state
 * http://url.spec.whatwg.org/#authority-state
 */

#define AUTHORITY_STATE 0x0b

/**
 * Defines the file host state
 * http://url.spec.whatwg.org/#file-host-state
 */

#define FILE_HOST_STATE 0x0c

/**
 * Defines the host state
 * http://url.spec.whatwg.org/#host-state
 */

#define HOST_STATE 0x0d

/**
 * Defines the hostname state
 * http://url.spec.whatwg.org/#hostname-state
 */

#define HOSTNAME_STATE 0x0e

/**
 * Defines the port state
 * http://url.spec.whatwg.org/#port-state
 */

#define PORT_STATE 0x0f

/**
 * Defiens the relative path tart state
 * http://url.spec.whatwg.org/#relative-path-start-state
 */

#define RELATIVE_PATH_START_STATE 0x10

/**
 * Defines the relative path state
 * http://url.spec.whatwg.org/#relative-path-state
 */

#define RELATIVE_PATH_STATE 0x11

/**
 * Defines the query state
 * http://url.spec.whatwg.org/#query-state
 */

#define QUERY_STATE 0x12

/**
 * Defines the fragment state
 * http://url.spec.whatwg.org/#fragment-state
 */

#define FRAGMENT_STATE 0x13

/**
 * Checks if a bit is in range of
 * two hex valuese
 */

#define IN_RANGE(c, a, b) (                                                    \
  (c >= a) && (c <= b)                                                         \
) ? 1 : 0

#endif
