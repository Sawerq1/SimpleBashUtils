#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "cat_parse.h"
#include "cat_print.h"

int main(int argc, char **argv) {
  flags flag = {0};

  char *short_options = "beEnstTv";
  struct option long_options[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                  {"number", no_argument, NULL, 'n'},
                                  {"squeeze-blank", no_argument, NULL, 's'}};

  int error = parse_params(argc, argv, short_options, long_options, &flag);

  if (error) {
    return 1;
  }
  if (optind == argc) {
    print_line(stdin, flag);
  } else {
    for (int i = optind; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (file == NULL) {
        perror("Error opening file");
        exit(1);
      }

      print_line(file, flag);

      fclose(file);
    }
  }

  return 0;
}