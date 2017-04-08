int s[maxn];
int t[maxn],t2[maxn],c[100],rank[maxn],sa[maxn];
int height[maxn];
int n;
void build_sa(int m){
    int *x=t,*y=t2;
    //memset(c,0,sizeof(c));
    FORP(i,0,m) c[i]=0;
    FORP(i,0,n-1) c[x[i]=s[i]]++;
    FORP(i,1,m-1) c[i]+=c[i-1];
    FORM(i,n-1,0) sa[--c[x[i]]]=i;
    for (int k=1;k<=n;k <<= 1){
        int p=0;
        FORP(i,n-k,n-1) y[p++]=i;
        FORP(i,0,n-1) if (sa[i]>=k) y[p++]=sa[i]-k;
         
        FORP(i,0,m) c[i]=0;
        FORP(i,0,n-1) c[x[y[i]]]++;
        FORP(i,1,m-1) c[i]+=c[i-1];
        FORM(i,n-1,0) sa[--c[x[y[i]]]]=y[i];
         
        swap(x,y);
        p=1; x[sa[0]]=0;
        FORP(i,1,n-1)
            if (y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k])
                x[sa[i]]=p-1;
            else x[sa[i]]=p++;
        if (p>=n) break;
        m=p;
    }
}
void getheight(){
    int k=0;
    FORP(i,0,n-1) rank[sa[i]]=i;
    FORP(i,0,n-1){
        if (k) k--;
        int j=sa[rank[i]-1];
        while (s[i+k] == s[j+k]) k++;
        height[rank[i]]=k;
    }
}