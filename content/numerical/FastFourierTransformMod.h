/**
 * Author: chilli
 * Date: 2019-04-25
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
 * Description: Higher precision FFT, can be used for convolutions modulo arbitrary integers
 * as long as $N\log_2N\cdot \text{mod} < 8.6 \cdot 10^{14}$ (in practice $10^{16}$ or higher).
 * Inputs must be in $[0, \text{mod})$.
 * Time: O(N \log N), where $N = |A|+|B|$ (twice as slow as NTT or FFT)
 * Status: stress-tested
 * Details: An in-depth examination of precision for both FFT and FFTMod can be found
 * here (https://github.com/simonlindholm/fft-precision/blob/master/fft-precision.md)
 */
#pragma once

typedef long long ll;
typedef complex<double> C;

void fft(vector<C>& a) {
	int n = a.size(), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		for (int i = k; i < 2 * k; i++) 
			rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vector <int> rev(n);
	for (int i = 0; i < n; i++) 
		rev[i] = (rev[i / 2] | (i & 1) << L) / 2;

	for (int i = 0; i < n; i++) 
		if (i < rev[i]) 
			swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
	for (int i = 0; i < n; i += 2 * k)  
	for (int j = 0; j < k; j++) {
		// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
		auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];		/// exclude-line
		C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);		   /// exclude-line
		a[i + j + k] = a[i + j] - z;
		a[i + j] += z;
	}
}

typedef vector<ll> vl;
template<int M> vl convMod(const vl &a, const vl &b) {

	vl res((int) a.size() + b.size() - 1);
	int B=32-__builtin_clz(res.size()), n=1<<B, cut=int(sqrt(M));
	
	vector<C> L(n), R(n), outs(n), outl(n);

	for (int i = 0; i < (int) a.size(); i++) 
		L[i] = C((int)a[i] / cut, (int)a[i] % cut);

	for (int i = 0; i < (int) b.size(); i++)  
		R[i] = C((int)b[i] / cut, (int)b[i] % cut);
	
	fft(L), fft(R);

	for (int i = 0; i < n; i++) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}

	fft(outl), fft(outs);
	
	for (int i = 0; i < (int) res.size(); i++) {
		ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
		ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);
		res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
	}
	return res;
}