
#ifndef __URL_COMMON_H__
#define __URL_COMMON_H__ 1

#if __GNUC__ >= 4
# define URL_EXTERN __attribute__((visibility("default")))
#else
# define URL_EXTERN /* nothing */
#endif

#endif
