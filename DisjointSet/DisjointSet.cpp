#include <cstdio>
#include <algorithm>
using namespace std;

// A disjoint set is an efficient data structure to solve the equivalence problem.
// An equivalence relation is a relation R that satisfies three properties: (1) Reflexive: a R a, for all a belongs to S; (2) Symmetric: a R b if and only if b R a; (3) Transitive: a R b and b R c implies that a R c.
// In disjoint set, each set contains a equivalence class of an element a belongs to S (a subset of S that contains all the elements that are related to a), which forms a partition of S and every member of S appears in exactly one equivalence class.
// There are two permissible operations: (1) Find - return the name of the set (equivalence class) containing a given element; (2) Union - merge the two equivalence classes containing a and b into a new equivalence class. The algorithm to do this is frequently known as the disjoint set Union/Find algorithm.

typedef int SetType;
typedef int ElementType;

class DisjointSet
{
    int numSet;
    ElementType* sarr;
public:
    DisjointSet(int numSet);
    void setUnion(SetType root1, SetType root2);
    SetType find(ElementType x);
};

DisjointSet::DisjointSet(int n) {
    // To use union-by-size strategy, the array entry of each root contains the negative of the size of its tree
    numSet = n;
    sarr = new ElementType[numSet + 1];
    fill_n(sarr, numSet+1, -1);
}

void DisjointSet::setUnion(SetType root1, SetType root2) {
    // Union-by-size: always change the root of the smaller tree
    // (optional) union-by-rank: rank is the estimated height of each tree

    if (sarr[root1] <= sarr[root2]) {
        sarr[root1] += sarr[root2];
        sarr[root2] = root1;
    } else {
        sarr[root2] += sarr[root1];
        sarr[root1] = root2;
    }
}

SetType DisjointSet::find(ElementType x) {
    // Path compression is performed during a Find operation and is independent of the strategy used to perform Unions. The effect of path compression is that every node on the path from X to the root has its paretn changed to the root.
    // If the union is done by size, the depth of any node is never more than logN. This implies that the running time for a Find operation is O(logN), and a sequence of M operation is O(MlogN).

    if (sarr[x] <= -1) {
        return x;
    }
    return sarr[x] = this->find(sarr[x]);
}

int main() {
    DisjointSet* disjSet = new DisjointSet(10);
    disjSet->setUnion(5,6);
    disjSet->setUnion(7,8);
    disjSet->setUnion(5, disjSet->find(8));
    disjSet->setUnion(4, disjSet->find(8));
    disjSet->setUnion(2,3);
    for (int i = 1; i <= 10; ++i) {
        printf("%d:%d\n", i, disjSet->find(i));
    }

    return 0;
}