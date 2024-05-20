/**
 * Author: me
 * Description: create a Z array from a string s
 * Time: O(n)
 * Status: stress-tested with https://judge.yosupo.jp/submission/60727
 */
#pragma once

vector <int> calc(string s) {
	int n = s.size();
	vector <int> z(n, 0);

	for (int i = 1, l = 0, r = 0; i < n; i++) {
		int &k = z[i];
		if (i < r)
			k = min(r - i, z[i - l]);

		while (i + k < n && s[k] == s[i + k])
			k++;

		if (i + k > r) {
			l = i;
			r = i + k;
		}
	}
	return z;
}
