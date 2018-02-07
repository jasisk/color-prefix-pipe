#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#define BUFFERSIZE 2048
#define DELIMITER "\t"

#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"

const char *a[]={RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
const unsigned long len=sizeof(a)/sizeof(*a);

int main(int argc, char* argv[]) {
  char buffer[BUFFERSIZE];
  int num_of_entries=0;

  char **prefixes = malloc(num_of_entries * sizeof(char*));

  while (fgets(buffer, BUFFERSIZE, stdin) != NULL) {
    char *cp = &buffer[0];
    char *token = strsep(&cp, DELIMITER);
    int i;
    for (i = 0; i < num_of_entries;) {
      if (!strcmp(prefixes[i], token)) {
        token = prefixes[i];
        break;
      }
      i++;
    }
    if (i == num_of_entries) {
      prefixes = realloc(prefixes, (num_of_entries + 1) * sizeof(char*));
      prefixes[num_of_entries++] = strdup(token);
    }
    printf("%s%s" RESET DELIMITER "%s", a[i % len], token, cp);
  }

  free(prefixes);
  return 0;
}
