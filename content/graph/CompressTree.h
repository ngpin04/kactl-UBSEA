/**
 * Author: Simon Lindholm
 * Date: 2016-01-14
 * Source: my head
 * Status: Tested at CodeForces
 * Description: Given a rooted tree and a subset S of nodes, compute the minimal
 * subtree that contains all the nodes by adding all (at most $|S|-1$)
 * pairwise LCA's and compressing edges.
 * Returns a list of (par, orig\_index) representing a tree rooted at 0.
 * The root points to itself.
 * Time: $O(|S| \log |S|)$
 */
#include "LCA.h"

vpi compressTree(LCA& lca, const vi& subset) {
	static vi rev; rev.resize(sz(lca.dist));
	vi li = subset, &T = lca.time;
	auto cmp = [&](int a, int b) { return T[a] < T[b]; };
	sort(all(li), cmp);
	rep(i,0,sz(li)-1) {
		int a = li[i], b = li[i+1];
		li.push_back(lca.query(a, b));
	}
	sort(all(li), cmp);
	li.erase(unique(all(li)), li.end());
	rep(i,0,sz(li)) rev[li[i]] = i;
	vpi ret = {pii(0, li[0])};
	rep(i,0,sz(li)-1) {
		int a = li[i], b = li[i+1];
		ret.emplace_back(rev[lca.query(a, b)], b);
	}
	return ret;
}