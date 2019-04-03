#include <cstdio>
#include <algorithm>
using namespace std;
const int CUTOFF = 10;

// Quicksort is the fastest known sorting algorithm in practice. Its average running time is O(NlogN) and O(N^2) worst-case performance, but it can be made exponentially unlikely with a little effort.
// The basic algorithm to sort an array S consists of the four easy steps: (1) If the number of elements in S is 0 or 1, then return; (2) Pick any element v in S, called the pivot; (3) Partition S-{v} into two disjoint groups, S1 consists of all element <= v, and S2 consists of all element >= v; (4) Return {quicksort(S1)} followed by v followed by quicksort(S2)

void insertionSort(int arr[], int left, int right) {
    for (int i = left+1; i <= right; i++) {
        int tmp = arr[i];
        int j;
        for (j = i; j > 0 && arr[j-1] > tmp; j--) {
            arr[j] = arr[j-1];
        }
        arr[j] = tmp;
    }
}

int median3(int arr[], int left, int right) {
    // A good strategy of picking the pivot is Median-of-Three Partition. pivot = median(left, center, right)
    int center = (left + right) / 2;
    if (arr[left] > arr[center]) {
        swap(arr[left], arr[center]);
    }
    if (arr[left] > arr[right]) {
        swap(arr[left], arr[right]);
    }
    if (arr[center] > arr[right]) {
        swap(arr[center], arr[right]);
    }

    // invariant: arr[left] <= arr[center] <= arr[right]
    swap(arr[center], arr[right-1]); // hide pivot
    return arr[right-1];
}

void qsort(int arr[], int left, int right) {
    // partitioning strategy
    int i, j;
    int pivot;

    if (left + CUTOFF <= right) {
        pivot = median3(arr, left, right);
        i = 0, j = right-1;
        for(;;) {
            while (arr[++i] < pivot) {};
            while (arr[--j] > pivot) {};
            if (i < j) {
                swap(arr[i], arr[j]);
            } else {
                break;
            }
        }
        swap(arr[i], arr[right-1]);
        qsort(arr, left, i-1);
        qsort(arr, i+1, right);
    } else {
        // For small arrays, quicksort does not perform as well as insertion sort. A good cutoff range is N=10
        insertionSort(arr, left, right);
    }
}

void quickSort(int n, int arr[]) {
    qsort(arr, 0, n-1);
}

int main () {
    int a[30] = {
        34, 8, 64, 51, 32, 21, 19, 22, 9, 48,
        9, 24, 42, 12, 39, 87, 12, 11, 5, 34,
        1, 89, 85, 98, 12, 86, 83, 65, 5, 23
        };
    quickSort(30, a);
    for (int i = 0; i < 30; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}