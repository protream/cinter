#ifndef TESTHELPER_H_
#define TESTHELPER_H_

#include <stdio.h>

#define TEST(what) printf(what);
#define assert(_e) ((_e)?(void)0:(_assert(#_e, __FILE__,__LINE__),exit(1)))

void ok() {
    printf("OK\n");
}

static void _assert(char *estr, char *file, int line) {
    printf("\n\n=== ASSERTION FAILED ===\n");
    printf("==> %s:%d '%s' is not true!\n", file, line, estr);
}

#endif // TESTHELPER_H_
