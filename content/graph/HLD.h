/**
 * Time: O((\log N)^2)
 * Status: stress-tested against old HLD
 */
#pragma once

#include "../data-structures/LazySegmentTree.h"

int sz[lim], in[lim], out[lim], depth[lim], t, root[lim], par[lim];
vector<int> child[lim];
segment_tree segtree;
void dfs_sz(int nd) {
    sz[nd] = 1;
    for(auto &i : child[nd]) {
        depth[i] = depth[nd] + 1;
        dfs_sz(i);
        sz[nd] += sz[i];
        if(sz[i] > sz[child[nd][0]])
            swap(i, child[nd][0]);
    }
}
void dfs_hld(int nd) {
    in[nd] = ++t;
    segtree.update(in[nd], in[nd], depth[nd]);
    for(auto i : child[nd]) {
        root[i] = i == child[nd][0] ? root[nd] : i;
        dfs_hld(i);
    }
    out[nd] = t;
}
int query(int u, int v) {
    int ans = -1e9;
    while(root[u] != root[v]) {
        if(depth[root[u]] > depth[root[v]])
            swap(u, v);
        ans = max(ans, segtree.query(in[root[v]], in[v]));
        v = par[root[v]];
    }
    if(depth[u] > depth[v])
        swap(u, v);
    ans = max(ans, segtree.query(in[u], in[v]));
    return ans;
}
