// Dijkstra's algorithm is an algorithm for finding the shortest paths between
// nodes in a graph. This is asymptotically the fastest known single-source
// shortest-path algorithm for arbitrary directed graphs with unbounded
// non-negative weights. Worse-case performance: O(|E|+|V|\log |V|)

// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
#include <limits.h>

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[]) {
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min) min = dist[v], min_index = v;

    return min_index;
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void Dijkstra(int A[V][V], int src) {
    int dist[V];  // The output array.  dist[i] will hold the shortest
                  // distance from src to i

    bool sptSet[V];  // sptSet[i] will true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is
                     // finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++) dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int i = 0; i < V - 1; i++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && A[u][v] && dist[u] != INT_MAX &&
                dist[u] + A[u][v] < dist[v])
                dist[v] = dist[u] + A[u][v];
    }
}
