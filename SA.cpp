// Suffix Array
#include <bits/stdc++.h>
#define REP(i, a, b) for (int i = a; i <= b; ++i)
#define PER(i, a, b) for (int i = a; i >= b; --i)
#define RVC(i, S) for (int i = 0; i < S.size(); ++i)
#define mp make_pair
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define fi first
#define se second
using namespace std;
 
typedef long long LL;
typedef pair<int, int> pii;
typedef vector<int> VI;

const int N = 100005;

int n, ca[N], cb[N], A[N], B[N], tsa[N], sa[N], rk[N], ht[N];
char str[N];

void getsa(){
	REP(i, 1, n) ca[str[i]]++;
	REP(i, 1, 255) ca[i] += ca[i - 1];
	PER(i, n, 1) sa[ca[str[i]]--] = i;
	rk[sa[1]] = 1;
	REP(i, 2, n){
		rk[sa[i]] = rk[sa[i - 1]];
		if (str[sa[i]] != str[sa[i - 1]]) ++rk[sa[i]];
	}
	for (int l = 1; rk[sa[n]] < n; l <<= 1){
		memset(ca, 0, sizeof ca);
		memset(cb, 0, sizeof cb);
		REP(i, 1, n){
			ca[A[i] = rk[i]]++;
			cb[B[i] = (i + l <= n ? rk[i + l] : 0)]++;
		}
		REP(i, 1, n) ca[i] += ca[i - 1], cb[i] += cb[i - 1];
		PER(i, n, 1) tsa[cb[B[i]]--] = i;
		PER(i, n, 1) sa[ca[A[tsa[i]]]--] = tsa[i];
		rk[sa[1]] = 1;
		REP(i, 2, n){
			rk[sa[i]] = rk[sa[i - 1]];
			if (A[sa[i]] != A[sa[i - 1]] || B[sa[i]] != B[sa[i - 1]]) ++rk[sa[i]];
		}
	}
	for (int i = 1, j = 0; i <= n; ++i){
		if (j) --j;
		while (str[i + j] == str[sa[rk[i] - 1] + j]) ++j;
		ht[rk[i]] = j;	
	}
}

int main(){
	scanf("%s", str + 1);	
	n = strlen(str + 1);
	getsa();
	REP(i, 1, n) printf("%d ", sa[i]); puts("");
	REP(i, 2, n) printf("%d ", ht[i]); puts("");
	return 0;
}
