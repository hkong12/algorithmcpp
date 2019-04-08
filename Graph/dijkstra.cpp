#include <cstdio>
#include <list>
#include <queue>
#include <limits>
using namespace std;

// Dijkstra's algorithm is known as the general method to solve the single-source shortest-path problem. 
// Dijkstra's algorithm proceeds in stages. At each stage, Dijkstra's algorithm selects a vertex v, which has the smallest distance from v, d_v, among all the unknown vertices, and declares that the shortest path from s to v is known. The remainder of ths stage consists of updating the value of d_w (where w is adjacent to v) if new value d_w would be an improvement.
// The algorithm always works as long as no edge has a negative cost.
// The running time depends on how the table is manipulated. If we use the obvious algorithm of scanning down the table to find the minimum d_v, the running time would be O(|V|^2); if priority queue is used, the runnint time is O(|E|log|V|); if Fibonacci heap is used, the running time is O(|E|+|V|log|V).

typedef pair<int, int> iPair;

class PairComparison 
{
public:
    bool operator() (const iPair& a, const iPair& b) {
        return a.second > b.second;
    }
};

struct Record
{
    bool visited;
    int dist;
    int path;
};

class Graph 
{
    int V;                              // number of vertice
    list<iPair> *adj;                   // adjacency list
    Record *tb;                         // maintain the table to do simple bookkeeping
public:
    Graph(int v);                           // constructor
    ~Graph();                               // deconstructor
    void addEdge(int v, int w, int cost);   // function to add an edge to the graph
    void dijkstra(int s);                   // function to find the shortest path from s to every other vertex
    void printCost();                  // function to print the cost of path from s to every other vertex
};

Graph::Graph(int v) {
    V = v;
    adj = new list<iPair>[V];
    tb = new Record[V];
}

Graph::~Graph() {
    delete [] adj;
    delete [] tb;
}

void Graph::addEdge(int v, int w, int cost) {
    // undirected weighted graph
    adj[v].push_back(make_pair(w, cost));
    adj[w].push_back(make_pair(v, cost));
}

void Graph::dijkstra(int s) {
    // init table
    for (int i = 0; i < V; i++) {
        tb[i].visited = false;
        tb[i].dist = numeric_limits<int>::max();
        tb[i].path = -1;
    }

    // maintain a priority queue to store vertex w and the new value d_w. When the DeleteMin option removes the smallest vertex from the priority queue, it must be checked to make sure that it is not already known.
    priority_queue<iPair, vector<iPair>, PairComparison> pq;
    pq.push(make_pair(s, 0));
    tb[s].dist = 0;
    tb[s].path = s;

    while (!pq.empty()) {
        iPair p = pq.top();
        pq.pop();
        if (tb[p.first].visited) {
            continue;
        }
        int v = p.first;
        tb[v].visited = true;
        for (auto tmp: adj[v]) {
            int w = tmp.first;
            if (tb[v].dist + tmp.second < tb[w].dist) {
                tb[w].dist = tb[v].dist + tmp.second;
                tb[w].path = v;
                pq.push(tmp);
            }
        }
    }

}

void Graph::printCost() {
    for (int i = 0; i < V; i++) {
        printf("to vertex %i, the dist is %d.\n", i, tb[i].dist);
    }
}

int main() {
    int V = 9; 
    Graph g(V); 
  
    //  making above shown graph 
    g.addEdge(0, 1, 4); 
    g.addEdge(0, 7, 8); 
    g.addEdge(1, 2, 8); 
    g.addEdge(1, 7, 11); 
    g.addEdge(2, 3, 7); 
    g.addEdge(2, 8, 2); 
    g.addEdge(2, 5, 4); 
    g.addEdge(3, 4, 9); 
    g.addEdge(3, 5, 14); 
    g.addEdge(4, 5, 10); 
    g.addEdge(5, 6, 2); 
    g.addEdge(6, 7, 1); 
    g.addEdge(6, 8, 6); 
    g.addEdge(7, 8, 7); 
  
    g.dijkstra(0);

    g.printCost();
}