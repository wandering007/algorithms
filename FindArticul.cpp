void DFSArticul(ALGraph G,int v0)
{
	visited[v0] = min = ++count;
	for(p=G.vertives[v0].firstarc;p;p=p->nextarc)
	{
	w = p->adjvex;
	if(0==visited[w])
	{
	DFSArticul(G,w);
	if(low[w]<min)min = low[w];
	if(low[w]>=visited[v0]) printf(v0,G.vertices[v0].data);
	}
	else if(visited[w]<min) min = visited[w];
	}
	low[v0] = min;
}//DFSArticul

void FindArticul(ALGraph G)
{
	count = 1;
	visited[0] = 1;
	for(i=0;i<G.vexnum;++i)visited[i] = 0;
	p = G.vertices[0].firstarc;
    v = p->adjvex;
    DFSArticul(G,v);
    if(count<G.vexnum)
    {
    	printf(0,G.vertices[0].data);
    	while(p->nextarc)
    	{
    		p=p->nextarc;
    		v=p->adjvex;
    		if(0==visited[v]) DFSArticul(G,v);
    	}
    }
}