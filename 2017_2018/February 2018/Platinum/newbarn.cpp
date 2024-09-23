#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 100005
#define LOGN 20
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

ll q, n = 0, d[MAXN], jmp[MAXN][LOGN], rt[MAXN];
pair<pair<ll, ll>, ll> dm[MAXN];

ll lca(ll a, ll b){
    if(d[a] > d[b]) swap(a, b);

    ll dj = d[b] - d[a];
    FOR(ji, 0, LOGN - 1) if(dj & (1 << ji)) b = jmp[b][ji];

    if(a == b) return a;

    for(ll ji = LOGN - 1; ji >= 0; ji--){
        if(jmp[a][ji] != jmp[b][ji]){
            a = jmp[a][ji], b = jmp[b][ji];
        }
    }

    return jmp[a][0];
}

int main(){
    ifstream cin("newbarn.in");
    ofstream cout("newbarn.out");

    cin >> q;
    d[0] = -1;
    FOR(qi, 1, q){
        char c; cin >> c;
        if(c == 'B'){
            ll p; cin >> p;
            n++, p = max(p, 0ll);
            if(p == 0) {
                rt[n] = n; 
                dm[n] = {{n, n}, 0};
            } else rt[n] = rt[p];

            FOR(ji, 0, LOGN - 1) jmp[n][ji] = -1;
            jmp[n][0] = p, d[n] = d[p] + 1;
            for(ll ji = 1, jsz = 2; jsz <= d[n]; ji++, jsz *= 2){
                jmp[n][ji] = jmp[jmp[n][ji - 1]][ji - 1];
            }
        }
        
        ll i = n;
        if(c == 'Q'){
            cin >> i;
        }

        ll d1 = dm[rt[i]].first.first, d2 = dm[rt[i]].first.second;

        ll d1i = d[i] + d[d1] - 2 * d[lca(i, d1)];
        ll d2i = d[i] + d[d2] - 2 * d[lca(i, d2)];

        if(c == 'Q') cout << max(d1i, d2i) << endl;

        if(d1i > d2i) {
            if(d1i > dm[rt[i]].second){
                dm[rt[i]].second = d1i;
                dm[rt[i]].first.second = i;
            }
        }else{
            if(d2i > dm[rt[i]].second){
                dm[rt[i]].second = d2i;
                dm[rt[i]].first.first = i;
            }
        }
    }
}
