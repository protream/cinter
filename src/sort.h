/* sort.h - Various sort algorigms implementation. */

#ifndef __SORT_H
#define __SORT_H

void bubbleSort(int *a, int n);
void insertSort(int *a, int n);
void selectSort(int *a, int n);
void quickSort(int *a, int n);
void mergeSort(int *a, int n);
void heapSort(int *a, int n);
void countSort(int *A, int *B, int n, int k);
void bucketSortSpec(int *A, int *B, int n, int k);
void bucketSort(int *A, int *B, int n, int k);
void radixSort(int *a, int n, int k);

#endif /* __SORT_H */
