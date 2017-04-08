int n,m;
int slack[maxn],lx[maxn],ly[maxn],w[maxn][maxn],link[maxn];
bool S[maxn],T[maxn];
int Ans;
bool match(int i){
    S[i]=true;
    FORP(j,1,m)
    if (!T[j]){
        int tmp=lx[i]+ly[j]-w[i][j];
        if (tmp==0){
            T[j]=true;
            if (!link[j] || match(link[j])){
                link[j]=i;
                return true;
            }
        }
        else slack[j]=min(slack[j],tmp);
    }
    return false;
}
void updata(){
    int a=INF;
    FORP(i,1,m) if (!T[i]) a=min(a,slack[i]);
    FORP(i,1,n) if (S[i]) lx[i]-=a;
    FORP(i,1,m)
        if (T[i]) ly[i]+=a;
            else slack[i]-=a;
}
void KM(){
    memset(lx,0,sizeof(lx));
    memset(link,0,sizeof(link));
    memset(ly,0,sizeof(ly));
    FORP(i,1,n)
        FORP(j,1,m) lx[i]=max(lx[i],w[i][j]);
    FORP(i,1,n){
        memset(slack,0x7f,sizeof(slack));
        while (true){
            memset(S,false,sizeof(S));
            memset(T,false,sizeof(T));
            if (match(i)) break;
            else updata();
        }
    }
    int ans=0;
    FORP(i,1,m) if (link[i]) ans+=w[link[i]][i];
}