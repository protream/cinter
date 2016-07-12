/* bitmap.h */

#ifndef __BITMAP_H
#define __BITMAP_H

#define BYTE 8
#define MASK 0x07
#define SHIFT 3

typedef char *bitmap;

/* API */
bitmap bmCreate(int capacity);
void bmPut(bitmap bm, int value);
int  bmGet(bitmap bm, int value);
void bmShow(bitmap bm);
void bmFree(bitmap bm);

#endif /* __BITMAP_H */
