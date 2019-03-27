
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