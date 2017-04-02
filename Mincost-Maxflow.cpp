// Mincost maxflow
// XIOJ 3
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

const int N = 505, M = 250005, INF = 0x3f3f3f3f;
struct Edge{int to, w, c, nxt;};

namespace Network{
	int m, s, t, fr[N], dist[N], inq[N], pre[N];
	Edge E[M];
	inline void init(){
		memset(fr, -1, sizeof fr);
		m = 0;
	}
	inline void addedge(int x, int y, int w, int c){
		E[m++] = (Edge){y, w, c, fr[x]}; fr[x] = m - 1;
		E[m++] = (Edge){x, -w, 0, fr[y]}; fr[y] = m - 1;
	}
	inline int spfa(){
		queue<int> q;
		memset(dist, 0x3f, sizeof dist);
		dist[s] = 0;
		q.push(s);
		while (!q.empty()){
			int h = q.front(); q.pop(); inq[h] = 0;
			for (int i = fr[h]; i != -1; i = E[i].nxt)
				if (E[i].c && dist[h] + E[i].w < dist[E[i].to]){
					dist[E[i].to] = dist[h] + E[i].w;
					pre[E[i].to] = i;
					if (!inq[E[i].to]){
						q.push(E[i].to);
						inq[E[i].to] = 1;
					}
				}
		}
		if (dist[t] == INF) return 0;
		int f = INF;
		for (int i = t; i != s; i = E[pre[i] ^ 1].to)
			f = min(f, E[pre[i]].c);
		for (int i = t; i != s; i = E[pre[i] ^ 1].to){
			E[pre[i] ^ 1].c += f;
			E[pre[i]].c -= f;
		}
		return dist[t] * f;
	}
	inline int mcmf(int _s, int _t){
		s = _s, t = _t;
		int res = 0, c;
		while ((c = spfa()))
			res += c;
		return res;
	}
}

int main(){
	int n = read(), m = read(), s = read(), t = read();
	Network::init();
	REP(i, 1, m){
		int u = read(), v = read(), c = read(), w = read();
		Network::addedge(u, v, w, c);
	}
	printf("%d\n", Network::mcmf(s, t));
	return 0;
}
