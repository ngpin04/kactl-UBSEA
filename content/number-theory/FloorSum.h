/**
 * Signature: floor_sum(n, m, a, b)
 * Usage: Calculate sum of (a * i + b) / m for i from 0 to n - 1
 * Complexity: O(log(a) + log(m))
 * Copied from https://atcoder.jp/contests/practice2/submissions/18805092
 */
#pragma once

ll floor_sum(ll n, ll m, ll a, ll b) {
	ll ans = 0;
	if (a >= m) {
		ans += (n - 1) * n * (a / m) / 2;
		a %= m;
	}
	if (b >= m) {
		ans += n * (b / m);
		b %= m;
	}

	ll mx = a * (n - 1) + b;
	if (mx < m) return ans;
	ll dv = mx / m;
	ll md = mx % m;
	ans += dv + floor_sum(dv, a, m, md);
	return ans;
};	