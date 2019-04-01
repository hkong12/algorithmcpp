#include <cstdio>
using namespace std;

// Mergesort runs in O(NlogN) worst-case running time.
// if N = 1, there is only one element to sort, return the element. Otherwise, recursively mergesort the first half and the second harf. This gives two sorted halves, which can then be merged in linear time to an output array.

void merge(int arr[], int tmp[], int lpos, int rpos, int rightEnd) {
    int leftEnd, numElement, tmpPos;

    leftEnd = rpos - 1;
    tmpPos = lpos;
    numElement = rightEnd - lpos + 1;

    // main loop
    while (lpos <= leftEnd && rpos <= rightEnd) {
        if (arr[lpos] <= arr[rpos]) {
            tmp[tmpPos++] = arr[lpos++];
        } else {
            tmp[tmpPos++] = arr[rpos++];
        }
    }
    while (lpos <= leftEnd) {
        tmp[tmpPos++] = arr[lpos++];
    }
    while (rpos <= rightEnd) {
        tmp[tmpPos++] = arr[rpos++];
    }

    // copy the tmp array back
    for (int i = 0; i < numElement; i++, rightEnd--) {
        arr[rightEnd] = tmp[rightEnd];
    }
}

void mSort(int arr[], int tmp[], int left, int right) {
    int center;
    if (left < right) {
        center = (left + right) / 2;
        mSort(arr, tmp, left, center);
        mSort(arr, tmp, center+1, right);
        merge(arr, tmp, left, center+1, right);
    }
}

void mergeSort(int n, int arr[]) {
    int *tmp = new int[n];
    mSort(arr, tmp, 0, n-1);
    delete [] tmp;
}

int main () {
    int a[10] = {34, 8, 64, 51, 32, 21, 19, 22, 9, 48};
    mergeSort(10, a);
    for (int i = 0; i < 10; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}