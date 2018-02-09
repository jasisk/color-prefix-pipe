#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFERSIZE 2048
#define DELIMITER '\t'

#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"

const char *colors[]={RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
const unsigned long colors_length=sizeof(colors)/sizeof(*colors);

int main(int argc, char* argv[]) {
  char buffer[BUFFERSIZE];
  size_t num_of_entries=0;

  if (isatty(fileno(stdin))) {
    puts("usage: precolor [-d delimiter]\n\t-d delimiter: specify a delimiter, defaults to tab");
    return 0;
  }

  char delimiter = DELIMITER;

  int opt;
  while ((opt = getopt(argc, argv, "d:")) != -1) {
    switch (opt) {
      case 'd':
        delimiter = *optarg;
        break;
      case '?':
        if (optopt == 'd') {
          fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        } else if (isprint(optopt)) {
          fprintf(stderr, "Option -%c unknown.\n", optopt);
        } else {
          fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
        }
        return 1;
      default:
        abort();
    }
  }

  char **prefixes = malloc(num_of_entries * sizeof(char*));

  while (fgets(buffer, BUFFERSIZE, stdin) != NULL) {
    char *cp = &buffer[0];
    char *token = strchr(buffer, delimiter);
    if (token == NULL) {
      fputs(buffer, stdout);
      continue;
    }
    size_t len = token-cp;
    size_t i;
    for (i = 0; i < num_of_entries;) {
      if (!memcmp(prefixes[i], cp, len)) {
        token = prefixes[i];
        break;
      }
      i++;
    }
    if (i == num_of_entries) {
      prefixes = realloc(prefixes, (num_of_entries + 1) * sizeof(char*));
      token = malloc(len+1);
      memcpy(token, cp, len);
      token[len] = '\0';
      prefixes[num_of_entries++] = token;
    }
    printf("%s%s" RESET "%s", colors[i % colors_length], token, &cp[len]);
    fflush(stdout);
  }

  // free(prefixes);
  return 0;
}
