#include "s21_grep.h"

int main(int argc, char* argv[]) {
  flags fl = flag_parser(argc, argv);
  output(fl, argc, argv);
  return 0;
}

flags flag_parser(int argc, char* argv[]) {
  flags fl = {0};
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        fl.e = 1;
        pattern_add(&fl, optarg);
        break;
      case 'i':
        fl.i = REG_ICASE;
        break;
      case 'v':
        fl.v = 1;
        break;
      case 'c':
        fl.c = 1;
        break;
      case 'l':
        fl.l = 1;
        break;
      case 'n':
        fl.n = 1;
        break;
      case 'h':
        fl.h = 1;
        break;
      case 's':
        fl.s = 1;
        break;
      case 'f':
        fl.f = 1;
        add_reg_from_file(&fl, optarg);
        break;
      case 'o':
        fl.o = 1;
        break;
    }
  }
  if (fl.len_pattern == 0) {
    pattern_add(&fl, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) {
    fl.h = 1;
  }
  return fl;
}

void pattern_add(flags* fl, char* pattern) {
  if (fl->len_pattern != 0) {
    strcat(fl->pattern + fl->len_pattern, "|");
    fl->len_pattern++;
  }
  fl->len_pattern += sprintf(fl->pattern + fl->len_pattern, "(%s)", pattern);
}

void add_reg_from_file(flags* fl, char* filepath) {
  FILE* text = fopen(filepath, "r");
  if (text == NULL) {
    if (!fl->s) perror(filepath);
    exit(1);
  }
  char* line = NULL;
  size_t memline = 0;
  int read = getline(&line, &memline, text);
  while (read != EOF) {
    if (line[read - 1] == '\n') line[read - 1] = '\0';
    pattern_add(fl, line);
    read = getline(&line, &memline, text);
  }
  free(line);
  fclose(text);
}

void outputLine(char* line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') putchar('\n');
}

void printMatch(regex_t* re, char* line) {
  regmatch_t match;
  int offset = 0;
  while (1) {
    int res_mutch = regexec(re, line + offset, 1, &match, 0);
    if (res_mutch != 0) {
      break;
    }
    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(line[i]);
    }
    putchar('\n');
    offset += match.rm_eo;
  }
}

void processFile(flags fl, char* path, regex_t* reg) {
  FILE* text = fopen(path, "r");
  if (text == NULL) {
    if (!fl.s) perror(path);
    exit(1);
  }
  char* line = NULL;
  size_t memline = 0;
  int read = 0;
  int line_count = 1;
  int c = 0;
  read = getline(&line, &memline, text);
  while (read != EOF) {
    int result = regexec(reg, line, 0, NULL, 0);
    if ((result == 0 && !fl.v) || (fl.v && result != 0)) {
      if (!fl.c && !fl.l) {
        if (!fl.h) printf("%s:", path);
        if (fl.n) printf("%d:", line_count);
        if (fl.o) {
          printMatch(reg, line);
        } else {
          outputLine(line, read);
        }
      }
      c++;
    }
    read = getline(&line, &memline, text);
    line_count++;
  }
  free(line);

  if (fl.c && !fl.l) {
    if (!fl.h) printf("%s:", path);
    printf("%d\n", c);
  }
  if (fl.l && fl.c && c > 0) printf("%s:%d\n", path, (c > 0) ? 1 : 0);
  if (fl.l && c > 0) printf("%s\n", path);

  fclose(text);
}

void output(flags fl, int argc, char* argv[]) {
  regex_t re;
  int error = regcomp(&re, fl.pattern, REG_EXTENDED | fl.i);
  if (error) perror("Error");
  for (int i = optind; i < argc; i++) {
    processFile(fl, argv[i], &re);
  }
  regfree(&re);
}