#include <cstdio>
#include <cmath>
using namespace std;

// Shellsort, named after its inventor, Donald Shell, was one of the first algorithm to break the quadratic time barrier which works by comparing elements that are distant and the distance between comparisons decreases as the algorithm tuns until the last phase, in which adjacent elements are comared.
// Shell sort uses a sequence, h_1, h_2,...h_t, called the increment sequence
// A popular but poor choice for increase sequence - h_t = floor(N/2); h_k = floor(h_(k-1)/2); worst-case time complexity BigTheta(N^2)
// Hibbard's increaments - 1, 3, 7, 2^k-1; worst-case time complexity BitTheta(N^(3/2))
// Sedgewick's increaments - 1, 5, 19, 41, 109... in which the terms are either of the form 9*4^i - 9*2^i + 1 or 4^i - 3*2^i + 1; worst-case time complexity O(N^(4/3))

void insertionSort(int n, int arr[]) {
    for (int i = 1; i < n; ++i) {
        int tmp = arr[i];
        int j;
        for (j = i; j > 0 && arr[j-1] > tmp; --j) {
            arr[j] = arr[j-1];
        }
        arr[j] = tmp;
    }
}

void shellSort(int n, int arr[]) {
    // use Hibbard's increaments
    int h = (1 << int(log(n+1)/log(2))) - 1;
    for (; h > 0; h = (h+1)/2 - 1) {
        printf("%d\n", h);
        for (int i = h; i < n; ++i) {
            int tmp = arr[i];
            int j;
            for (j = i; j > h-1 && arr[j-1] > tmp; j -= h) {
                arr[j] = arr[j-h];
            }
            arr[j] = tmp;
        }
    }
}

int main () {
    int a[10] = {34, 8, 64, 51, 32, 21, 19, 22, 9, 48};
    // insertionSort(10, a);
    shellSort(10, a);
    for (int i = 0; i < 10; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}

