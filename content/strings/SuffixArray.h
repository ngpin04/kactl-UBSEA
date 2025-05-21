/**
 * Author: 罗穗骞, chilli
 * Date: 2019-04-11
 * License: Unknown
 * Source: Suffix array - a powerful tool for dealing with strings
 * (Chinese IOI National team training paper, 2009)
 * Description: Builds suffix array for a string.
 * \texttt{sa[i]} is the starting index of the suffix which
 * is $i$'th in the sorted suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * The \texttt{lcp} array contains longest common prefixes for
 * neighbouring strings in the suffix array:
 * \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}.
 * The input string must not contain any zero bytes.
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

struct SufArr {
	vector<int> sa;
	vector<int> pos;
	vector<int> lcp;
	string s;
	int n;

	SufArr(string _s) {
		s = ' ' + _s;
		n = _s.size();
		buildSA();
		buildLCP();
	}

	void buildSA() {
		sa.assign(n + 1, 0); pos.assign(2 * n + 1, 0);
		iota(ALL(sa), 0);
		sort(ALL(sa), [&](int i, int j) {
			return s[i] < s[j];
		});
		iota(ALL(pos), 0);

		for (int i = 1; i <= n; i++) {
			int u = sa[i]; int v = sa[i - 1];
			pos[u] = (s[u] == s[v]) ? pos[v] : i;
		}

		for (int len = 1; len <= n; len <<= 1) {
			vector <int> tsa(sa), tpos(pos), ptr(n + 1, 0);
			iota(ALL(ptr), 0);

			for (int i = n + 1; i <= n + len; i++)
				sa[ptr[pos[i - len]]++] = i - len;

			for (int i : tsa) 
				if (i >= len)
					sa[ptr[pos[i - len]]++] = i - len;
		
			for (int i = 1; i <= n; i++) {
				int u = sa[i], v = sa[i - 1];
				pos[u] = 
				(tpos[u] == tpos[v] &&  tpos[u + len] == tpos[v + len]) ? 
				pos[v] : i;
			}
		}

		// for (int x : sa)
		// 	cerr << x << " ";
	}

	void buildLCP() {
		lcp.assign(n, 0);
		for (int i = 1; i <= n; i++) if (pos[i] < n) {
			int &res = lcp[pos[i]];
			if (pos[i - 1] < n)
				res = max(0, lcp[pos[i - 1]] - 1);
			int j = sa[pos[i] + 1];
			while (max(i, j) + res <= n && s[i + res] == s[j + res])
				res++;
		}
	}
};