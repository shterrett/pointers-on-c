#include "minunit.h"
#include <string.h>

typedef int (*comparer)(void *v_1, void *v_2);

int int_cmp(void *i_1, void *i_2) {
  return *(int *)i_1 - *(int *)i_2;
}

int int_cmp_rev(void *i_1, void *i_2) {
  return *(int *)i_2 - *(int *)i_1;
}

int strcmp1(void *s_1, void *s_2) {
  return strcmp((char *)s_1, (char *)s_2);
}

void sort(void **arr, int length, int item_size, comparer cmp_fn) {
  if (length == 1) { return; }

  int front_length = length / 2;
  int back_length = length - front_length;
  void **front = arr;
  void **back = arr + (front_length);
  sort(front, front_length, item_size, cmp_fn);
  sort(back, back_length, item_size, cmp_fn);

  void **f = front;
  int f_i = 0;
  void **b = back;
  int b_i = 0;
  void **sorted = malloc(length * item_size);
  for (void **next = sorted; next < sorted + length; next++) {
    if (f_i >= front_length) {
      memcpy(next, b, item_size);
      b++;
      b_i++;
    } else if (b_i >= back_length) {
      memcpy(next, f, item_size);
      f++;
      f_i++;
    } else {
      if (cmp_fn(*f, *b) <= 0) {
        memcpy(next, f, item_size);
        f++;
        f_i++;
      } else {
        memcpy(next, b, item_size);
        b++;
        b_i++;
      }
    }
  }

  memcpy(arr, sorted, length * item_size);
}

char *test_forward_cmp(void) {
  int one = 1;
  int two = 2;
  int other_two = 2;
  mu_assert(int_cmp((void *)&one, (void *)&two) < 0,
      "First value less than second should be negative");
  mu_assert(int_cmp((void *)&two, (void *)&one) > 0,
      "First value greater than second should be positive");
  mu_assert(int_cmp((void *)&two, (void *)&other_two) == 0,
      "First value equal to second should be zero");

  return NULL;
}

char *test_backward_cmp(void) {
  int one = 1;
  int two = 2;
  int other_two = 2;
  mu_assert(int_cmp_rev((void *)&one, (void *)&two) > 0,
      "First value less than second should be positive");
  mu_assert(int_cmp_rev((void *)&two, (void *)&one) < 0,
      "First value greater than second should be negative");
  mu_assert(int_cmp_rev((void *)&two, (void *)&other_two) == 0,
      "First value equal to second should be zero");

  return NULL;
}

int zero = 0;
int one = 1;
int two = 2;
int three = 3;
int four = 4;
int five = 5;
int six = 6;
int seven = 7;
int eight = 8;
int nine = 9;

char *test_forward_sort(void) {
  int **unsorted_array = malloc(10 * sizeof(int *));
  int **curr = unsorted_array;
  *curr = &five; curr++;
  *curr = &two; curr++;
  *curr = &three; curr++;
  *curr = &seven; curr++;
  *curr = &nine; curr++;
  *curr = &six; curr++;
  *curr = &one; curr++;
  *curr = &eight; curr++;
  *curr = &zero; curr++;
  *curr = &four;

  sort((void **)unsorted_array, 10, sizeof(int *), int_cmp);
  for (int i = 0; i < 10; i++) {
    mu_assert(**unsorted_array == i, "Array not sorted");
    unsorted_array++;
  }

  return NULL;
}

char *test_backward_sort(void) {
  int **unsorted_array = malloc(10 * sizeof(int *));
  int **curr = unsorted_array;
  *curr = &five; curr++;
  *curr = &two; curr++;
  *curr = &three; curr++;
  *curr = &seven; curr++;
  *curr = &nine; curr++;
  *curr = &six; curr++;
  *curr = &one; curr++;
  *curr = &eight; curr++;
  *curr = &zero; curr++;
  *curr = &four;

  sort((void **)unsorted_array, 10, sizeof(int *), int_cmp_rev);
  for (int i = 9; i >= 0; i--) {
    mu_assert(**unsorted_array == i, "Array not sorted");
    unsorted_array++;
  }

  return NULL;
}

char *test_sort_strings(void) {
  char **unsorted_array = malloc(3 * sizeof(char *));
  char **curr = unsorted_array;
  *curr = "hi"; curr++;
  *curr = "bye"; curr++;
  *curr = "aye";

  sort((void **)unsorted_array, 3, sizeof(char *), strcmp1);
  char **sorted = unsorted_array;
  mu_assert(strcmp(*sorted, "aye") == 0, "Array not sorted");
  sorted++;
  mu_assert(strcmp(*sorted, "bye") == 0, "Array not sorted");
  sorted++;
  mu_assert(strcmp(*sorted, "hi") == 0, "Array not sorted");

  return NULL;
}

char *all_tests(void) {
  mu_suite_start();
  mu_run_test(test_forward_cmp);
  mu_run_test(test_backward_cmp);
  mu_run_test(test_forward_sort);
  mu_run_test(test_backward_sort);
  mu_run_test(test_sort_strings);
  return NULL;
}

RUN_TESTS(all_tests);
