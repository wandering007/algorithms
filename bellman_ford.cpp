// The Bellman–Ford algorithm is slower than Dijkstra's algorithm, but capable
// of handling graphs in which some of the edge weights are negative numbers.
// Bellman–Ford runs in {\displaystyle O(|V|\cdot |E|)} O(|V|\cdot |E|) time,
// where {\displaystyle |V|} |V| and {\displaystyle |E|} |E| are the number of
// vertices and edges respectively. Part of code is copied from
// https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/ a structure to
// represent a weighted edge in graph
#include <stdio.h>
#include <limits.h>

struct Edge {
    int src;
    int dest;
    int weight;
};

// a structure to represent a connected, directed and
// weighted graph
struct Graph {
    // V-> Number of vertices, E-> Number of edges
    int V, E;

    // graph is represented as an array of edges.
    struct Edge* edges;
};

// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edges = new Edge[E];
    return graph;
}

bool BellmanFord(const struct Graph* graph, const int src, int* dist) {
    int V = graph->V;
    int E = graph->E;
    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;
    // Step 2: Relax all edges |V| - 1 times. A simple shortest
    // path from src to any other vertex can have at-most |V| - 1
    // edges
    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edges[j].src;
            int v = graph->edges[j].dest;
            int weight = graph->edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
    // Step 3: check for negative-weight cycles.  The above step
    // guarantees shortest distances if graph doesn't contain
    // negative weight cycle.  If we get a shorter path, then there
    // is a cycle.
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            fprintf(stderr, "Graph contains negative weight cycle...\n");
            return false;
        }
    }
    return true;
}
