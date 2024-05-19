/**
 * Description: 
 * Time: O(N)
 * Status: Stress-tested
 */
#pragma once

auto manacher = [&](string s) {
	string str;
	for (char c : s) {
		str += '#';
		str += c;
	}
	str += '#';
	int n = str.size();
	vector <int> f(n, 0);

	for (int i = 0, l = 0, r = -1; i < n; i++) {
		int &k = f[i];
		k = (i < r) ? min(f[l + r - i], r - i) : 1;
		while (i - k >= 0 && i + k < n && str[i - k] == str[i + k])
			k++;

		if (i + k > r) {
			l = i - k;
			r = i + k;
		}
	}
	return f;
};       
 