#include "minunit.h"

char *test_it_runs() {
  mu_assert(1 == 1, "WTF?");

  return NULL;
}

char *all_tests() {
  mu_suite_start();
  mu_run_test(test_it_runs);

  return NULL;
}

RUN_TESTS(all_tests);
