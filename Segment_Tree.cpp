//Segment Tree

#define LCHILD rt << 1, l, m
#define RCHILD rt << 1, m + 1, r
//新建一棵长度N的线段树
void build(int rt = 1, int l = 1, int r = N) //这种写法虽然方便，但是有风险，在工程中慎用
{
    if (l == r) 
    	{ 
    		cin >> tree[rt];//视具体情况更改
    		return; 
    	}
    int m = (l + r) >> 1;
    build(LCHILD); 
    build(RCHILD);
    push_up(rt);
}

/* 对于区间求和 */
void push_up(int rt) 
{
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}
void push_down(int rt, int len) {
    tree[rt << 1] += lazy[rt] * (len - (len >> 1));
    lazy[rt << 1] += lazy[rt];
    tree[rt << 1 | 1] += lazy[rt] * (len >> 1);
    lazy[rt << 1 | 1] += lazy[rt];
    lazy[rt] = 0;
} 

/* 对于区间求最大值 */
void push_up(int rt) 
{
    tree[rt] = max(tree[rt << 1], tree[rt << 1 | 1]);
}
void push_down(int rt) 
{
    tree[rt << 1] += lazy[rt];
    lazy[rt << 1] += lazy[rt];
    tree[rt << 1 | 1] += lazy[rt];
    lazy[rt << 1 | 1] += lazy[rt];
    lazy[rt] = 0;
    return;
}

//单点更新, 不需要用到lazy标记
void update(int p, int delta, int rt = 1, int l = 1, int r = N) 
{
    if (l == r) 
    {
        tree[rt] += delta;//视情况而定
        return;
    }
    int m = (l + r) >> 1;
    if (p <= m) update(p, delta, LCHILD);
    else update(p, delta, RCHILD);
    push_up(rt);
}

//成段更新, 需要用到lazy标记来提高时间效率
void update(int L, int R, int delta, int rt = 1, int l = 1, int r = N) {
    if (L <= l && r <= R) 
    {
        tree[rt] += delta * (r - l + 1);
        lazy[rt] += delta;
        return;
    }
    if (lazy[rt]) push_down(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, delta, LCHILD);
    if (R > m)  update(L, R, delta, RCHILD);
    push_up(rt);
    return;
}

//区间查询
int query(int L, int R, int rt = 1, int l = 1, int r = N) 
{
    if (L <= l && r <= R) return tree[rt];
    if (lazy[rt]) push_down(rt, r - l + 1);
    int m = (l + r) >> 1, ans = 0;
    if (L <= m) ans += query(L, R, LCHILD);
    if (R > m)  ans += query(L, R, RCHILD);
    return ans;
}

//二维线段树即是树套树，自己感悟

//请多做题，验证模板的正确性