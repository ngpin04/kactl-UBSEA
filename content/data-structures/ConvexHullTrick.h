/**
 * Convexhull Trick
 * tested with https://www.acmicpc.net/problem/11001\
 * Author: me
 * Description: add lines by increasing order of (slope, y-inter) for max query and vice versa
 */
#pragma once

template <typename T> 
struct CHT {
    typedef pair<T, T> L;
	vector<L> hull;
    vector<int> ind;
	vector <long double> inters;
	int n, ptr;

	CHT() {
		inters.push_back(-1e18);
		ptr = 0, n = 0;
	}

	long double inter(L a, L b) {
		return -(long double) (a.se - b.se) / (a.fi - b.fi);
	}

	bool ok(L a, L b, L c) {
		return inter(a, c) <= inter(b, c);
	}

	void add(L line, int i) {
		while (n > 0 && line.fi == hull.back().fi) {
			hull.pop_back();
            ind.pop_back();
			n--;
			if (inters.size() > 1) {
				inters.pop_back();
			}
		}

		while (n > 1 && !ok(hull[n - 2], hull[n - 1], line)) {
			n--;
			hull.pop_back();
			inters.pop_back();
            ind.pop_back();
		}	

		if (n > 0) {
			inters.push_back(inter(line, hull.back()));
		}
		hull.push_back(line);
        ind.push_back(i);
		n++;
		mini(ptr, n - 2);
	}

	// query with binary search
	pair<T, int> querybin(T x) {
		assert(n > 0);
		int it = upper_bound(ALL(inters), x) - inters.begin() - 1;
		return {hull[it].fi * x + hull[it].se, ind[it]};
	}

	// query with pointer, only when x is non-decreasing.
	pair<T, int> queryptr(T x) {
		assert(n > 0);
		while (ptr + 1 < (int) inters.size() && x >= inters[ptr + 1]) {
			ptr++;
		}

		return {hull[ptr].fi * x + hull[ptr].se, ind[ptr]};
	}
};

