#ifndef STR_H_
#define STR_H_

#include <stdlib.h>

void *memchar(const void *s, int c, size_t n);

size_t mystrlen(const char *s);
char *mystrchr(const char *s, int c);
char *mystrrchr(const char *s, int c);
char *mystrcat(char *s1, const char *s2);
char *mystrncat(char *s1, const char *s2, size_t n);
int mystrcmp(const char *s1, const char *s2);
int mystrncmp(const char *s1, const char *s2, size_t n);
char *mystrcpy(char *dst, const char *src);
char *mystrncpy(char *dst, const char *src, size_t n);

#endif /* STR_H_ */
