SHELL := /bin/bash
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -D _POSIX_C_SOURCE=200809L -D _GNU_SOURCE_ -D _GNU_SOURCE
CF_CHECK = clang-format --style="{BasedOnStyle: Google}" -n
CF_APPLY = clang-format --style="{BasedOnStyle: Google}" -i

all: s21_grep format

s21_grep: Makefile s21_grep.h s21_grep.c
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep

format:
	$(CF_CHECK) *.c
	$(CF_CHECK) *.h
	$(CF_APPLY) *.c
	$(CF_APPLY) *.h

test:
	./testing/start.sh

rebuild:
	make clean
	make all

clean:
	rm -f s21_grep