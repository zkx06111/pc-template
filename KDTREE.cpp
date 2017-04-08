#define me AcrossTheSky&HalfSummer11  
#include <cstdio>  
#include <cmath>  
#include <ctime>  
#include <string>  
#include <cstring>  
#include <cstdlib> 
#include <iostream>  
#include <algorithm>  
   
#include <set> 
#include <map> 
#include <stack>  
#include <queue>  
#include <vector> 
#include <bitset> 
  
#define pb push_back 
#define lb lower_bound 
#define ub upper_bound 
#define sqr(x) (x)*(x) 
#define lowbit(x) (x)&(-x)  
#define ls(a,b) (((a)+(b)) << 1)  
#define rs(a,b) (((a)+(b)) >> 1)
#define lc ch[0]
#define rc ch[1]  
#define fin(a) freopen(a,"r",stdin); 
#define fout(a) freopen(a,"w",stdout); 
#define Abs(x) ((x) > 0 ? (x) : (-(x)))  
#define FOR(i,a,b) for((i)=(a);(i)<=(b);(i)++)  
#define FORP(i,a,b) for(int i=(a);i<=(b);i++)  
#define FORM(i,a,b) for(int i=(a);i>=(b);i--)  
  
#define maxn 1100005 
#define maxm 600005 
#define MOD 1000000007 
#define INF 1070000000  
using namespace std;  
typedef long long ll;  
typedef unsigned long long ull;  
   
template<class T> inline 
void read(T& num){  
    num = 0; bool f = 1;char ch = getchar();  
    while(ch < '0' || ch > '9') { if(ch == '-') f = 0;ch = getchar();}  
    while(ch >= '0' && ch <= '9') {num = num * 10 + ch - '0';ch = getchar();}  
    num = f ? num: -num;  
} 
template<class T> inline
void write(T x,char ch){ 
    int s[100]; 
    if (x==0) {putchar('0'); putchar(ch); return;} 
    if (x<0) {putchar('-'); x=-x;} int num=0; 
    while (x){ s[num++]=(x%10); x=x/10;} 
    FORM(i,num-1,0) putchar(s[i]+'0'); putchar(ch); 
} 
/*==================split line==================*/
const double pi = acos(-1); 
const double eps = 1e-8; 
int flag;
inline int Max(int x, int y){return x < y ? y : x;}
inline int Min(int x, int y){return x < y ? x : y;}
struct Node{
    int x, y;
    inline void in(){ read(x); read(y);}
    inline bool operator<(const Node& a)const{ 
        if(!flag) return x<a.x;
        return y<a.y;
    }
}p[maxn];
inline int dist(Node a,Node b){return Abs(a.x - b.x) + Abs(a.y - b.y);}
struct KD{ 
    int minv[2], maxv[2];
    inline int dis(Node p){
       int res = 0;
       if (p.x < minv[0] || p.x > maxv[0]) res += p.x < minv[0] ? minv[0] - p.x : p.x - maxv[0];
       if (p.y < minv[1] || p.y > maxv[1]) res += p.y < minv[1] ? minv[1] - p.y : p.y - maxv[1];
       return res;
    }
    inline KD operator+(const KD &a){
        KD c;  
        c.minv[0] = Min(minv[0], a.minv[0]);
        c.minv[1] = Min(minv[1], a.minv[1]);
        c.maxv[0] = Max(maxv[0], a.maxv[0]);
        c.maxv[1] = Max(maxv[1], a.maxv[1]);
        return c;
    }
};
       
struct KDtree{
    Node p;
    KD c;
}tree[maxn];
int n, m, ch[maxn][2], cnt, ans = INF, root = 1;
  
inline int build(int l,int r,int k){
    int x = ++cnt;
    flag = k;
    int mid = rs(l,r);
    nth_element(p + l, p + mid, p + 1 + r);
    tree[x].p = p[mid];
    tree[x].c.minv[0] = tree[x].c.maxv[0] = tree[x].p.x;
    tree[x].c.minv[1] = tree[x].c.maxv[1] = tree[x].p.y;
    if (l <= mid - 1){
        ch[x][0] = build(l, mid - 1, k ^ 1);
        tree[x].c = tree[x].c + tree[ch[x][0]].c;
    }
    if (mid + 1 <= r){
        ch[x][1] = build(mid + 1, r, k ^ 1);
        tree[x].c = tree[x].c + tree[ch[x][1]].c;
    }
    return x;
}
inline void insert(int &o, Node a, int k){
    flag = k;
    if (!o) {
        o = ++cnt; tree[o].p = a;
        tree[o].c.minv[0] = tree[o].c.maxv[0] = tree[o].p.x;
        tree[o].c.minv[1] = tree[o].c.maxv[1] = tree[o].p.y;
        return;
    }
    if (tree[o].p.x == a.x && tree[o].p.y == a.y) return;
    int d = tree[o].p < a;
    insert(ch[o][d], a, k ^ 1);
    tree[o].c = tree[o].c + tree[ch[o][d]].c;
}
inline void ask(int o, Node a){
    if (!o) return;
    ans = Min(ans, dist(tree[o].p, a));
    int d = tree[ch[o][0]].c.dis(a) > tree[ch[o][1]].c.dis(a);
    ask(ch[o][d], a);
    if (tree[ch[o][d^1]].c.dis(a) < ans) ask(ch[o][d ^ 1], a);
}
int main(){
    read(n); int m; read(m);
    FORP(i, 1, n)
        p[i].in();
 
    build(1, n, 0);
    FORP(i, 1, m){
        int op; read(op); Node a; a.in();
        if (op == 1) insert(root, a, 0);
        else {
                ans = INF;
                ask(1,a);
                write(ans,'\n');
            }
    }
}