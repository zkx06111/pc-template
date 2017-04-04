// Splay Tree with many amortized O(log n) operations
/*
Splay(x, y): make x the child of y
Rank(x, y): returns the rank of first x, stores the position of the first x in y
Newnode(x): create a new node with the key value x
Insert(x): insert a value x
Delete(x): Delete a value x
GetKth(k): find the k-th smallest value
Prev(x): find the predecessor of x
Succ(x): find the successor of x
*/
#include <bits/stdc++.h>
#define REP(i, a, b) for (int i = a; i <= b; ++i)
using namespace std;
 
const int N = 100005;
int n;

namespace Splay{
	int fa[N], ch[N][2], rt, sz[N], val[N], cnt[N], idx, useless;
 
	#define dir(x) (x == ch[fa[x]][1])
	#define lc ch[x][0]
	 
	inline void Pushup(int x){
		sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x];
	}
	 
	inline void Rotate(int x){
		int p = fa[x], d = dir(x);
		 
		ch[p][d] = ch[x][d ^ 1];
		fa[ch[p][d]] = p;
		 
		ch[fa[p]][dir(p)] = x;
		fa[x] = fa[p];
		 
		ch[x][d ^ 1] = p;
		fa[p] = x;
		 
		Pushup(p); Pushup(x);
	}

	inline void Splay(int x, int y = 0){
		while (fa[x] != y){
		    if (fa[fa[x]] == y) Rotate(x);
		    else if (dir(x) != dir(fa[x]))
		        Rotate(x), Rotate(x);
		    else Rotate(fa[x]), Rotate(x);
		}
		Pushup(x);
		if (y == 0) rt = x;
	}

	int Rank(int x, int&pos = useless){ 
		int y, res = 0;
		for (y = rt; ; y = ch[y][val[y] < x]){
		    if (x > val[y]) res += sz[ch[y][0]] + cnt[y];
		    else if (x == val[y]){
		        res += sz[ch[y][0]];
		        break;
		    }
		    int d = val[y] < x;
		    if (!ch[y][d]) break;
		}
		pos = -y;
		if (val[y] == x) ++res, pos = y;
		return res;
	}
	 
	inline void Newnode(int x){
		++idx;
		val[idx] = x;
		cnt[idx] = sz[idx] = 1;
		ch[idx][0] = ch[idx][1] = 0;
		sz[0] = 0;
	}
	 
	void Insert(int x){
		if (rt == 0){
		    Newnode(x);
		    rt = idx;
		    return;
		}
		int y; Rank(x, y);
		if (y > 0){
		    ++cnt[y];
		    Splay(y);
		    return;
		}
		y = -y;
		int d = x > val[y];
		Newnode(x);
		ch[y][d] = idx;
		fa[idx] = y;
		Splay(idx);
	}
	 
	void Delete(int x){
		int y; Rank(x, y);
		--cnt[y]; Splay(y);
	}
	 
	int GetKth(int k){
		for (int x = rt; ;){
		    if (sz[lc] < k && sz[lc] + cnt[x] >= k){
		        Splay(x);
		        return val[x];
		    }
		    if (sz[lc] < k) k -= sz[lc] + cnt[x], x = ch[x][1];
		    else x = ch[x][0];
		}
	}
	 
	int Prev(int x){
		int y; int rk = Rank(x, y);
		if (y > 0) return GetKth(rk - 1);
		return GetKth(rk);
	}
	 
	int Succ(int x){
		int y;
		int t = Rank(x, y);
		if (y > 0) t += cnt[y];
		else ++t;
		return GetKth(t);
	}
}
 
int main(){
    scanf("%d", &n);
    REP(i, 1, n){
        int opt, x;
        scanf("%d%d", &opt, &x);
        if (opt == 1) Splay::Insert(x);
        else if (opt == 2) Splay::Delete(x);
        else if (opt == 3) printf("%d\n", Splay::Rank(x));
        else if (opt == 4) printf("%d\n", Splay::GetKth(x));
        else if (opt == 5) printf("%d\n", Splay::Prev(x));
        else if (opt == 6) printf("%d\n", Splay::Succ(x));
    }
    return 0;
}
