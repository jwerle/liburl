
#ifndef __URL_TEST_H__
#define __URL_TEST_H__ 1

#include <assert.h>

#define TEST_STRING(x) #x

#define TEST(fn)                                                               \
  URL_EXTERN int url_test_##fn ()

#define TEST_IMPL(fn)                                                          \
  int url_test_##fn ()

#define TEST_RUN(fn) {                                                         \
  printf("run: `%s'\n", TEST_STRING(fn));                                      \
  assert(0 == url_test_##fn());                                                \
  printf("[status]: ok\n\n");                                                  \
}


/* tests */
TEST(common);
TEST(version);
TEST(relative_schemes);
TEST(parser);

#endif
