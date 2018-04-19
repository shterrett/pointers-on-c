#include "minunit.h"

float single_tax(float income) {
  float max_income[5] = { 23350, 56550, 117950, 256500, -1 };
  float base_tax[5] = { 0, 3502.5, 12798.5, 31832.5, 81710.5 };
  float percentage[5] = { 0.15, 0.28, 0.31, 0.36, 0.396 };

  int idx = 0;
  while (idx < 5 && max_income[idx] > 0 && income >= max_income[idx]) {
    idx++;
  }
  float at_rate;
  if (idx == 0) {
    at_rate = income;
  } else {
    at_rate = income - max_income[idx - 1];
  }

  return base_tax[idx] + (percentage[idx] * at_rate);
}

// m1 is an x by y matrix
// m2 is a y by z matrix
// the result, an x by z matrix, will be stored in r
void matrix_multiply(int *m1, int *m2, int *r, int x, int y, int z) {
  for (int outer_row = 0; outer_row < x; outer_row++) {
    for (int outer_col = 0; outer_col < z; outer_col++) {
      int sum = 0;
      for (int inner = 0; inner < y; inner++) {
        sum += *(m1 + (outer_row * y) + inner) * *(m2 + (inner * z) + outer_col);
      }
      *(r + (outer_row * z) + outer_col) = sum;
    }
  }
}

char *test_single_tax(void) {
  mu_assert(single_tax(20000) == 0.15 * 20000, "Incorrect calculation");
  mu_assert(single_tax(40000) == 3502.5 + (0.28 * (40000 - 23350)), "Incorrect calculation");
  mu_assert(single_tax(100000) == 12798.5 + (0.31 * (100000 - 56550)), "Incorrect calculation");
  mu_assert(single_tax(200000) == 31832.5 + (0.36 * (200000 - 117950)), "Incorrect calculation");
  mu_assert(single_tax(400000) == 81710.50 + (0.396 * (400000 - 256500)), "Incorrect calculation");

  return NULL;
}

char *test_matrix_multiply(void) {
  int mat_1[3][2] = {
    { 2, -6 },
    { 3, 5 },
    { 1, -1 }
  };
  int mat_2[2][4] = {
    { 4, -2, -4, -5 },
    { -7, -3, 6, 7 }
  };
  int r[3][4];

  matrix_multiply(mat_1[0], mat_2[0], r[0], 3, 2, 4);

  int res[3][4] = {
    { 50, 14, -44, -52 },
    { -23, -21, 18, 20 },
    { 11, 1, -10, -12 }
  };

  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 4; col++) {
      mu_assert(r[row][col] == res[row][col], "Matrix elements not equal");

    }
  }

  return NULL;
}

char *all_tests() {
  mu_suite_start();
  mu_run_test(test_single_tax);
  mu_run_test(test_matrix_multiply);

  return NULL;
}

RUN_TESTS(all_tests);
