#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1024
#define MAX_PATTERNS 128

typedef struct {
  int i;
  int v;
  int c;
  int l;
  int n;
} flags_gr;

int strcase_search(const char *haystack, const char *needle);

int contains_pattern(const char *line, const char *pattern, int i);

void process_line(const char *line, const char *filename, int line_number,
                  flags_gr *flags, int match, int multiple_files);

void process_file(const char *filename, char *patterns[], int pattern_count,
                  flags_gr *flags, int multiple_files);

void parse_arguments(int argc, char *argv[], flags_gr *flags, char *patterns[],
                     int *pattern_count, char **files, int *file_count);