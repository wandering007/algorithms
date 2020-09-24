// Segment tree is a tree data structure used for storing information about
// intervals, or segments. A segment tree for a set I of n intervals uses O(n
// log n) storage and can built in O(n log n) time. Segment trees support
// searching for all the intervals that contain a query point in O(log n + k), k
// being the number of retrieved intervals or segments.

#define LCHILD node << 1, l, m
#define RCHILD node << 1, m + 1, r
// Consider an array `arr` of size N, and a corresponding segtree `tree` with
// size >= 2*2^(ceil(log(N))) - 1, call build(1, 1, N, arr) to build and init
// the segment tree
void build(int node, int l, int r, const int arr[]) {
    if (l == r) {
        tree[node] = arr[l];
        return;
    }
    int m = (l + r) >> 1;
    build(LCHILD, arr);
    build(RCHILD, arr);
    push_up(node);
}

/* range sum */
void push_up(int node) { tree[node] = tree[node << 1] + tree[node << 1 | 1]; }
void push_down(int node, int len) {
    tree[node << 1] += lazy[node] * (len - (len >> 1));
    lazy[node << 1] += lazy[node];
    tree[node << 1 | 1] += lazy[node] * (len >> 1);
    lazy[node << 1 | 1] += lazy[node];
    lazy[node] = 0;
}

/* range max */
void push_up(int node) {
    tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
}
void push_down(int node) {
    tree[node << 1] += lazy[node];
    lazy[node << 1] += lazy[node];
    tree[node << 1 | 1] += lazy[node];
    lazy[node << 1 | 1] += lazy[node];
    lazy[node] = 0;
    return;
}

// Update single node, don't need to do lazy labeling
void updateSingle(int p, int delta, int node = 1, int l = 1, int r = N) {
    if (l == r) {
        tree[node] += delta;  // here we use sum updating
        return;
    }
    int m = (l + r) >> 1;
    if (p <= m)
        updateSingle(p, delta, LCHILD);
    else
        updateSingle(p, delta, RCHILD);
    push_up(node);
}

// segment update, lazy
void update(int L, int R, int delta, int node = 1, int l = 1, int r = N) {
    if (L <= l and r <= R) {
        tree[node] += delta * (r - l + 1);
        lazy[node] += delta;
        return;
    }
    if (lazy[node]) push_down(node, r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, delta, LCHILD);
    if (R > m) update(L, R, delta, RCHILD);
    push_up(node);
    return;
}

// range query, sum here
int query(int L, int R, int node = 1, int l = 1, int r = N) {
    if (L <= l and r <= R) return tree[node];
    if (lazy[node]) push_down(node, r - l + 1);
    int m = (l + r) >> 1, ans = 0;
    if (L <= m) ans += query(L, R, LCHILD);
    if (R > m) ans += query(L, R, RCHILD);
    return ans;
}

// The segment tree can be generalized to higher dimension spaces. The structure
// uses O(nlog^d n) storage, and answers queries in O(log^d n).
