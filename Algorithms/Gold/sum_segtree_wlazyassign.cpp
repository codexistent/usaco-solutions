#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define ll long long

struct SumSegmentTree{
public:
    vector<ll> tree, assign;
    vector<bool> lazy;
    ll n;

    SumSegmentTree(ll n) {
        this->n = n;
        tree.assign(4 * this->n + 1, 0);
        lazy.assign(4 * this->n + 1, false);
        assign.assign(4 * this->n + 1, 0);
    }
    SumSegmentTree(const vector<ll> &a) : SumSegmentTree(a.size()){
        build(a, 1, 1, n);
    }
    
    void update(ll i, ll x){ // poll update
        if(i == 0) return;
        update_range(1, 1, n, make_tuple(i, i, x));
    }
    void update(ll i, ll j, ll x){
        if(i == j && i == 0) return; else if(i == 0) i++;
        update_range(1, 1, n, make_tuple(i, j, x));
    }
    ll query(ll i){
        if(i == 0) return 0;
        return query_range(1, 1, n, make_pair(i, i));
    }
    ll query(ll i, ll j){
        if(i == j && i == 0) return 0; else if(i == 0) i++;
        return query_range(1, 1, n, make_pair(i, j));
    }

private:
    void push(int i, int l, int r){
        if(lazy[i]){
            int m = (l + r) / 2;

            tree[i*2] = (m - l + 1) * assign[i];
            tree[i*2 + 1] = (r - m) * assign[i];
            lazy[i*2] = lazy[i*2 + 1] = true;
            assign[i*2] = assign[i*2 + 1] = assign[i];

            lazy[i] = false;
        }
    }

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
        if(l > r) return;
        
        if(get<0>(upd) == l && get<1>(upd) == r){
            tree[i] = (r - l + 1) * get<2>(upd);
            lazy[i] = true;
            assign[i] = get<2>(upd);
        } else {
            push(i, l, r);
            ll m = (l + r) / 2;
            
            if(get<0>(upd) <= min(get<1>(upd), m)) update_range(i * 2, l, m, make_tuple(get<0>(upd), min(get<1>(upd), m), get<2>(upd)));
            if(max(get<0>(upd), m + 1) <= get<1>(upd)) update_range(i * 2 + 1, m + 1, r, make_tuple(max(get<0>(upd), m + 1), get<1>(upd), get<2>(upd)));

            tree[i] = tree[i * 2] + tree[i * 2 + 1];
        }
    }
    ll query_range(ll i, ll l, ll r, pair<ll, ll> qry){
        if(l > r || qry.second < l || r < qry.first) return 0;

        if(qry.first <= l && r <= qry.second) return tree[i];

        push(i, l, r);

        ll m = (l + r) / 2;
        return query_range(i * 2, l, m, qry) + query_range(i * 2 + 1, m + 1, r, qry);
    }
};

int main() {
}
