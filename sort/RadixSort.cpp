#define KEY_NUM 10    //关键字长度
#define RADIX   10     // 关键字基数，整数时为0-9
typedef struct Node{
KeyType key[KEY_NUM];  //关键字字段
OtherField otheritem;
Node *next;
} Node;  
typedef struct Queue{
Node *e;
Node *f;
}Queue;
Queue queue[READIX];
void Distribute_Radix(Node **head, int i){
Node *p;
//分配过程，序列链表*head已按关键字key[0], key[1],…, key[i-1]有序，
//本过程按第i个关键字建立子序列，使得同一子序列中的key[i]相等，
//queue[k]->e 和queue[k]->f分别指向第k个队列的第一个和最后一个数据
for(j=0; j<RADIX; ++j) 
	{queue[j]->e=null; queue[j]->f=null;}  //队列置空
for(p=*head; p!=null; p=p->next){
j=ord(p.key[i]);   //ord为取出p中第i个关键字字段
if(queue[j]->f==null) queue[j]->f=p;  //分配到相应队列中
else queue[j]->e->next=p;
Queue[j]->e=p;
}
}
void Collect_Radix(Node **head, int i){
//收集过程
//将queue[0], queue[1],…, queue[RADIX-1]所指序列收集起来形成新的链表
for(j=0; !queue[j]->f; ++j);  //寻找第一个非空队列
*head=queue[j]->f; t=queue[j]->e; 
 //第一个非空队列链入新的链表中
while(j<RADIX){
for(++j; j<RADIX-1 && !queue[j]->f; ++j);
 //寻找下一个非空队列
if(queue[j]->f){   //链接两个非空队列
t->next=queue[j]->f;
t=queue[j]->e;
}
}
t->next=null;  //t指向最后一个非空结点
}
void Radix_Sort(Node **head, int n){
//对*head做基数排序，使其称成为按关键字升序的链表，
//*head指向第一个数据结点
for(i=0;i<KEY_NUM; ++i){
Distribute_Radix(*head, i);
Collect_Radix(*head, i);
}
}