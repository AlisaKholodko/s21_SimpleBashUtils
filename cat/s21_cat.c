#include "s21_cat.h"

int main(int argc, char* argv[]) {
  flags fl = flag_parser(argc, argv);
  res_output(&fl, argv);
  return 0;
}

flags flag_parser(int argc, char* argv[]) {
  flags fl = {0};

  struct option long_options[] = {{"number", no_argument, NULL, 'n'},
                                  {"number-nonblank", no_argument, NULL, 'b'},
                                  {"squeeze-blank", no_argument, NULL, 's'},
                                  {0, 0, 0, 0}};

  int opt;
  opt = getopt_long(argc, argv, "beEvnstT", long_options, 0);
  switch (opt) {
    case 'b':
      fl.b = 1;
      break;
    case 'e':
      fl.E = 1;
      fl.v = 1;
      break;
    case 'E':
      fl.E = 1;
      break;
    case 'v':
      fl.v = 1;
      break;
    case 'n':
      fl.n = 1;
      break;
    case 's':
      fl.s = 1;
      break;
    case 't':
      fl.T = 1;
      fl.v = 1;
      break;
    case 'T':
      fl.T = 1;
      break;
    case '?':
      perror("ERROR");
      exit(1);
      break;
    default:
      break;
  }
  return fl;
}

char v_flag(char ch) {
  if (ch == '\n' || ch == '\t') return ch;
  if (ch >= 0 && ch <= 31) {
    putchar('^');
    ch += 64;
  } else if (ch == 127) {
    putchar('^');
    ch = '?';
  } else if (ch <= -97) {
    printf("M-^");
    ch += 64 + 128;
  }
  return ch;
}

void t_e_flag(flags* fl, char* line, int n) {
  for (int i = 0; i < n; i++) {
    if (fl->T && line[i] == '\t')
      printf("^I");
    else {
      if (fl->E && line[i] == '\n') putchar('$');
      if (fl->v) line[i] = v_flag(line[i]);
      putchar(line[i]);
    }
  }
}

void res_output(flags* fl, char* argv[]) {
  FILE* text = fopen(argv[optind], "r");
  char* line = NULL;
  size_t memline = 0;
  int read = 0;
  int line_count = 1;
  int empty_count = 0;
  read = getline(&line, &memline, text);
  while (read != EOF) {
    if (line[0] == '\n')
      empty_count++;
    else
      empty_count = 0;
    if (fl->s && empty_count > 1)
      ;
    else {
      if (fl->n || fl->b) {
        if (fl->b && line[0] != '\n') {
          printf("%6d\t", line_count);
          line_count++;
        } else if (fl->n) {
          printf("%6d\t", line_count);
          line_count++;
        }
      }
      t_e_flag(fl, line, read);
    }
    read = getline(&line, &memline, text);
  }
  free(line);
  fclose(text);
}