#include <cstdio>
#include <list>
#include <queue>
using namespace std;

// The unweigted shortest-path problem is given as an in put a unweighted graph, G=(V,E), and a distinguished vertex, s, find the shortest path from s to every other vertex in G.
// We use the breadth-first search strategy to find the shortest-path in unweighted graph. It operates by processing vertices in layers: the vertices closest to the start are evealuated first, and the most distant vertices are evaluated last.
// The running time is O(|E|+|V|).

struct Record
{
    bool visited;
    int dist;
    int path;
};

class Graph 
{
    int V;                          // number of vertice
    list<int> *adj;                 // adjacency list
    Record *tb;                      // maintain the table to do simple bookkeeping
public:
    Graph(int v);                   // constructor
    ~Graph();                       // deconstructor
    void addEdge(int v, int w);     // function to add an edge to the graph
    void shortestPath(int s);       // function to find the shortest path from s to every other vertex
    void printPath(int v);               // function to print the path recursively
};

Graph::Graph(int v) {
    V = v;
    adj = new list<int>[V];
    tb = new Record[V];
}

Graph::~Graph() {
    delete [] adj;
    delete [] tb;
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

void Graph::shortestPath(int s) {
    // init table
    for (int i = 0; i < V; i++) {
        tb[i].visited = false;
        tb[i].dist = -1;
        tb[i].path = -1;
    }
    
    queue<int> q;
    q.push(s);
    tb[s].visited = true;
    tb[s].dist = 0;
    tb[s].path = s;

    int count = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        
        for (auto w : adj[v]) {
            if (!tb[w].visited) {
                q.push(w);
                tb[w].visited = true;
                tb[w].dist = tb[v].dist + 1;
                tb[w].path = v;
            }
        }
        count ++;
    }

    if (count < V) {
        printf("Graph G is not connected");
    }
}

void Graph::printPath(int v) {
    if (!tb[v].visited) {
        printf("%d is not visited.", v);
        return;
    }
    if (tb[v].path != v) {
        this->printPath(tb[v].path);
        printf(" to ");
    }
    printf("%d", tb[v].path);
}

int main() 
{ 
    // Create a graph given in the above diagram 
    Graph g(6); 
    g.addEdge(5, 2); 
    g.addEdge(5, 0); 
    g.addEdge(4, 0); 
    g.addEdge(4, 1); 
    g.addEdge(2, 3); 
    g.addEdge(3, 1); 
  
    printf("Following is to find the shortest path from source 5 of the given unweighted graph \n"); 
    g.shortestPath(5); 

    for (int i = 0; i < 6; i++) {
        g.printPath(i);
        printf("\n");
    }
  
    return 0; 
} 