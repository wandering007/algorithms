//	Tarjan's off-line lowest common ancestors algorithm is an algorithm for
// computing lowest common ancestors for pairs of nodes in a tree, based on the
// union-find data structure.
// https://en.wikipedia.org/wiki/Tarjan%27s_off-line_lowest_common_ancestors_algorithm
// linear time
//	A practical version
typedef struct node {
    int v;
    node *next;
} node;

//	Find for a disjoint-set forest.

int Find(int x) {
    if (Ances[x] == x) return x;
    return Ances[x] = Find(Ances[x]);
}

void Tarjan(int u) {
    color[u] = BLACK;
    Ances[u] = u;

    for (int i = 0; i < query[u].size(); ++i) {
        // id[u][i] is the No. of query[u][i]
        if (BLACK == color[query[u][i]]) LCA[id[u][i]] = Find(query[u][i]);
    }

    for (node *p = children[u]; p != NULL; p = p->next) {
        if (BLACK != [p->v]) {
            Tarjan(p->v);
            Ances[p->v] = u;
        }
    }
    return;
}
