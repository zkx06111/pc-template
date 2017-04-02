// Network maxflow with dinic algorithm
// XIOJ 2
// Call Network::init() first
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

typedef long long LL;
typedef pair<int, int> pii;
typedef vector<int> VI;

inline int read(){
	int x = 0, ch = getchar(), f = 1;
	while (!isdigit(ch)){if (ch == '-') f = -1; ch = getchar();}
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}

const int N = 505, M = 100005, INF = 0x3f3f3f3f;

struct Edge{int to, c, nxt; };

namespace Network{
	int m, s, t, fr[N], vis[N], cur[N], d[N];
	Edge E[M];
	void init(){
		m = 0;
		memset(fr, -1, sizeof fr);
	}
	inline void addedge(int x, int y, int c){
		E[m++] = (Edge){y, c, fr[x]}; fr[x] = m - 1;
		E[m++] = (Edge){x, 0, fr[y]}; fr[y] = m - 1;
	}
	int bfs(){
		queue<int> q;
		memset(vis, 0, sizeof vis);
		memcpy(cur, fr, sizeof cur);
		d[s] = 0; vis[s] = 1;
		q.push(s);
		while (!q.empty()){
			int h = q.front(); q.pop();
			for (int i = fr[h]; i != -1; i = E[i].nxt)
				if (E[i].c && !vis[E[i].to]){
					vis[E[i].to] = 1;
					d[E[i].to] = d[h] + 1;
					q.push(E[i].to);
				}
		}
		return vis[t];
	}
	int dfs(int x, int a){
		if (x == t || a == 0) return a;
		int fl = 0, f;
		for (int &i = cur[x]; i != -1; i = E[i].nxt)
			if (d[E[i].to] == d[x] + 1 && (f = dfs(E[i].to, min(a, E[i].c))) > 0){
				E[i].c -= f; E[i ^ 1].c += f;
				fl += f; a -= f;
				if (!a) break;
			}
		return fl;
	}
	int maxflow(int _s, int _t){
		s = _s; t = _t;
		int fl = 0;
		while (bfs()) fl += dfs(s, INF);
		return fl;
	}
}

int main(){
	Network::init();
	int n = read(), m = read();
	int s = read(), t = read();
	REP(i, 1, m){
		int u = read(), v = read(), c = read();
		Network::addedge(u, v, c);
	}
	printf("%d\n", Network::maxflow(s, t));
	return 0;
}
