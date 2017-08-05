//线索二叉树
typedef struct  BiThrNode
{
	TelemType data;
	struct BiThrNode *lchild, *rchild;
	int LTag,RTag;
};BiThrNode,*BiThrTree;
//以结点p为根的子树中序线索化
void InThreading(BiThrTree p)
{//pre是全局变量，初始化时其右孩子指针为空，便于左树的最左点开始建线索
	if(p)
	{
		InThreading(p->lchild);
		if(!p->lchild)
		{
			p->LTag = 1;
			p->lchild = pre;
		}
		if(!pre->rchild)
		{
			pre->RTag = 1;
			pre->rchild = p;
		}
		pre = p;
		InOrderThreading(p->rchild);
	}
}
//带头结点的中序线索化
void InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	Thrt = new BiThrNode;
	Thrt->LTag = 0;
	Thrt->RTag = 1;
	Thrt->rchild = Thrt;
	if(!T) Thrt->rchild = Thrt;
	else 
	{
		Thrt->lchild = T;
		pre = Thrt;
		InTreading(T);
		pre->rchild = Thrt;
		pre->RTag = 1;
		Thrt->rchild = pre;
	}
}