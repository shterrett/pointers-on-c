#include "minunit.h"
#include <ctype.h>
#include <string.h>

void downcase(char *str) {
  for (char *c = str; *c != '\0'; c++) {
    *c = tolower(*c);
  }
}

int prepare_key(char *key) {
  char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
  downcase(key);

  char cipher[27] = {};
  char *cipher_hole = cipher;
  char *c = key;
  while (*c != '\0') {
    if (alphabet[*c - 'a'] != '\0') {
      alphabet[*c - 'a'] = '\0';
      strncpy(cipher_hole, c, 1);
      cipher_hole++;
    }
    c++;
  }
  for (int i = 0; i < 27; i++) {
    if (alphabet[i] != '\0') {
      memcpy(cipher_hole, (alphabet + i), sizeof(char));
      cipher_hole++;
    }
  }
  strncpy(key, cipher, 26);

  return 1;
}

void encrypt(char *message, char const *key) {
  for (char *c = message; *c != '\0'; c++) {
    if (isalpha(*c)) {
      char encrypted = *(key + (tolower(*c) - 'a'));
      if (isupper(*c)) {
        encrypted = toupper(encrypted);
      }
      *c = encrypted;
    }
  }
}

void decrypt(char *message, char const *key) {
  for (char *c = message; *c != '\0'; c++) {
    if (isalpha(*c)) {
      char decrypted = 'a' + (strchr(key, tolower(*c)) - key);
      if (isupper(*c)) {
        decrypted = toupper(decrypted);
      }
      *c = decrypted;
    }
  }
}

char *test_prepare_key(void) {
  char *key = malloc(sizeof(char) * 27);
  strncpy(key, "trailBlazers", 13);
  int success = prepare_key(key);

  mu_assert(success == 1, "Processing failed");
  char *expected = "trailbzescdfghjkmnopquvwxy";
  mu_assert(strncmp(expected, key, 26) == 0, "Cipher not created correctly");

  return NULL;
}

char *test_encrypt(void) {
  char *key = malloc(sizeof(char) * 27);
  strncpy(key, "trailBlazers", 13);
  prepare_key(key);

  char *message = malloc(sizeof(char) * 13);
  strncpy(message, "Hello, World", 13);

  encrypt(message, key);

  char *expected = "Elffj, Vjnfi";

  mu_assert(strncmp(expected, message, 13) == 0, "Message not encoded successfully");

  return NULL;
}

char *test_decrypt(void) {
  char *key = malloc(sizeof(char) * 27);
  strncpy(key, "trailBlazers", 13);
  prepare_key(key);

  char *original = "Hello World";
  char *message = malloc(sizeof(char) * 13);
  strncpy(message, original, 13);

  encrypt(message, key);
  decrypt(message, key);

  mu_assert(strncmp(original, message, 13) == 0, "Message not decrypted successfully");

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_prepare_key);
  mu_run_test(test_encrypt);
  mu_run_test(test_decrypt);

  return NULL;
}

RUN_TESTS(all_tests);
