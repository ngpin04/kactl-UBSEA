#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define bit(n) (1LL << (n))
#define getbit(x, i) (((x) >> (i)) & 1)
#define pii pair<int, int>
#define ALL(x) (x).begin(), (x).end()
#define sz(x) ((int) (x).size())
using namespace __gnu_pbds;
using namespace std;
const int M = 5e5 + 5;
const int N = 2e5 + 5;
const int mod = 1e9 + 7;
const int oo = 1e9;
const long long ooo = 1e18;
const double pi = acos(-1);

template<typename T1, typename T2> bool mini(T1 &a, T2 b) {if(a > b) a = b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b) {if(a < b) a = b; else return 0; return 1;}

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;

ll rand(ll l, ll r) {
    return l + rd() % (r - l + 1);
}

int myrand(int i) {
    return rd() % i;
}

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return x ^ RANDOM; }
};
// USAGE: gp_hash_table<key, value, chash> table;



int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    return 0;
}