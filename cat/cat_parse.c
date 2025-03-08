#include "cat_parse.h"

int parse_params(int argc, char **argv, char *short_options,
                 struct option long_options[], flags *flag) {
  int res;
  int error = 0;
  int idx = 0;

  while ((res = getopt_long(argc, argv, short_options, long_options, &idx)) !=
         -1) {
    switch (res) {
      case 'b':
        flag->b = true;
        break;
      case 'e':
        flag->e = true;
        flag->v = true;
        break;
      case 'E':
        flag->e = true;
        break;
      case 'n':
        flag->n = true;
        break;
      case 's':
        flag->s = true;
        break;
      case 't':
        flag->t = true;
        flag->v = true;
        break;
      case 'T':
        flag->t = true;
        break;
      case 'v':
        flag->v = true;
        break;
      case '?':
        error = true;
        break;
      default:
        error = true;
        break;
    }
  }

  if (error) {
    return 1;
  }
  return 0;
}