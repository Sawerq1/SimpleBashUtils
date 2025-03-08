#ifndef PARSE_H
#define PARSE_H
#include <getopt.h>
#include <stdbool.h>

typedef struct {
  bool b;
  bool e;
  bool n;
  bool s;
  bool t;
  bool v;
} flags;

int parse_params(int argc, char **argv, char *short_options,
                 struct option long_options[], flags *conf);

#endif