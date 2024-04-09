/**
 * Convexhull Trick
 * have not been tested!!!!
 */
#pragma once

template <typename T> 
struct CHT {
	vector <pair <T, T>> hull;
	vector <double> inters;
	int n, ptr;

	CHT() {
		inters.push_back(-1e18);
		ptr = 0, n = 0;
	}

	double inters(pair <T, T> a, pair <T, T> b) {
		return -(double) (a.se - b.se) / (a.fi - b.fi);
	}

	bool ok(pair <T, T> a, pair <T, T> b, pair <T, T> c) {
		return inters(a, c) < inters(b, c);
	}

	void add(pair <T, T> line) {
		while (n > 0 && line.fi == hull.back().fi) {
			assert(line.se > hull.back().se);
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

		hull.push_back(line);
		inters.push_back(intersect(line, hull.back()));
		n++;
		mini(ptr, n - 2);
	}

	// query with binary search
	T querybin(T x) {
		assert(n > 0);
		int it = lower_bound(ALL(inters), x) - inters.begin();
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