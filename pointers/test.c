#include "minunit.h"

// Find the first character in the source string that matches
// any character in the chars string
char const *find_char(char const *source, char const *chars) {
  char const *haystack = source;
  char const *needle;

  while (*haystack != '\0') {
    needle = chars;

    while (*needle != '\0') {
      if (*needle == *haystack) {
        return haystack;
      } else {
        needle++;
      }
    }

    haystack++;
  }
  return NULL;
}

int del_substr(char *str, char const *substr) {
  char *new_str = malloc(strlen(str) * sizeof(char));
  char *new_curr = new_str;
  char *start = str;
  char *end;
  char const *substart;

  while (*start != '\0') {
    if (*start == *substr) {
      substart = substr;
      end = start;
      while (*substart == *end) {
        substart++;
        end++;
      }

      if (*substart == '\0') {
        while (*end != '\0') {
          memcpy(new_curr, end, 1);
          new_curr++;
          start++;
          end++;
        }
        *new_curr = '\0';
        str = new_str;
        return strlen(substr);
      } else {
        memcpy(new_curr, start, 1);
        start++;
        new_curr++;
      }
    } else {
      memcpy(new_curr, start, 1);
      start++;
      new_curr++;
    }
  }

  return 0;
}

void reverse_string(char *str) {
  char *start = str;
  char *end = str;
  while (*(end + 1) != '\0') {
    end++;
  }
  char *tmp = malloc(sizeof(char));

  while (start < end) {
    memcpy(tmp, start, 1);
    memcpy(start, end, 1);
    memcpy(end, tmp, 1);
    start++;
    end--;
  }
}

char *test_find_char_exists() {
  char *haystack = "ABCDEFG";
  char *needle = "XRCQTD";

  char const *found = find_char(haystack, needle);
  mu_assert(*found == 'C', "Failed to find C in ABCDEF");
  mu_assert(found == haystack + 2, "Does not reference proper memory location");

  return NULL;
}

char *test_find_char_does_not_exist() {
  char *haystack = "ABCDEFG";
  char *needle = "HIJKLMN";

  char const *found = find_char(haystack, needle);
  mu_assert(found == NULL, "Should have found nothing");

  return NULL;
}

char *test_del_substring_not_present() {
  char *str = "ABCDEFG";
  mu_assert(0 == del_substr(str, "FGH"), "Deleted nonexistent substring");
  mu_assert(0 == del_substr(str, "CDF"), "Deleted nonexistent substring");
  mu_assert(0 == del_substr(str, "XABC"), "Deleted nonexistent substring");
  mu_assert(strncmp(str, "ABCDEFG", 7) == 0, "String improperly mutated");

  return NULL;
}

char *test_del_substring_removes_first_occurance() {
  char *str = "ABCDABC";
  int del = del_substr(str, "ABC");
  mu_assert(3 == del, "Deleted the wrong amount");
  mu_assert(strncmp(str, "DABC", 4), "Deleted the wrong amount");

  return NULL;
}

char *test_del_substring_in_middle() {
  char *str = "ABCDEFGHI";
  int del = del_substr(str, "DEF");
  mu_assert(3 == del, "Deleted the wrong amount");
  mu_assert(strncmp(str, "ABCGHI", 4), "Deleted the wrong amount");

  return NULL;
}

char *test_reverse_string() {
  char *one = malloc(sizeof(char) * 8);
  char *abcdefg = "ABCDEFG";
  strncpy(one, abcdefg, 8);
  char *two = malloc(sizeof(char) * 3);
  char *hi = "HI";
  strncpy(two, hi, 3);
  char *three = malloc(sizeof(char) * 1);
  char *empty = "";
  strncpy(three, empty, 1);

  reverse_string(one);
  mu_assert(strncmp("GFEDCBA", one, 7) == 0, "Failed to reverse ABCDEFG");
  reverse_string(two);
  mu_assert(strncmp("IH", two, 2) == 0, "Failed to reverse HI");
  reverse_string(three);
  mu_assert(strncmp("", three, 1) == 0, "Failed to reverse \"\"");

  return NULL;
}

char *all_tests() {
  mu_suite_start();
  mu_run_test(test_find_char_exists);
  mu_run_test(test_find_char_does_not_exist);
  mu_run_test(test_del_substring_not_present);
  mu_run_test(test_del_substring_removes_first_occurance);
  mu_run_test(test_del_substring_in_middle);
  mu_run_test(test_reverse_string);

  return NULL;
}

RUN_TESTS(all_tests);
