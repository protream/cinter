#include "str.h"

/* Find first occurence of c in s[n]. */
void *memchar(const void *s, int c, size_t n)
{
    const unsigned char uc = c;
    const unsigned char *su;

    for (su = s; n > 0; su++, n--)
        if (*su == uc)
            return (void *)su;
    return NULL;
}

size_t mystrlen(const char *s)
{
    const char *sc;

    for (sc = s; *sc != '\0'; sc++)
        ;
    return sc - s;
}

char *mystrchr(const char *s, int c)
{
    const char ch = c;

    for (; *s != ch; s++)
        if (*s == '\0') return NULL;
    return (char *)s;
}

char *mystrrchr(const char *s, int c)
{
    const char ch = c;
    const char *last;

    for (last = NULL; ; ++s) {
        if (*s == ch)
            last = s;
        if (*s == '\0')
            return (char *)last;
    }
}

char *mystrcat(char *s1, const char *s2)
{
    char *s;

    for (s = s1; *s != '\0'; s++)
        ;
    for (; (*s = *s2) != '\0'; s++, s2++)
        ;
    return s1;
}

char *mystrncat(char *s1, const char *s2, size_t n)
{
    char *s;

    for (s = s1; *s != '\0'; s++)
        ;
    for (; n > 0 && *s2 != '\0'; n--)
        *s++ = *s2++;
    *s = '\0';
    return s1;
}

/* compare unsigned char s1[] s2[]
 *
 * returns:
 *   -1: s1[] <  s2[]
 *    0: s1[] == s2[]
 *   +1: s1[] >  s2[]   */
int mystrcmp(const char *s1, const char *s2)
{
    for (; *s1 == *s2; s1++, s2++)
        if (*s1 == '\0') return 0;
    return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}

int mystrncmp(const char *s1, const char *s2, size_t n)
{
    for (; n > 0; s1++, s2++, n--) {
        if (*s1 != *s2)
            return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
        if (*s1 == '\0')
            return 0;
    }
    return 0;
}

char *mystrcpy(char *dst, const char *src)
{
    char *s;

    for (s = dst; (*s++ = *src++) != '\0';)
        ;

    return dst;
}

char *mystrncpy(char *dst, const char *src, size_t n)
{
    char *s;

    for (s = dst; n > 0 && *src != '\0'; n--)
        *s++ = *src++;
    for (; n > 0; n--)
        *s++ = '\0';
    return dst;
}

#ifdef STR_TEST
#include "testhelper.h"

void strTest(void)
{
    char s[20] = {0};
    const char *abcde = "abcde";
    const char *abcdx = "abcdx";

    TEST("mystrlen: ") {
        assert(mystrlen("") == 0);
        assert(mystrlen(abcde) == 5);
        ok();
    }

    TEST("mystrchr: ") {
        assert(mystrchr(abcde, 'a') == abcde);
        assert(mystrchr(abcde, 'd') == abcde+3);
        ok();
    }

    TEST("mystrcat: ") {
        assert(mystrcat(s, abcde) == s);
        assert(mystrcmp(s, abcde) == 0);
        assert(mystrcat(s, abcdx) == s);
        assert(mystrcmp(s, "abcdeabcdx") == 0);
        ok();
    }

    TEST("mystrcmp: ") {
        assert(mystrcmp(abcde, abcdx) == -1);
        assert(mystrcmp(abcde, "abcde") == 0);
        ok();
    }

    TEST("mystrcpy: ") {
        assert(mystrcpy(s, abcde) == s);
        assert(mystrcmp(s, abcde) == 0);
        ok();
    }
}

#ifdef STR_TEST_MAIN
int main(void)
{
    strTest();
    return 0;
}
#endif
#endif
