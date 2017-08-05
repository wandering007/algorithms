typedef struct
{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char** HuffmanCode;

void HuffmanCoding()
{
	//构造赫夫曼树HT
	if(n<=1) return;
	m = 2*n-1;
	int i, j, m, s1, s2, start;
  	char *cd;
  	unsigned int c, f;
	HuffmanTree p;
	HuffmanCode HC;
	HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));
	for(p=HT,i=1;i<=n;++i,++p,++w) *p = {*w, 0,0,0};
	for(;i<=m;++i,++p) *p = {0,0,0,0};
	for(i=n+1;i<=m;++i)
	{
		Select(HT,i-1,s1,s2);
		HT[s1].parenta = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	 //--- 从叶子到根逆向求每个字符的哈夫曼编码 ---
	HC = (HuffmanCode)malloc((n+1)*sizeof(char*));
	cd = (char*)malloc(n*sizeof(char));
	cd[n-1] = '\0';
	for(i=1;i<=n;++i)
	{
		start = n-1;
		for(c=i,f=HT[i].parent;f!=0;c=f, f = HT[f].parent)
			if(HT[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';
		HC[i] = (char*)malloc((n-start)*sizeof(char));
		strcpy(HC[i],&cd[start]);
	}
	free(cd);
}//HuffmanCoding

 //------无栈非递归遍历赫夫曼树，求哈夫曼编码
 HC = (HuffmanCode)malloc((n+1)*sizeof(char*));
 p = m;
 cdlen = 0;
 for(i=1;i<=m;++i)HT[i].weight = 0;
 while(p)
 {
 	if(0 == HT[p].weight)
 	{
 		HT[p].weight = 1;
 		if(HT[p].lchild!=0)
 			{p=HT[p].lchild; cd[cdlen++]='0';}
 		else if(0==HT[p].rchild)
 		{
 			HC[p] = (char*)malloc(cdlen+1)*sizeof(char);
 			cd[len] = '\0';
 			strcpy(HC[p],cd);
 		}
 	}
 	else if(1==HT[p].weight)
 	{
 		HT[p].weight = 2;
 		if(HT[p].rchild!=0){p = HT[p].rchild; cd[cdlen++] = '1';}
 	}
 	else 
 	{
 		HT[p].weight = 0;
 		p = HT[p].parent;
 		--cdlen;
 	} 	
 }