#include "cat_print.h"

#include <stdlib.h>
#include <string.h>

void print_line(FILE *file, flags flag) {
  int prev_ch = '\n';
  int ch;
  int line_number = 1;
  int count_end = 1;
  while ((ch = fgetc(file)) != EOF) {
    if (flag.s) {
      if (ch == '\n') count_end++;
      if (count_end > 2 && ch == '\n') {
        continue;
      }
    }
    if (flag.b) {
      if ((prev_ch == '\n' && ch != '\n') || (line_number == 1 && ch != '\n')) {
        count_end = 0;
        printf("%6d\t", line_number);
        line_number++;
      }
    } else if (flag.n && prev_ch == '\n') {
      if (line_number == 1 || prev_ch == '\n') {
        printf("%6d\t", line_number);
        line_number++;
      }
    }
    if (flag.v) {
      if (((ch < 32 && ch >= 0) || ch == 127) && ch != 10 && ch != 9) {
        count_end = 0;
        if (ch == 127) {
          count_end = 0;
          printf("^?");
        } else if (ch >= 160) {
          count_end = 0;
          printf("M-^%c", ch - 64);
        } else {
          count_end = 0;
          printf("^%c", ch + 64);
        }
      } else if ((ch >= 32 && ch != 127 && ch != 9) && ch != 10) {
        count_end = 0;
        putchar(ch);
      }
    } else if (ch != 9 && ch != 10) {
      count_end = 0;
      putchar(ch);
    }

    if (ch == '\t') {
      if (flag.t) {
        putchar('^');
        putchar('I');
        prev_ch = ch;
        continue;
      } else {
        printf("\t");
        prev_ch = ch;
        continue;
      }
    }
    if (count_end <= 2 && ch == '\n') {
      if (flag.e) putchar('$');
      putchar('\n');
    }
    prev_ch = ch;
  }
}