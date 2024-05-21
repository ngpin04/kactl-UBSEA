/**
 * Author: me
 * Description: FFT of two vector a and b
 * Tested judge.yosupo.jp/problem/convolution_mod
 */
#pragma once

typedef long long ll;


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