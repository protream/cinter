#include <stdlib.h>
#include "bitmap.h"


// Create a bitmap with capacity.
//
// A bm with 16 capacity :
//
//  +--------+--------+
//  |00000000|00000000|
//  +--------+--------+
//
// This bm can holds flag of value 0~15.
bitmap bmCreate(int capacity)
{
    bitmap bm;

    return ((bm = calloc(capacity / BYTE, BYTE)) == NULL
        ? NULL
        : bm);
}

// Put a value into the bm.
//
// Put 9 to the above bm:
//
//  +--------+--------+
//  |00000000|01000000|
//  +--------+--------+
//
// means set the flag of value 9 to 1.
void bmPut(bitmap bm, int value)
{
    // value & MASK <=> value % 8
    bm[value >> SHIFT] |= (1 << (value & MASK));
}

// Get the flag of value in the bm.
int bmGet(bitmap bm, int value)
{
    return bm[value >> SHIFT] & (1 << (value & MASK));
}

void bmFree(bitmap bm)
{
    free(bm);
}

#ifdef BITMAP_TEST
#include "testhelper.h"

void bitmapTest(void)
{
    int i;
    bitmap bm;

    bm = bmCreate(16);

    /* +--------+--------+
     * |10100100|00000110|
     * +--------+--------+ */
    bmPut(bm, 5);
    bmPut(bm, 2);
    bmPut(bm, 0);
    bmPut(bm, 13);
    bmPut(bm, 14);

    assert(bmGet(bm, 0) == 1);
    assert(bmGet(bm, 2) == 1);
    assert(bmGet(bm, 5) == 1);
    assert(bmGet(bm, 13) == 1);
    assert(bmGet(bm, 14) == 1);

    for (i = 0; i < 16; ++i) {
        if (bmGet(bm, i)) {
            printf("%d\n", i);
        }
    }

    bmFree(bm);
    printf("Test bitmap OK!\n");
}

#ifdef BITMAP_TEST_MAIN
int main(void) {
    bitmapTest();
}
#endif
#endif
