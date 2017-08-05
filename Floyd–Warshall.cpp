// The Floyd–Warshall algorithm is an algorithm for finding shortest paths in a 
// weighted graph with positive or negative edge weights (but with no negative cycles).
// A single execution of the algorithm will find the lengths (summed weights) of
// the shortest paths between all pairs of vertices, though it does not return details
// of the paths themselves. 
// The algorithm is also known as Floyd's algorithm, the Roy–Warshall algorithm,
// the Roy–Floyd algorithm, or the WFI algorithm.

// V: Number of vertices in the graph
int graph[V][V];

// Path reconstruction
/* 
   With simple modifications, it is possible to create a method to reconstruct
   the actual path between any two endpoint vertices.
*/
// let next be a |V| × |V| array of vertex indices initialized to null(-1)
// int next[V][V];

// Solves the all-pairs shortest path problem using Floyd Warshall algorithm
void floydWarshell(int graph[][V])
{
    /* dist[][] will be the output matrix that will finally have the shortest 
      distances between every pair of vertices */
    int dist[V][V], i, j, k;
 
    /* Initialize the solution matrix same as input graph matrix. Or 
       we can say the initial values of shortest distances are based
       on shortest paths considering no intermediate vertex. */
    for (i = 0; i < V; ++i)
        for (j = 0; j < V; ++j)
		{
			dist[i][j] = graph[i][j];
		//	if(i != j && graph[i][j] != INF)
		//		next[i][j] = j;
		}
 
    /* Add all vertices one by one to the set of intermediate vertices.
      ---> Before start of a iteration, we have shortest distances between all
      pairs of vertices such that the shortest distances consider only the
      vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
      ----> After the end of a iteration, vertex no. k is added to the set of
      intermediate vertices and the set becomes {0, 1, 2, .. k} */
    for (k = 0; k < V; ++k)
    {
        // Pick all vertices as source one by one
        for (i = 0; i < V; ++i)
        {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < V; ++j)
            {
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
				//	next[i][j] = next[i][k];
				}
            }
        }
    }
	return;
}

/*
void Path(int u, int v)
{
	if(-1 == next[u][v])
	{
		printf("No path available.\n");
		return;
	}
	int path[V] = {u};
	int e = 0;
    while(u != v)
	{
		u = next[u][v];
		path[++e] = u;
	}
    printPath(path, e);
    return;
}