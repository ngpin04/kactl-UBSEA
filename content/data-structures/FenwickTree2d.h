/**
 * Description: Computes sums a[i,j] for all i<I, j<J, and increases single elements a[i,j].
 *  Requires that the elements to be updated are known in advance (call fakeUpdate() before init()).
 * Time: $O(\log^2 N)$. (Use persistent segment trees for $O(\log N)$.)
 * Note: i > 0 and j > 0
 */
#pragma once

typedef vector <int> vi;

struct FT2 {
	int n;
	vector<vi> ys, ft;
	FT2(int _n) : n(_n), ys(n + 5), ft(n + 5) {}
	void fakeUpdate(int x, int y) {
		for (; x <= n; x += x & -x) ys[x].push_back(y);
	}
	void init() {
		for (int i = 1; i <= n; i++) 
			sort(ALL(ys[i])), ft[i].resize(ys[i].size() + 1);
	}
	int ind(int x, int y) {
		return (int)(upper_bound(ALL(ys[x]), y) - ys[x].begin()); }

	void update(int x, int y, int dif) {
		for (; x <= n; x += x & -x)
		for (int i = ind(x, y); i < (int) ft[x].size(); i += i & -i)
			ft[x][i] += dif;
	}

	int getsum(int x, int y) {
		int res = 0;
		for (; x; x -= x & -x)
		for (int i = ind(x, y); i > 0; i -= i & -i)
			res += ft[x][i];
		return res;
	}
};
