
#ifndef __URL_TEST_H__
#define __URL_TEST_H__ 1

#include <assert.h>

#define TEST_STRING(x) #x

#define TEST(fn)                                                               \
  URL_EXTERN int url_test_##fn ();

#define TEST_IMPL(fn)                                                          \
  int url_test_##fn ()

#define TEST_RUN(fn) {                                                         \
  assert(0 == url_test_##fn());                                                \
  printf("test: `%s' ok\n", TEST_STRING(fn));                                  \
}


/* tests */
TEST(version)
TEST(schemes)

#endif
