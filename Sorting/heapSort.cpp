#include <cstdio>
#include <algorithm>
using namespace std;

// Heapsort based on the idea of using priority queue to sort in O(NlogN) time. The basic strategy is to build a binary heap of N elements. This stage takes O(N) time. Then we perform the N DeleteMin operations, the total running time of which is O(NlogN). A way to avoid using a second array makes use of the fact that after each DeleteMin, the heap shrinks by 1. Thus the cell that was last in the heap can be used to store the element that was just delted. Using this strategy, after the last DeleteMin the array will contain the element in decreasing sorted order. If we want the elements in the more typical increasing sorted order, we can use a max heap.
// Heapsort is the only sort to get the partial result.

void percDown(int n, int i, int arr[]) {
    int tmp = arr[i];
    int j, child;
    for (j = i; 2*j+1 < n; j = child) {
        child = 2 * j + 1;
        if (child+1 < n && arr[child+1] > arr[child]) {
            child ++;
        }
        if (arr[child] > tmp) {
            arr[j] = arr[child];
        } else {
            break;
        }
    }
    arr[j] = tmp;
}

void heapSort(int n, int arr[]) {
    // build the max heap
    // element at index i, its parent has index floor((i-1)/2), its left child 2i+1, its right child 2i+2
    for (int i = (n-1)/2; i >= 0; --i) {
        percDown(n, i, arr);
    }

    // swap the largest element in the heap with the last element in the heap, then do a percolate down
    for (int i = n-1; i > 0; i--) {
        swap(arr[i], arr[0]);
        percDown(i, 0, arr);
    }
}

int main () {
    int a[10] = {34, 8, 64, 51, 32, 21, 19, 22, 9, 48};
    heapSort(10, a);
    for (int i = 0; i < 10; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}