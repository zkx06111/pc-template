// Chinese Remainder Theorem
// Divisors are stored in array m, remainders are stored in array a
// Capable of dealing with the situation when divisors are not pairwise coprime
// Function CRT returns -1 when there is no solution
#include <iostream>
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define REP(i, a, b) for (int i = a; i <= b; ++i)
using namespace std;

typedef long long LL;
LL a[1005], m[1005];

void exgcd(LL a, LL b, LL &d, LL &x, LL &y) {
	if (b == 0) {x = 1, y = 0, d = a; return;}
	exgcd(b, a % b, d, y, x);
	y -= (a / b) * x;
}

LL merge(LL a1, LL m1, LL a2, LL m2, LL &a3, LL &m3) {
	LL p, q, dt = a2 - a1, d;
	exgcd(m1, m2, d, p, q);
	if (dt % d) return 0;
	(p *= dt / d) %= m2; //q *= dt / d;
	m3 = m1 * m2 / d;
	a3 = p * m1 % m3 + a1;
	a3 = (a3 % m3 + m3) % m3;
	return 1;
}

LL CRT(int n, LL *a, LL *m) {
	LL a1 = a[1], m1 = m[1], a2, m2;
	REP(i, 2, n) {
		if (!merge(a1, m1, a[i], m[i], a2, m2)) return -1;
		a1 = a2; m1 = m2;
	}
	return (a1 % m1 + m1) % m1;
}

int main() {
	int n;
	while (cin >> n) {
		REP(i, 1, n) cin >> m[i] >> a[i];
		cout << CRT(n, m, a) << endl;
	}
	return 0;
}
