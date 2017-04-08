/*=================================
# Created time: 2017-01-10 13:47
# Filename: 1519_1.cpp
# Description: 
=================================*/
#define me AcrossTheSky&HalfSummer11  
#pragma GCC optimize(2)
#include <cstdio>  
#include <cmath>  
#include <ctime>  
#include <string>  
#include <cstring>  
#include <cstdlib>  
#include <iostream>  
#include <algorithm>  
  
#include <set> 
#include <stack>  
#include <queue>  
#include <vector>  
 
#define pb push_back 
#define lb lower_bound 
#define sqr(x) (x)*(x) 
#define lowbit(x) (x)&(-x)  
#define Abs(x) ((x) > 0 ? (x) : (-(x)))  
#define FOR(i,a,b) for((i)=(a);(i)<=(b);(i)++)  
#define FORP(i,a,b) for(int i=(a);i<=(b);i++)  
#define FORM(i,a,b) for(int i=(a);i>=(b);i--)  
#define ls(a,b) (((a)+(b)) << 1)  
#define rs(a,b) (((a)+(b)) >> 1)  
#define getlc(a) ch[(a)][0]  
#define getrc(a) ch[(a)][1]  
  
#define maxn 1000005 
#define maxm 100005 
#define INF 1070000000  
using namespace std;  
typedef long long ll;  
typedef unsigned long long ull;  
  
template<class T> inline  
void read(T& num){  
    num = 0; bool f = true;char ch = getchar();  
    while(ch < '0' || ch > '9') { if(ch == '-') f = false;ch = getchar();}  
    while(ch >= '0' && ch <= '9') {num = num * 10 + ch - '0';ch = getchar();}  
    num = f ? num: -num;  
} 
int out[100]; 
template<class T> inline 
void write(T x,char ch){ 
	if (x==0) {putchar('0'); putchar(ch); return;} 
	if (x<0) {putchar('-'); x=-x;} 
	int num=0; 
	while (x){ out[num++]=(x%10); x=x/10;} 
	FORM(i,num-1,0) putchar(out[i]+'0'); putchar(ch); 
} 
/*==================split line==================*/ 
const double eps=1e-8; 
const int HASH = 30007;
int n, m, x, y, now, nex, nx, ny;
char c[20];
int a[10], b[10];
int g[20][20];
struct Node{
	int sz, first[HASH], next[maxn];
	ll h, s[maxn], v[maxn];
	void clr(){sz = 0; memset(first, 0, sizeof(first));}
	ll push(ll S, ll val){
		h = S % HASH;
		for (int i = first[h]; i; i = next[i]) 
			if (s[i] == S) return v[i] = max(v[i], val);
		sz++; v[sz] = val; s[sz] = S;
		next[sz] = first[h]; first[h] = sz; 
		return val;
	}
}f[2];
void decode(ll s){FORP(i, 0, m) a[i] = s & 7, s >>= 3;}
ll encode(){
	int k = 0; ll s = 0; FORP(i, 0, 8) b[i] = 0;
	FORP(i, 0, m) if (a[i]) a[i] = b[a[i]] ? b[a[i]] : b[a[i]] = ++k;
	FORM(i, m, 0) s <<= 3, s|= a[i];
	//write(s,'\n');
	return s;
}
void up(int u, int v, ll val){
	if (x && y){
		if ( x != y){
			FORP(i, 0, m) if (a[i] == y) a[i] = x;
			a[0] = a[v] = 0;
			f[nex].push(encode(), val + g[u][v]);
		}
	}
	else if (x || y){
		//x = max(x, y);
		//a[0] = 0; a[v] = x;
		f[nex].push(encode(), val + g[u][v]);
		swap(a[0], a[v]);
		f[nex].push(encode(), val + g[u][v]);
	}
	else {
		f[nex].push(encode(), val);
		a[0] = a[v] = 7;
		f[nex].push(encode(), val + g[u][v]);
	}
}
int cas = 0;
void work(){
	//if (nx == 0) {puts("0"); return;}
	FORP(i, 1, n)
		FORP(j, 1, m){
			f[nex].clr();
			//printf("%d %d %d\n", i, j, f[now].sz);
			FORP(k, 1, f[now].sz){
				decode(f[now].s[k]);
	//			FORP(l, 0, m) write(a[l],' '); puts("");
				x = a[0], y = a[j];
				if (j == 1 && a[0]) continue;
				if (i == n && j == m && (x && y)) continue;
				up(i, j, f[now].v[k]);
				//else if (!x && !y) f[nex].push(f[now].s[k], f[now].v[k]);
	//			printf("%d %d %lld %lld\n", i, j, f[now].s[k], f[now].v[k]);
			}
			swap(now, nex);
		}
	memset(a, 0, sizeof(a)); a[m] = 1;
	printf("Case %d: ", cas); write(f[now].push(encode(), -INF),'\n');
}
void init(){
	nx = 0;
	memset(g, 0, sizeof(g));
	FORP(i, 1, n)
		FORP(j, 1, m) read(g[i][j]);
	f[0].clr();
	now = 0, nex = 1;
	memset(a, 0, sizeof(a)); a[1] = 1;
	f[0].push(encode(), 0);
}
int main(){
	freopen("3377.in","r",stdin);
	//freopen("tmp.out","w",stdout);
	while (cin >> n >> m){
		cas++;
		init();
		work();
	}
	return 0;
}
