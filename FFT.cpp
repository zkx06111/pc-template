// Fast Fourier Transform
// UOJ 34
// Polynomial multiplication in O(n log n)
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

const double pi = acos(-1);
const int N = 500005;

struct cpx{
	double x, y;
	cpx(double _x = 0, double _y = 0){x = _x, y = _y;}
	cpx operator + (const cpx &a){return cpx(x + a.x, y + a.y);}
	cpx operator - (const cpx &a){return cpx(x - a.x, y - a.y);}
	cpx operator * (const cpx &a){return cpx(x * a.x - y * a.y, x * a.y + y * a.x);}
} A[N], B[N];

int rev[N];

void FFT(cpx *a, int n, int d = 1){
	REP(i, 0, n - 1) if (i > rev[i]) swap(a[i], a[rev[i]]);
	for (int m = 2; m <= n; m <<= 1){
		cpx wm = cpx(cos(2 * pi / m), d * sin(2 * pi / m));
		for (int i = 0; i < n; i += m){
			cpx w = cpx(1, 0);
			for (int j = i; j < i + m / 2; ++j){
				cpx u = a[j], v = w * a[j + m / 2];
				a[j] = u + v;
				a[j + m / 2] = u - v;
				w = w * wm;
			}
		}
	}
	if (d == -1) REP(i, 0, n - 1) A[i].x /= n;
}

int main(){
	int n = read(), m = read();
	REP(i, 0, n) A[i].x = read();
	REP(i, 0, m) B[i].x = read();
	int len = 1;
	for (; len <= n + m + 1; len <<= 1);
	REP(i, 1, len - 1)
		if (i & 1) rev[i] = (rev[i >> 1] >> 1) ^ (len >> 1);
		else rev[i] = (rev[i >> 1] >> 1);
	FFT(A, len); FFT(B, len);
	REP(i, 0, len - 1) A[i] = A[i] * B[i];
	FFT(A, len, -1);
	REP(i, 0, n + m) printf("%d ", (int)trunc(A[i].x + 0.432));
	printf("\n");
	return 0;
}
