#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
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
    
    void update(ll i, ll x){ // poll update
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

int main() {
    
}
