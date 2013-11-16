
#ifndef __URL_COMMON_H__
#define __URL_COMMON_H__ 1

/**
 * Returns '0' or '1' whether
 * a bit `b' is set in `n'
 */

#define IS_BIT_SET(n, b) (b == (n & b)) ? 1 : 0

/**
 * Converts a char to lower case
 */

#define TO_LOWER(c) (c | 0x60)

/**
 * Converts a char to upper case
 */

#define TO_UPPER(c) (c & ~(0x01 << 0x05))

/**
 * Outputs to stdout if `URL_DEBUG' is defined
 */

#ifdef URL_DEBUG
#define debug printf
#else
#define debug(...) /* noop */
#endif

#endif
