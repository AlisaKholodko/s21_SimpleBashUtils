SHELL := /bin/bash
FILE=testfile.txt
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -D _POSIX_C_SOURCE=200809L -D _GNU_SOURCE_ -D _GNU_SOURCE
CF_CHECK = clang-format --style="{BasedOnStyle: Google}" -n
CF_APPLY = clang-format --style="{BasedOnStyle: Google}" -i

all: s21_cat format

s21_cat: Makefile s21_cat.h s21_cat.c
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

format:
	$(CF_CHECK) *.c
	$(CF_CHECK) *.h
	$(CF_APPLY) *.c
	$(CF_APPLY) *.h

test:
	-diff <(./s21_cat $(FILE)) <(cat $(FILE))
	-diff <(./s21_cat -e $(FILE)) <(cat -e $(FILE))
	-diff <(./s21_cat -t $(FILE)) <(cat -t $(FILE))
	-diff <(./s21_cat -s $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat --squeeze-blank $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat -n $(FILE)) <(cat -n $(FILE))
	-diff <(./s21_cat --number $(FILE)) <(cat -n $(FILE))
	-diff <(./s21_cat -b $(FILE)) <(cat -b $(FILE))
	-diff <(./s21_cat --number-nonblank $(FILE)) <(cat -b $(FILE))

rebuild:
	make clean
	make all

clean:
	rm -f s21_cat