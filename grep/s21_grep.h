#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments {
  int e, i, v, c, l, n, h, s, f, o;
  char pattern[1024];
  int len_pattern;
} flags;

flags flag_parser(int argc, char* argv[]);
void pattern_add(flags* fl, char* pattern);
void add_reg_from_file(flags* fl, char* filepath);
void outputLine(char* line, int n);
void printMatch(regex_t* re, char* line);
void processFile(flags fl, char* path, regex_t* reg);
void output(flags fl, int argc, char* argv[]);

#endif