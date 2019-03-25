#include <iostream>
#include <queue> // std:priority_queue

using namespace std;

class Point 
{
    int x;
    int y;
public:
    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }
    int getX() const { return x; }
    int getY() const { return y; }
};

class MyComparison
{
    bool operator() (const Point& p1, const Point& p2) const {
        return p1.getX() > p2.getX();
    }
};

int main() {

    // by default it is max heap
    priority_queue<int> maxHeap;
    // to create a min heap, priority_queue <Type, vector<Type>, ComparisonType>
    priority_queue<int, vector<int>, greater<int>> minHeap;
    // make a min heap of user defined class
    priority_queue<Point, vector<Point>, MyComparison> userHeap;

    // commonly used operations
    maxHeap.push(20);
    cout << maxHeap.top() << endl;
    maxHeap.pop();

    return 0;
}