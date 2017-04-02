// Link Cut Tree
// BZOJ 2049
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
 
const int N = 10005;
 
int n, m;
char op[10];
 
namespace LCT{
    int ch[N][2], fa[N], rev[N];
 
    inline int isrt(int x){return ch[fa[x]][0] != x && ch[fa[x]][1] != x;}
 
    #define lc ch[x][0]
    #define rc ch[x][1]
    #define dir(x) (ch[fa[x]][1] == x)
 
    inline void rever(int x){
        rev[x] ^= 1;
        swap(lc, rc);
    }
 
    inline void pd(int x){
        if (rev[x]){
            rever(lc);
            rever(rc);
            rev[x] = 0;
        }
    }
 
    void gop(int x){
        if (!isrt(x)) gop(fa[x]);
        pd(x);
    }
 
    inline void rot(int x){
        int d = dir(x), p = fa[x];
        fa[x] = fa[p];
        if (!isrt(p)) ch[fa[p]][dir(p)] = x;
        ch[p][d] = ch[x][d ^ 1];
        fa[ch[x][d ^ 1]] = p;
        ch[x][d ^ 1] = p;
        fa[p] = x;
    }
 
    void splay(int x){
        gop(x);
        while (!isrt(x)){
            if (isrt(fa[x])) rot(x);
            else if (dir(x) == dir(fa[x])) rot(fa[x]), rot(x);
            else rot(x), rot(x);
        }
    }
 
    void access(int x){
        for (int y = 0; x; x = fa[y = x])
            splay(x), rc = y;
    }
 
    void mkrt(int x){
        access(x);
        splay(x);
        rever(x);
    }
 
    void link(int x, int y){
        mkrt(x);
        fa[x] = y;
    }
 
    void cut(int x, int y){
        mkrt(x);
        access(y);
        splay(y);
        ch[y][0] = fa[x] = 0;
    }
 
    int findrt(int x){return fa[x] ? findrt(fa[x]) : x;}
}
 
int main(){
    n = read(), m = read();
    REP(i, 1, m){
        scanf("%s", op);
        int u = read(), v = read();
        if (op[0] == 'C') LCT::link(u, v);
        else if (op[0] == 'D') LCT::cut(u, v);
        else{
            if (LCT::findrt(u) == LCT::findrt(v)) printf("Yes\n");
            else printf("No\n");
        }
    }
    return 0;
}
