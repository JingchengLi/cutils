#ifndef CUTILS_H
#define CUTILS_H 1

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

int isStartWith(const char *buf, const char *match, int sensitive);
int isEndWith(const char* buf, const char* match, int sensitive);
char* replaceStr (const char *strbuf, const char *strold, const char *strnew);

#endif
