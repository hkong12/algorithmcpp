#include <cstdio>
using namespace std;

void heapSort(int n, int arr[]) {

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