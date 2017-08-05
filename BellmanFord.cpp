bool BellmanFord(int MAX_VERTEXS, int MAX_EDGES, int v)
{//Single sourse all destination shortest paths with negative edge lengths
	for(int i=0;i<MAX_VERTEXS;i++)
		dist[i] = length[v][i];//initialize dist
	for(int k=2; k<MAX_VERTEXS; k++)
		for(int j=0;j<MAX_EDGES; j++)
			{
				if(dist[j].u!=INFINIT&&dist[edge[j].u]+length[edge[j].u][edge[j].v]<dist[edge[j].v])
					dist[edge[j].v] = dist[edge[j].u]+length[edge[j].u][edge[j].v];
			}
	for(int i=0; i<MAX_EDGES; i++)
		if(dist[j].u!=INFINIT&&dist[edge[i].u]+length[edge[i].u][edge[i].v]<dist[edge[i].v])
			return FAlSE;
	return TRUE;
}