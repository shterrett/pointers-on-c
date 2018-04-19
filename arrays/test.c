#include "minunit.h"
#include <stdarg.h>
#include <assert.h>

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

int array_offset(int array_info[], ...) {
  int dim = array_info[0];
  int lower_bound(int d) {
    return array_info[2 * d + 1];
  }
  int upper_bound(int d) {
    return array_info[2 * d + 2];
  }
  int dim_size(int d) {
    if (d == 0) {
      return 1;
    } else {
      return upper_bound(d) - lower_bound(d) + 1;
    }
  }

  assert(dim > 0);
  assert(dim <= 10);
  int bounds = 0;
  for (; bounds < dim; bounds++) {
    assert(lower_bound(bounds) <= upper_bound(bounds));
  }
  assert(bounds == dim);

  int idxs[10];
  int num_idx = 0;
  va_list vl;
  va_start(vl, array_info);
  for (; num_idx < dim; num_idx++) {
    idxs[num_idx] = va_arg(vl, int);
    assert(idxs[num_idx] >= lower_bound(num_idx));
    assert(idxs[num_idx] <= upper_bound(num_idx));
  }

  assert(num_idx == dim);

  int offset = 0;
  for (int d = 0; d < dim; d++) {
    offset = offset * dim_size(d) + (idxs[d] - lower_bound(d));
  }

  return offset;
}

int threatens(int r_1, int c_1, int r_2, int c_2) {
  int same_diagonal = (r_2 - r_1) == (c_2 - c_1);
  return r_1 == r_2 || c_1 == c_2 || same_diagonal;
}

int is_threatened(int board[8][8], int row, int col) {
  int threat = 0;
  for (int r = 0; r < 8; r++) {
    for (int c = 0; c < 8; c++) {
      if (board[r][c] == 1) {
        threat = threat || threatens(r, c, row, col);
      }
    }
  }

  return threat;
}

void print_queens(int board[8][8]) {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      putchar('|');
      if (board[row][col]) {
        putchar('*');
      } else {
        putchar(' ');
      }
    }
    printf("|\n");
  }
}

int eight_queens(int board[8][8], int next_row) {
  if (next_row >= 8) {
    return 1;
  }

  for (int col = 0; col < 8; col++) {
    if (!is_threatened(board, next_row, col)) {
      board[next_row][col] = 1;
      if (eight_queens(board, next_row + 1)) {
        return 1;
      } else {
        board[next_row][col] = 0;
      }
    }
  }
  return 0;
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

char *test_array_offset(void) {
  int array_info[7] = { 3, 4, 6, 1, 5, -3, 3 };

  mu_assert(array_offset(array_info, 4, 1, -3) == 0, "Offset 4, 1, -3 failed");
  mu_assert(array_offset(array_info, 4, 1, -2) == 1, "Offset 4, 1, -2 failed");
  mu_assert(array_offset(array_info, 4, 1, 3) == 6, "Offset 4, 1, 3 failed");
  mu_assert(array_offset(array_info, 4, 2, -3) == 7, "Offset 4, 2, -3 failed");
  mu_assert(array_offset(array_info, 5, 1, -3) == 35, "Offset 5, 1, -3 failed");
  mu_assert(array_offset(array_info, 6, 3, 1) == 88, "Offset 6, 3, 1 failed");

  return NULL;
}

char *test_is_threatened(void) {
  int board[8][8];
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      board[i][j] = 0;
    }
  }

  board[1][3] = 1;
  mu_assert(is_threatened(board, 1, 6) == 1, "Same row is threatened");
  mu_assert(is_threatened(board, 4, 3) == 1, "Same column is threatened");
  mu_assert(is_threatened(board, 4, 6) == 1, "On diagonal is threatened");
  mu_assert(is_threatened(board, 4, 5) == 0, "Off diagonal is not threatened");

  return NULL;
}

char *test_eight_queens(void) {
  int board[8][8];
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      board[i][j] = 0;
    }
  }
  mu_assert(eight_queens(board, 0) == 1, "Queens not placed successfully");
  print_queens(board);

  return NULL;
}

char *all_tests() {
  mu_suite_start();
  mu_run_test(test_single_tax);
  mu_run_test(test_matrix_multiply);
  mu_run_test(test_array_offset);
  mu_run_test(test_is_threatened);
  mu_run_test(test_eight_queens);

  return NULL;
}

RUN_TESTS(all_tests);
