#include <bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define bit(n) (1LL << (n))
#define getbit(x, i) (((x) >> (i)) & 1)
#define pii pair<int, int>
#define ALL(x) x.begin(), x.end()
#define lb lower_bound
#define ub upper_bound
#define rep(i, a, b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 2e5 + 5;
const int mod = 1e9 + 7;
const int oo = 1e9;
const long long ooo = 1e18;
const double pi = acos(-1);

template<typename T1, typename T2> bool mini(T1 &a, T2 b) {if(a > b) a = b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b) {if(a < b) a = b; else return 0; return 1;}

typedef long long ll;
typedef vector <int> vi;

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());

long long rand(long long l, long long r) {
    return l + rd() % (r - l + 1);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    // g++ main.cpp -o main && ./main < file.inp
    return 0;
}