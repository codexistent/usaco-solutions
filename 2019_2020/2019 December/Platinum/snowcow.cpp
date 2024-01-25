#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define ll long long

struct SumSegmentTree{
public:
    vector<ll> tree, lazy;
    ll n;

    SumSegmentTree(ll n) {
        this->n = n;
        tree.assign(4 * this->n + 1, 0);
        lazy.assign(4 * this->n + 1, 0);
    }
    SumSegmentTree(const vector<ll> &a) : SumSegmentTree(a.size()){
        build(a, 1, 1, n);
    }
    
    void update(ll i, ll x){ // point update
        update_range(1, 1, n, make_tuple(i, i, x));
    }
    void update(ll i, ll j, ll x){
        update_range(1, 1, n, make_tuple(i, j, x));
    }
    ll query(ll i){
        return query_range(1, 1, n, make_pair(i, i));
    }
    ll query(ll i, ll j){
        return query_range(1, 1, n, make_pair(i, j));
    }

private:
    void build(const vector<ll> &a, ll i, ll l, ll r){
        if(l > r) return;
        
        if(l == r) {
            tree[i] = a[l - 1];
            return;
        }
        
        ll m = (l + r) / 2;
        build(a, 2*i, l, m);
        build(a, 2*i + 1, m + 1, r);

        tree[i] = tree[2*i] + tree[2*i + 1];
    }
    void update_range(ll i, ll l, ll r, tuple<ll, ll, ll> upd){
        if(lazy[i] != 0){
            tree[i] += (r - l + 1) * lazy[i];
            if(l != r){
                lazy[i * 2] += lazy[i];
                lazy[i * 2 + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
        if(l > r || get<1>(upd) < l || r < get<0>(upd)) return;

        if(get<0>(upd) <= l && r <= get<1>(upd)){
            tree[i] += (r - l + 1) * get<2>(upd);
            if(l != r){
                lazy[i * 2] += get<2>(upd);
                lazy[i * 2 + 1] += get<2>(upd);
            }
            return;
        }

        ll m = (l + r) / 2;
        update_range(i * 2, l, m, upd);
        update_range(i * 2 + 1, m + 1, r, upd);

        tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }
    ll query_range(ll i, ll l, ll r, pair<ll, ll> qry){
        if(l > r || qry.second < l || r < qry.first) return 0;

        if(lazy[i] != 0){
            tree[i] += (r - l + 1) * lazy[i];
            if(l != r) {
                lazy[i * 2] += lazy[i];
                lazy[i * 2 + 1] += lazy[i];
            }
            lazy[i] = 0;
        }

        if(qry.first <= l && r <= qry.second) return tree[i];

        ll m = (l + r) / 2;
        return query_range(i * 2, l, m, qry) + query_range(i * 2 + 1, m + 1, r, qry);
    }
};

vector<pair<ll, ll>> rng;

ll eulertour(const vector<vector<ll>>& adj, ll t, ll v, ll p){
    rng[v].f = t;
    for(ll v2 : adj[v]) if(v2 != p) t = eulertour(adj, t + 1, v2, v);
    return rng[v].s = t;
}

int main(){
    ifstream cin ("snowcow.in");
    ofstream cout ("snowcow.out");

    ll n, q;
    cin >> n >> q;
    vector<vector<ll>> adj(n + 1);
    FOR(i, 1, n - 1){
        ll a, b; cin >> a >> b;
        adj[a].pb(b), adj[b].pb(a);
    }
    rng.resize(n + 1), eulertour(adj, 1, 1, -1);

    map<ll, set<pair<pair<ll, ll>, ll>>> cr;
    SumSegmentTree st(n + 2);
    FOR(qi, 1, q){
        ll t; cin >> t;
        if(t == 1) {
            ll r, c; cin >> r >> c;
            auto it = cr[c].upper_bound(mp(rng[r], r));
            if(it != cr[c].begin() && (*prev(it)).f.s >= rng[r].s) continue;
            while(it != cr[c].end() && (*it).f.s <= rng[r].s){
                st.update((*it).f.f, (*it).f.s, -1);
                cr[c].erase(it++);
            }
            st.update(rng[r].f, rng[r].s, 1);
            cr[c].insert(mp(rng[r], r));
        } else {
            ll r; cin >> r;
            cout << st.query(rng[r].f, rng[r].s) << endl;
        }
    }
}
