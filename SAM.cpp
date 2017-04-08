int extend(int c, int pos){
    int cur = ++idx, p;
    len[cur] = len[las] + 1;
    cnt[cur] = 1;
    RRight[cur] = pos;
    //memset(ch[cur], 0, sizeof ch[cur]);
 
    for (p = las; p && !ch[p][c]; p = fa[p])
        ch[p][c] = cur;
    if (!p) fa[cur] = 1;
    else{
        int q = ch[p][c];
        if (len[p] + 1 == len[q]) fa[cur] = q;
        else{
            int nq = ++idx;
            //memset(ch[nq], 0, sizeof ch[nq]);
 
            fa[nq] = fa[q], len[nq] = len[p] + 1;
 
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            fa[q] = fa[cur] = nq;
            for (; p && ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
        }
    }
    las = cur;
}
