#include <cstdio>
#include <list>
#include <queue>
#include <algorithm>
using namespace std;

// A topological sort is an ordering of vertices in a directed acyclic graph, such that if there is a path from v_i to v_j, then v_j appears after v_i in the ordering. It's clear that a topological ordering is not possible if the graph has a cycle
// A simple algorithm to find a topological ordering is first to find any vertex with no incoming edges. We can then print this vertex, and remove it, along with its edges, from the graph. Then we apply this same stragegy to the rest of the graph.
// The time to perform the algorithm is O(|E|+|V|).

class Graph {
    int V;                          // number of vertices
    list<int> *adj;                 // adjacency list
public:
    Graph(int n);                   // constructor
    ~Graph();                       // deconstructor
    void addEdge(int v, int w);     // function to add an edge to the graph
    void topologicalSort();         // function to perform the topological sort
};

Graph::Graph(int _v) {
    V = _v;
    adj = new list<int>[V];
}

Graph::~Graph() {
    delete [] adj;
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); // add w to v's adjacency list
}

void Graph::topologicalSort() {
    bool *visited = new bool[V];
    fill_n(visited, V, false);
    int *ingress = new int[V];
    fill_n(ingress, V, 0);

    int counter = 0;
    queue<int> q;

    // initialize ingress array
    for (int i = 0; i < V; i++) {
        for (auto v: adj[i]) {
            ingress[v] ++;
        }
    }

    for (int i = 0; i < V; i++) {
        if (ingress[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        // printf("%d ", v);
        counter ++;
        for (auto w: adj[v]) {
            if (--ingress[w] == 0) {
                q.push(w);
            }
        }
    }

    if (counter != V) {
        printf("Graph has a cycle.\n");
    }
    
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
  
    printf("Following is a Topological Sort of the given graph \n"); 
    g.topologicalSort(); 
  
    return 0; 
} 