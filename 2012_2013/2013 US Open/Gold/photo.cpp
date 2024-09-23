#include <bits/stdc++.h>
using namespace std;
#define MAXN 200005
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define f first
#define s second

int n, m, dp[MAXN], st[MAXN * 4], sfx[MAXN], adt = 0;
pair<int, int> rng_e[MAXN], rng_s[MAXN];

void update(int i, int l, int r, pair<int, int> upd){
    if(r < upd.f || upd.f < l) return;

    if(l == r) {
        st[i] = upd.second;
        return;
    }
    update(i * 2, l, (l + r) / 2, upd);
    update(i * 2 + 1, (l + r) / 2 + 1, r, upd);
    st[i] = max(st[i * 2], st[i * 2 + 1]);
}

int query(int i, int l, int r, pair<int, int> qry){
    if(qry.s < l || r < qry.f) return INT_MIN;

    if(qry.f <= l && r <= qry.s) return st[i];
    return max(query(i * 2, l, (l + r) / 2, qry), query(i * 2 + 1, (l + r) / 2 + 1, r, qry));
}

int main(){
    ifstream cin("photo.in");
    ofstream cout("photo.out");

    cin >> n >> m;
    FOR(i, 1, m){
        cin >> rng_e[i].s >> rng_e[i].f;
        rng_s[i] = {rng_e[i].s, rng_e[i].f};
    }
    sort(rng_e + 1, rng_e + 1 + m), sort(rng_s + 1, rng_s + 1 + m);
    FOR(i, 1, m) swap(rng_e[i].f, rng_e[i].s);

    FOR(i, 0, MAXN * 4 - 1) st[i] = 0;
    FOR(i, 1, m) update(1, 1, m, {i, rng_e[i].f});

    sfx[m + 1] = INT_MAX;
    for(int i = m; i >= 1; i--) sfx[i] = min(sfx[i + 1], rng_e[i].f);

    FOR(i, 0, m) dp[i] = -1;
    dp[0] = 0;
    FOR(i, 1, n){
        int mni, mxi;

        // find mni
        int lo = 1, hi = m;
        while(lo < hi){
            int md = (lo + hi) / 2;
            if(md == m || i <= rng_e[md].s){
                hi = md;
            }else{
                lo = md + 1;
            }
        }
        mni = lo;
        if(rng_e[mni].s < i || i < sfx[mni]) {
            adt++;
            continue;
        }

        // find mxi
        lo = mni, hi = m;
        while(lo < hi){
            int md = (lo + hi + 1) / 2;
            if(sfx[md] <= i){
                lo = md;
            }else{
                hi = md - 1;
            }
        }
        mxi = lo;

        if(query(1, 1, m, {mni, mxi}) <= i && dp[mni - 1] != -1){
            dp[mxi] = max(dp[mxi], dp[mni - 1] + 1);
        }
    }

    cout << ((dp[m] == -1) ? -1 : (dp[m] + adt)) << endl;
}
