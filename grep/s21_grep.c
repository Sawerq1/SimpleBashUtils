#include "s21_grep.h"

int strcase_search(const char *haystack, const char *needle) {
  for (; *haystack; haystack++) {
    const char *h = haystack, *n = needle;
    while (*h && *n &&
           tolower((unsigned char)*h) == tolower((unsigned char)*n)) {
      h++;
      n++;
    }
    if (!*n) return 1;
  }
  return 0;
}

int contains_pattern(const char *line, const char *pattern, int i) {
  if (i) {
    return strcase_search(line, pattern);
  }
  return strstr(line, pattern) != NULL;
}

void process_line(const char *line, const char *filename, int line_number,
                  flags_gr *flags, int match, int multiple_files) {
  if (!flags->c && !flags->l && match) {
    if (multiple_files) {
      printf("%s:", filename);
    }
    if (flags->n) {
      printf("%d:", line_number);
    }
    printf("%s", line);
  }
}

void process_file(const char *filename, char *patterns[], int pattern_count,
                  flags_gr *flags, int multiple_files) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror(filename);
    return;
  }
  char line[MAX_LINE_LENGTH];
  int match_count = 0;
  int line_number = 0;
  int file_match = 0;

  while (fgets(line, sizeof(line), file)) {
    line_number++;
    int match = 0;

    for (int i = 0; i < pattern_count; i++) {
      if (contains_pattern(line, patterns[i], flags->i)) {
        match = 1;
        break;
      }
    }

    if (flags->v) match = !match;

    if (match) {
      file_match = 1;
      match_count++;
      process_line(line, filename, line_number, flags, match, multiple_files);
    }
  }
  fclose(file);
  if (flags->l && file_match && flags->c) {
    printf("%d\n", match_count);
    printf("%s\n", filename);
  } else if (flags->c) {
    if (multiple_files)
      printf("%s:%d\n", filename, match_count);
    else
      printf("%d\n", match_count);
  } else if (flags->l && file_match)
    printf("%s\n", filename);
}

void parse_arguments(int argc, char *argv[], flags_gr *flags, char *patterns[],
                     int *pattern_count, char **files, int *file_count) {
  int opt;

  while ((opt = getopt(argc, argv, "e:ivcln")) != -1) {
    switch (opt) {
      case 'e':
        if (*pattern_count < MAX_PATTERNS) {
          patterns[(*pattern_count)++] = optarg;
        } else {
          fprintf(stderr, "Error: Too many patterns specified\n");
          exit(1);
        }
        break;
      case 'i':
        flags->i = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      default:
        exit(1);
    }
  }

  if (*pattern_count == 0 && optind < argc) {
    patterns[(*pattern_count)++] = argv[optind++];
  }

  *file_count = 0;
  for (int i = optind; i < argc; i++) {
    files[(*file_count)++] = argv[i];
  }

  if (*pattern_count == 0 || *file_count == 0) exit(1);
}

int main(int argc, char *argv[]) {
  flags_gr flags = {0};
  char *patterns[MAX_PATTERNS];
  char *files[MAX_PATTERNS];
  int pattern_count = 0;
  int file_count = 0;

  parse_arguments(argc, argv, &flags, patterns, &pattern_count, files,
                  &file_count);

  int multiple_files = file_count > 1;

  for (int i = 0; i < file_count; i++) {
    process_file(files[i], patterns, pattern_count, &flags, multiple_files);
  }

  return 0;
}
