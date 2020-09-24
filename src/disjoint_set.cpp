// a disjoint-set data structure, also called a union–find data structure or
// merge–find set, is a data structure that keeps track of a set of elements
// partitioned into a number of disjoint (nonoverlapping) subsets.

// Disjoint-set forests
// The first improvement: union by rank
void MakeSet(DataType x) {
    x.parent = x;
    x.rank = 0;
}

void Union(DataType x, DataType y) {
    DataType xRoot = Find(x);
    DataType yRoot = Find(y);
    if (xRoot == yRoot) return;
    // x and y are not already in same set. Merge them.
    if (xRoot.rank < yRoot.rank)
        xRoot.parent = yRoot;
    else if (xRoot.rank > yRoot.rank)
        yRoot.parent = xRoot;
    else {
        yRoot.parent = xRoot;
        xRoot.rank = xRoot.rank + 1;
    }
}

// The second improvement: path compression
DataType Find(DataType x) {
    if (x.parent != x) x.parent = Find(x.parent);
    return x.parent;
}

//常用比赛代码
int parent[MAXN + 1];
void initial() {
    for (int i = 1; i <= MAXN; i++) parent[i] = i;
    return;
}

int Find(int n) {
    if (parent[n] != n) parent[n] = Find(parent[n]);
    return parent[n];
}
