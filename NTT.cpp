// Number Theory Transform
// UOJ 34
// Polynomial Multiplication
#include <bits/stdc++.h>
#define REP(i, a, b) for (int i = a; i <= b; ++i)
#define PER(i, a, b) for (int i = a; i >= b; --i)
#define RVC(i, S) for (int i = 0; i < S.size(); ++i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__)
using namespace std;

typedef pair<int, int> pii;
typedef long long LL;
typedef vector<int> VI;

inline int read(){
	int x = 0, ch = getchar(), f = 1;
	while (!isdigit(ch)){if (ch == '-') f = -1; ch = getchar();}
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}

const int N = 500005, mo = 998244353, g = 3;

int rev[N];
LL A[N], B[N];

LL pwr(LL a, LL b){
	LL res = 1;
	for (; b; b >>= 1, (a *= a) %= mo)
		if (b & 1) (res *= a) %= mo;
	return res;
}

void NTT(LL *a, int n, int d = 1){
	REP(i, 0, n - 1) if (i > rev[i]) swap(a[i], a[rev[i]]);
	for (int m = 2; m <= n; m <<= 1){
		LL wm = pwr(g, d * (mo - 1) / m + mo - 1);
		for (int i = 0; i < n; i += m){
			LL w = 1;
			for (int j = i; j < i + m / 2; ++j){
				LL u = a[j], v = w * a[j + m / 2];
				a[j] = (u + v) % mo;
				a[j + m / 2] = (u - v + mo) % mo;
				w = w * wm % mo;
			}
		}
	}
	LL inv = pwr(n, mo - 2);
	if (d == -1) REP(i, 0, n - 1) a[i] = a[i] * inv % mo;
}

int main(){
	int n = read(), m = read();
	REP(i, 0, n) A[i] = read();
	REP(i, 0, m) B[i] = read();
	int len = 1;
	for (; len <= n + m + 1; len <<= 1);
	REP(i, 1, len - 1)
		if (i & 1) rev[i] = (rev[i >> 1] >> 1) ^ (len >> 1);
		else rev[i] = (rev[i >> 1] >> 1);
	NTT(A, len); NTT(B, len);
	REP(i, 0, len - 1) A[i] = A[i] * B[i] % mo;
	NTT(A, len, -1);
	REP(i, 0, n + m) printf("%lld ", (A[i] + mo) % mo);
	printf("\n");
	return 0;
}
