#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  int size = 10 * sizeof(char);
  char *str = malloc(size);
  for (int i = 0; i < size; i++) {
    *(str + i) = '*';
  }
  int count = 0;
  char current = '\0';

  while ((current = getc(stdin)) != '\n') {
    if (count >= size - 1) {
      size *= 2;
      str = realloc(str, size);
    }

    *(str + count) = current;
    count++;
  }

  str = realloc(str, count * sizeof(char));
  *(str + count) = '\0';

  printf("Count is %d\n", count);
  printf("Entered string is %s\n", str);
  printf("Number of characters is %ld\n", strlen(str));
  return 0;
}
