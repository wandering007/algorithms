void Dijkstra(int v, int cost[][MAX_VERTICES]), 
			int distance[], int n, bool found[]}//如果<i,j>不存在通路，cost[i][j]不宜取INT_MAX，只需大于代价矩阵的最大值
{/*distance[i] represents the shortest path from vertex v has not 
	been found and a 1 if it has, cost is the adjacency matrix */
	int i, u, w;
	for (i = 0; i < n; i++)
	{
		found[i] = FALSE;
		distance[i] = cost[v][i];
	}
	found[v] = true;
	distance[v] = 0;
	for(i=1; i<n; i++)
	{
		u = choose(distance, n, found);
		found[u] = true;
		for(w=0; w<n; w++)
			if(!found[w])
				if(distance[u]+cost[u][w]<distance[w])
					distance[w] = distance[u] + cost[u][w];
	}
}//单源点至所有其它节点最短路径，边权值非负
int choose(int distance[], int n, short int found[])
{//found the smallest distance not yet checked
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for(i=0; i<n; i++)
		if(distance[i]<min&&!found[i])
		{
			min = distance[i];
			minpos = i;
		}
	return minpos;
}//选取最小代价边