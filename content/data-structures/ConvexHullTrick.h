/**
 * Convexhull Trick
 * tested with https://www.acmicpc.net/problem/11001\
 * Author: me
 * Description: add lines by increasing order of (slope, y-inter) for max query and vice versa
 */
#pragma once

template <typename T> 
struct CHT {
	vector <pair <T, T>> hull;
	vector <long double> inters;
	int n, ptr;

	CHT() {
		inters.push_back(-1e18);
		ptr = 0, n = 0;
	}

	long double inter(pair <T, T> a, pair <T, T> b) {
		return -(long double) (a.se - b.se) / (a.fi - b.fi);
	}

	bool ok(pair <T, T> a, pair <T, T> b, pair <T, T> c) {
		return inter(a, c) <= inter(b, c);
	}

	void add(pair <T, T> line) {
		while (n > 0 && line.fi == hull.back().fi) {
			hull.pop_back();
			n--;
			if (inters.size() > 1) {
				inters.pop_back();
			}
		}

		while (n > 1 && !ok(hull[n - 2], hull[n - 1], line)) {
			n--;
			hull.pop_back();
			inters.pop_back();
		}	

		if (n > 0) {
			inters.push_back(inter(line, hull.back()));
		}
		hull.push_back(line);
		n++;
		mini(ptr, n - 2);
	}

	// query with binary search
	T querybin(T x) {
		assert(n > 0);
		int it = upper_bound(ALL(inters), x) - inters.begin() - 1;
		return hull[it].fi * x + hull[it].se;
	}

	// query with pointer, only when x is non-decreasing.
	T queryptr(T x) {
		assert(n > 0);
		while (ptr + 1 < (int) inters.size() && x >= inters[ptr + 1]) {
			ptr++;
		}

		return hull[ptr].fi * x + hull[ptr].se;
	}
};