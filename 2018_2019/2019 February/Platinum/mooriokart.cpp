#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define pll pair<ll, ll>
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define ll long long
#define MOD 1000000007

void modp(ll& a, ll b) { a = (a + b) % MOD; }
ll modm(ll a, ll b) { return (a * b == 0) ? 0 : a * b % MOD; }

ll n, m, x, y, k;
vector<ll> cpnt, dpl;
vector<bool> v;

void dfs1(int i, const vector<vector<pll>>& adj){
    if(v[i]) return;
    v[i] = true;
    cpnt.pb(i);

    for(auto e : adj[i]) dfs1(e.f, adj);
}

void dfs2(int fi, int i, ll l, const vector<vector<pll>>& adj, int p){
    for(auto e : adj[i]) if(e.f != p) {
        if(fi < e.f) dpl.pb(l + e.s);
        dfs2(fi, e.f, l + e.s, adj, i);
    }
}

ll fact(ll n){
    ll r = 1;
    FOR(i, 1, n) r = modm(r, i);
    return r;
}

ll pow2(ll n){
    ll r = 1;
    FOR(i, 1, n) r = modm(r, 2);
    return r;
}

int main(){
    ifstream in("mooriokart.in");
    ofstream out("mooriokart.out");

    in >> n >> m >> x >> y;
    vector<vector<pll>> adj(n);
    FOR(i, 1, m) {
        ll a, b, w; in >> a >> b >> w; a--, b--;
        adj[a].pb(mp(b, w)), adj[b].pb(mp(a, w));
    }
    k = n - m;

    v.assign(n, false);
    ll dp[y + 1], tl[y + 1], dp2[y + 1], tl2[y + 1];
    FOR(i, 0, y) dp[i] = tl[i] = 0; 
    dp[min(y, x * k)] = 1, tl[min(y, x * k)] = x * k;
    FOR(si, 0, n - 1) if(!v[si]) {
        dfs1(si, adj);

        for(int i : cpnt) dfs2(i, i, 0, adj, i);

        FOR(i, 0, y) dp2[i] = tl2[i] = 0;
        for(ll cl : dpl){
            FOR(l2, 0, y){
                dp2[min(y, cl + l2)] += dp[l2];
                if (dp2[min(y, cl + l2)] > MOD) dp2[min(y, cl + l2)] -= MOD; 
                modp(tl2[min(y, cl + l2)], (tl[l2] + modm(cl, dp[l2])) % MOD);
            }
        }

        FOR(i, 0, y) dp[i] = dp2[i], tl[i] = tl2[i];

        cpnt.clear(), dpl.clear();
    }

    out << modm(modm(tl[y], fact(k - 1)), pow2(k - 1)) << endl;
}
