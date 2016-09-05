
int binSearch(int *a, int low, int high, int target)
{
    int mid;

    while (low <= high) {
       mid = low + (high - low) / 2;
       if (target < a[mid])
           high = mid - 1;
       else if (target > a[mid])
           low = mid + 1;
       else
           return mid;
    }
    return -1;
}


int binSearchUpperBound(int *a, int low, int high, int target)
{
    if (low > high || target >= a[high])
        return -1;

    int mid = low + (high - low) / 2;
    while (low < high) {
        if (target < a[mid])
            high = mid;
        else
            low = mid + 1;
        mid = low + (high - low) / 2;
    }

    return mid;
}


int binSearchLowerBound(int *a, int low, int high, int target)
{
    if (low > high || target <= a[low])
        return -1;

    int mid = low + (high - low + 1) / 2;
    while (low < high) {
        if (target > a[mid])
            low = mid;
        else
            high = mid - 1;
        mid = low + (high - low + 1) / 2;
    }

    return mid;
}

#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};


    assert(binSearch(a, 0, 9, 0) == 0);
    assert(binSearch(a, 0, 9, 3) == 3);
    assert(binSearch(a, 0, 9, 9) == 9);
    assert(binSearch(a, 0, 9, -1) == -1);

    printf("%d\n", binSearchUpperBound(a, 0, 9, 2));
    printf("%d\n", binSearchLowerBound(a, 0, 9, 2));

    return 0;
}
