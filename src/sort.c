/* sort.c - Various sort algorigms implementation. */
#define TEST_SORT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

static inline void swap(int *a, int *b)
{
    int tp;

    tp = *a;
    *a = *b;
    *b = tp;
}

/*------------------------- 3 Bubble Sort -------------------------*/

void bubbleSort(int *a, int n)
{
//    int i;

//    while (n--) {
//        for (i = 1; i <= n; i++)
//           if (a[i - 1] > a[i]) swap(a + i - 1, a + i);
//    }

//     int i, flag;
//
//     flag = 1;
//     while (flag && n--) {
//        flag = 0;
//        for (i = 1; i <= n; i++)
//           if (a[i - 1] > a[i]) {
//               swap(a + i - 1, a + i);
//               flag = 1;
//           }
//     }

    int i, j, flag;

    flag = n;
    while (flag) {
        j = flag;
        flag = 0;
        for (i = 1; i < j; i++) {
           if (a[i - 1] > a[i]) {
               swap(a + i - 1, a + i);
               flag = i;
           }
        }
    }
}

/*------------------------- Insert Sort -------------------------*/

void insertSort(int *a, int n)
{
    int i, j, key;

    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

/*------------------------- Select Sort -------------------------*/

void selectSort(int *a, int n)
{
    int i, max;

    while (n--) {
        max = 0;
        for (i = 1; i <= n; i++) {
            if (a[i] > a[max]) max = i;
        }
        swap(a + n, a + max);
    }
}

/*------------------------- Quick Sort -------------------------*/

static void qSort(int *a, int lrange, int rrange)
{
    if (lrange < rrange) {
        int i, j, pivot;

        i = lrange;
        j = rrange;
        pivot = a[i];

        while (i < j) {
            while (i < j && a[j] >= pivot)
                j--;
            if (i < j) a[i++] = a[j];

            while (i < j && a[i] <= pivot)
                i++;
            if (i < j) a[j--] = a[i];
        }
        a[i] = pivot;
        qSort(a, lrange, i - 1);
        qSort(a, i + 1, rrange);
    }
}

void quickSort(int *a, int n)
{
   qSort(a, 0, n - 1);
}

/*------------------------- Merge Sort -------------------------*/

static void mSort(int *a, int lrange, int rrange, int *temp)
{
    if (lrange < rrange) {
        int l, m, r;

        l = lrange;
        r = rrange;
        m = l + (r - l) / 2;
        mSort(a, l, m, temp);
        mSort(a, m + 1, r, temp);

        /* merge two part of the array.
         *
         * lb rb: left/right begin
         * le re: left/rieht end
         */
        int i, n, lb, le, rb, re;

        lb = l;
        le = m;
        rb = m + 1;
        re = r;
        i = l;
        n = r - l + 1;
        while (lb <= le && rb <= re) {
            if (a[lb] <= a[rb])
                temp[i++] = a[lb++];
            else
                temp[i++] = a[rb++];
        }

        while (lb <= le) temp[i++] = a[lb++];
        while (rb <= re) temp[i++] = a[rb++];

        for (i = 0; i < n; i++, re--) {
            a[re] = temp[re];
        }
    }
}

void mergeSort(int *a, int n)
{
    int *temp;

    if ((temp = (int *)malloc(n * sizeof(int))) == NULL) {
        printf("Memery allocation error.\n");
        exit(1);
    }
    mSort(a, 0, n - 1, temp);
    free(temp);
}

/*------------------------- Heap Sort -------------------------*/

#define lchild(i) (2 * (i) + 1)

static void maxHeapify(int *a, int i, int n)
{
    int child, tmp;

    for (tmp = a[i]; lchild(i) < n; i = child) {
        child = lchild(i);
        if (child != n - 1 && a[child + 1] > a[child]) {
            child++;
        }
        if (tmp < a[child])
            a[i] = a[child];
        else
            break;
    }
    a[i] = tmp;
}

void heapSort(int *a, int n)
{
    int i;

    for (i = n / 2; i >= 0; i--) {
        maxHeapify(a, i, n);
    }
    for (i = n - 1; i > 0; i--) {
        swap(a, a + i);
        maxHeapify(a, 0, i);
    }

}

/*------------------------- Count Sort -------------------------*/

/* Count sort assume that every element in range [0, k]. */
void countSort(int *A, int *B, int n, int k)
{
    int i, *C;

     /* count array. */
    if ((C = (int *)calloc(k + 1, sizeof(int))) == NULL) {
        printf("Memery allocation error.\n");
        exit(1);
    };

    for (i = 0; i < n; i++)
        C[A[i]]++;
    for (i = 1; i <= k; i++)
       C[i] += C[i - 1];
    for (i = n; i >= 1; i--) {
       B[C[A[i]]] = A[i];
       C[A[i]]--;
    }
    free(C);
}

/*------------------------- Bucket Sort -------------------------*/

/* Special edition: every element has a bucket. */
void bucketSortSpec(int *A, int *B, int n, int k)
{
    int i, j, *C;

     /* C: count array. */
    if ((C = (int *)calloc(k + 1, sizeof(int))) == NULL) {
        printf("Memery allocation error.\n");
        exit(1);
    };

    for (i = 0; i < n; i++)
        C[A[i]]++;
    for (i = j = 0; i <= k; i++) {
        while (C[i]--)
            B[j++] = i;
    }
    free(C);
}

typedef struct listNode {
    int value;
    struct listNode *next;
} listNode;

static listNode *listInsertSort(listNode *head)
{
    if (head == NULL || head->next == NULL)
        return head;

    listNode **p, *curr, *next;

    curr = head->next;
    head->next = NULL;
    while (curr) {
        next = curr->next;
        p = &head;
        while (*p) {
            if ((*p)->value <= curr->value)
                p = &(*p)->next;
            else
                break;
        }
        curr->next = *p;
        *p = curr;
        curr = next;
    }
    return head;
}

void bucketSort(int *A, int *B, int n, int k)
{
    int i, j;
    listNode *node, *buckets[200];

    memset(buckets, 0, sizeof(buckets));
    for (i = 0; i < n; i++) {
        if ((node = (listNode *)malloc(sizeof(listNode))) == NULL) {
            printf("Memery allocation error.\n");
            exit(1);
        }
        j = A[i] / 50;
        node->value = A[i];
        node->next = buckets[j];
        buckets[j] = node;
    }
    for (i = j = 0; i < 200; i++) {
        node = listInsertSort(buckets[i]);
        while (node) {
            B[j++] = node->value;
            node = node->next;
        }
    }
}


/*------------------------- Radix Sort -------------------------*/
void bs(int *a, int n, int k)
{
    int i, j, divisor;
    listNode *node, *buckets[10];

    divisor = 1;
    while (k--)
        divisor *= 10;
    memset(buckets, 0, sizeof(buckets));
    for (i = n - 1; i >= 0; i--) {
        if ((node = (listNode *)malloc(sizeof(listNode))) == NULL) {
            printf("Memery allocation error.\n");
            exit(1);
        }
        j = a[i] / divisor % 10;
        node->value = a[i];
        node->next = buckets[j];
        buckets[j] = node;
    }
    for (i = j = 0; i < 10; ++i) {
        node = buckets[i];
        while (node) {
            a[j++] = node->value;
            node = node->next;
        }
    }

}

void radixSort(int *a, int n, int k)
{
    int i;

    for (i = 0; i < k; i++) {
        bs(a, n, i);
    }

}

#ifdef TEST_SORT
#include <time.h>

#define ARR_SIZE 100

int main(int argc, char *argv[])
{
    int i;
    int a[ARR_SIZE];

    srand(time(NULL));
    for (i = 0; i < ARR_SIZE; ++i) {
        a[i] = rand() % ARR_SIZE;
    }

    //bubbleSort(a, 10);
    //insertSort(a, 10);
    //selectSort(a, 10);
    //quickSort(a, 10);
    //mergeSort(a, 10);
    //heapSort(a, 10);
    /*countSort(a, ARR_SIZE, 9);*/
    /*int *b = (int *)calloc(ARR_SIZE, sizeof(int));*/
    /*bucketSort(a, b, ARR_SIZE, 100);*/
    radixSort(a, ARR_SIZE, 2);
    for (i = 0; i < ARR_SIZE; ++i) {
        printf("%d ", a[i]);
    }
    return 0;
}
#endif
