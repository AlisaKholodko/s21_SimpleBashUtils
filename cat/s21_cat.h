#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct arguments {
  int b, e, E, v, n, s, t, T;
} flags;

flags flag_parser(int argc, char* argv[]);
char v_flag(char ch);
void t_e_flag(flags* arg, char* line, int n);
void res_output(flags* arg, char* argv[]);

#endif