#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define ll long long

struct LCASegmentTree {
public:
    vector<pair<int/*depth*/, int/*node*/>> tree, tour;
    vector<int> tour_seen;
    int n2, n;
    LCASegmentTree(const vector<vector<int>> &adj /* 0 base indexed adj list */ , int root){
        n2 = adj.size();
        tour.reserve(2 * n2 + 1);
        tour_seen.resize(n2);
        flatten_dfs(adj, root, root, 1);

        n = tour.size();
        tree.resize(4 * n + 1, make_pair(INT_MAX, INT_MAX));
        build(1, 1, n);
    }
    
    int LCA(ll i, ll j){
        return query_range(1, 1, n, make_pair(min(tour_seen[i], tour_seen[j]), max(tour_seen[i], tour_seen[j]))).second;
    }

private:
    void flatten_dfs(const vector<vector<int>> &adj, int p, int i, int d){
        tour.push_back(make_pair(d, i));
        tour_seen[i] = tour.size();

        for(int e : adj[i]) if(e != p) {
            flatten_dfs(adj, i, e, d + 1);
            tour.push_back(make_pair(d, i));
        }
    }
    void build(ll i, ll l, ll r){
        if(l > r) return;
        if(l == r) {
            tree[i] = tour[l - 1];
            return;
        }
        
        ll m = (l + r) / 2;
        build(2*i, l, m);
        build(2*i + 1, m + 1, r);

        tree[i] = min(tree[2*i], tree[2*i + 1]);
    }
    pair<int, int> query_range(ll i, ll l, ll r, pair<ll, ll> qry){
        if(l > r || qry.second < l || r < qry.first) {
            return make_pair(INT_MAX, INT_MAX);
        }

        if(qry.first <= l && r <= qry.second) return tree[i];

        ll m = (l + r) / 2;
        return min(query_range(i * 2, l, m, qry), query_range(i * 2 + 1, m + 1, r, qry));
    }
};

int main(){
    int N;
    cin >> N;
    vector<vector<int>> E(N);
    FOR(i, 1, N - 1){
        int a, b;
        cin >> a >> b;
        a--, b--;
        E[a].push_back(b), E[b].push_back(a);
    }

    LCASegmentTree T(E, 0);
}
