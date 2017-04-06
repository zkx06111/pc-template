//模数大的时候还是要暴力判，快速幂的时候可能会炸
ll fpow(ll a, ll k, ll mod){
    ll s = 1;
    for (; k; a = (a * a) % mod, k >>= 1)
        if (k & 1) s *= a,s %= mod;
    return s;
}
bool check(ll x,ll a){
    if (!x % a) return false;
    ll r = 0, s = x - 1;
    while (!(s & 1)) s >>= 1,r ++;
    ll k = fpow(a, s, x);
    if (k == 1) return true;
    for (ll j = 0; j < r; j ++, k = k * k % x)
        if (k == x - 1) return true;
    return false;
}
bool miller_rabin(ll x){
    if (x > 1e9) return brute(x);
    FORP(i, 0, 5) if (x == c[i]) return true;
    FORP(i, 0, 5) if (!check(x,c[i])) return false;
    return true;
}