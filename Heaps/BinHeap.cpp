#include <cstdio>
using namespace std;

// A binary heap is a binary tree that is completely filled and satisfy heap order property.
// In a Min(Max) heap, for every node X, the key in the parent of X is smaller(larger) or equal to the key in X, with the exception of root (which has no parent).
// For element at index i, its left child has index 2i+1, its right child has index 2i+2, its parent has index (i-1)/2

class BinHeap
{
    int capacity; // maximum heap size
    int size; // current number of element in the heap
    int *harr; // pointer to array of elements in the heap

public:
    BinHeap(int capacity);              // constructor 1
    ~BinHeap();                         // deconstructor
    void buildHeap(int n, int* arr);    // build the heap from an input N keys 
    void makeEmpty();                   // remove all keys from the min heap
    void insert(int x);                 // insert new key to the min heap
    void deleteMin();                   // remove the minimun key from the min heap
    int findMin();                      // return the minimun key from the min heap
    bool isEmpty();                     // return if the heap is empty
    bool isFull();                      // return if the heap is full
    void decreaseKey(int p, int delta); // decrease the value of the key at position p
    void increaseKey(int p, int delta); // increase the value of the keay at postion p
}; 

BinHeap::BinHeap(int cap) {
    capacity = cap;
    size = 0;
    harr = new int[cap];
}

BinHeap::~BinHeap() {
    delete [] harr;
}

void BinHeap::buildHeap(int n, int* arr) {
    if (n > capacity) {
        printf("Heap is full\n");
        return;
    }

    size = n;
    for (int i = 0; i < n; i++) {
        harr[i] = arr[i];
    }

    // interate to percolate down the non-leaf node
    for (int i = (size-2)/2; i >=0; i--) {
        int j, child;
        int ele = harr[i];
        for (j = i; 2*j+1 < size; j = child) {
            child = 2*j + 1;
            if (child + 1 < size; harr[child+1] < harr[child]) {
                child ++;
            }
            if (ele > harr[child]) {
                harr[j] = harr[child];
            } else {
                break;
            }
        }
        harr[j] = ele;
    }

}

void BinHeap::makeEmpty() {
    size = 0;
}

void BinHeap::insert(int x) {
    // To insert an element X into the heap, we create a hole in the next available location since other wise the tree will not be complete. If X can be placed in the hole without violating heap order, then we do so and are done. Otherwise we slide the element that is in the hole's parent node into the hoe, thus bubbling the hole up towards the root. We continue this process until X can be placed in the hole. 
    // This general strategy is known as a 'percolate up'.

    if (this->isFull()) {
        printf("BinHeap is full\n");
        return;
    }

    size += 1;
    int i = size - 1;
    while (i != 0 && x < harr[(i-1)/2]) {
        harr[i] = harr[(i-1)/2];
        i = (i-1) / 2;
    }
    harr[i] = x;
}

void BinHeap::deleteMin() {
    // When the minimun is removed, a hole is created at the root. Since the heap now becomes one smaller, it follows that the last element X in the heap must move somewhere in the heap. If X can be placed in the hole, the we are done. Otherwise we slide the smaller o the hole's children into the hole, thus pushing the hole down one level. We repeat this step until X can be placed in the hole.
    // This general strategy is known as a 'percolate down'.

    if (this->isEmpty()) {
        printf("BinHeap is empty\n");
        return;
    }

    int lastEle = harr[--size];
    int i, child;
    for (i = 0; 2*i+1 < size; i = child) {
        child = 2 * i + 1;
        if (child < size-1 && harr[child+1] < harr[child]) {
            child ++;
        }
        if (lastEle > harr[child]) {
            harr[i] = harr[child];
        } else {
            break;
        }
    }
    harr[i] = lastEle;
}

int BinHeap::findMin() {
    if (this->isEmpty()) {
        printf("Heap is empty\n");
        return -1;
    }
    return harr[0];
}

bool BinHeap::isEmpty() {
    return size == 0;
}

bool BinHeap::isFull() {
    return size == capacity;
}

void BinHeap::decreaseKey(int p, int delta) {
    // Since lowering the value of the key at position p by a positive amount delta might violate the heap order, it must be fixed by a percolate up.

    int x = harr[p] - delta;
    int i = p;
    while (i != 0 && x < harr[(i-1)/2]) {
        harr[i] = harr[(i-1)/2];
        i = (i-1) / 2;
    }
    harr[i] = x;
}

void BinHeap::increaseKey(int p, int delta) {
    // Since increasing the value of the key at positoin p by a positive amount delta might violate the heap order, it must be fixed by a percolate down.

    int x = harr[p] + delta;
    int i, child;
    for (i = p; 2*i+1 < size; i = child) {
        child = 2*i + 1;
        if (child+1 < size && harr[child+1] < harr[child]) {
            child ++;
        }
        if (x > harr[child]) {
            harr[i] = harr[child];
        } else {
            break;
        }
    }
    harr[i] = x;
}

int main() {

    BinHeap* bh = new BinHeap(20);
    int a[15] = {150, 80, 40, 30, 10, 70, 110, 100, 20, 90, 60, 50, 120, 140, 130};
    bh->buildHeap(15, a);
    bh->insert(160);
    bh->insert(0);
    while (!bh->isEmpty()) {
        int d = bh->findMin();
        bh->deleteMin();
        printf("%d\n", d);
    }
    return 0;
}