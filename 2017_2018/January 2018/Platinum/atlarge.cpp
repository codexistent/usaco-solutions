// inspo: https://codeforces.com/blog/entry/57170#comment-410179
#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define MAXN 70005
#define f first
#define s second

int n, leafd[MAXN];
int prev_fs[MAXN], idx[MAXN];
vector<int> adj[MAXN];
vector<pair<int, int>> dp[MAXN], dp2[MAXN];
int ct = 0;

void bfs() {
    memset(leafd, -1, sizeof leafd);
    queue<int> q;
    FOR(i, 0, n - 1) if(adj[i].size() == 1) q.push(i), leafd[i] = 0;
    while(q.size()){
        int v = q.front(); q.pop();
        for(int u : adj[v]) if(leafd[u] == -1 ) leafd[u] = leafd[v] + 1, q.push(u); 
    }
}

void dfs (int v = 0, int p = -1) {
    if(leafd[v] == 0 && p != -1) {
        dp[v].push_back({0, 1});
        return;
    }
    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, greater<pair<pair<int, int>, int>>> pq;
    int dp_r = 0, k = 0;
    for(int v2 : adj[v]) if(v2 != p){
        dfs(v2, v);
        pq.emplace(dp[v2][0], v2);
    }

    while(pq.size()){
        auto st = pq.top();
        pq.pop();

        int k2 = max(0, st.f.f - 1);
        if(k2 != k) dp[v].emplace_back(k, dp_r);
        k = k2;

        dp_r += st.f.s - prev_fs[st.s];
        prev_fs[st.s] = st.f.s;
        ++idx[st.s];
        if(idx[st.s] != dp[st.s].size()) pq.emplace(dp[st.s][idx[st.s]], st.s);
    }
    dp[v].emplace_back(k, dp_r);

    while(dp[v].size() && dp[v].back().f >= leafd[v]) dp[v].pop_back();
    if(dp[v].empty() || dp[v].back().s > 1) dp[v].emplace_back(leafd[v], 1);
}

void dfs2 (int v = 0, int p = -1) {
    int a = 0, b = 0, c = 0;
    int va, vb, vc, k = 0;
    if(v == 0) {
        dp2[v].emplace_back(0, 0);
        goto recurse;
    }

    while(true){
        int ka = a < dp2[p].size() ? dp2[p][a].f - 1 : INT_MAX;
        int kb = b < dp[p].size() ? dp[p][b].f - 1 : INT_MAX;
        int kc = c < dp[v].size() ? dp[v][c].f - 2 : INT_MAX;
        if(ka == INT_MAX && kb == INT_MAX && kc == INT_MAX) break;

        int k2;
        if(ka <= kb && ka <= kc) k2 = max(ka, 0);
        else if(kb <= ka && kb <= kc) k2 = max(kb, 0);
        else k2 = max(kc, 0);

        if(k != k2) dp2[v].emplace_back(k, va + vb - vc);
        k = k2;

        if(ka <= kb && ka <= kc) va = dp2[p][a++].s; 
        else if(kb <= ka && kb <= kc) vb = dp[p][b++].s;
        else vc = dp[v][c++].s;
    }
    dp2[v].emplace_back(k, va + vb - vc);
    while(dp2[v].size() && dp2[v].back().f >= max(leafd[p] - 1, 0)) dp2[v].pop_back();
    if(dp2[v].empty() || dp2[v].back().second > 1) dp2[v].emplace_back(max(leafd[p] - 1, 0), 1);

    recurse:; 
    for(int v2 : adj[v]) if(v2 != p) dfs2(v2, v); 
}

int main(){
    ifstream cin ("atlarge.in");
    ofstream cout ("atlarge.out");

    cin >> n;
    FOR(i, 1, n - 1) {
        int a, b; cin >> a >> b; a--, b--;
        adj[a].push_back(b), adj[b].push_back(a);
    }

    bfs();
    dfs();
    dfs2();

    FOR(i, 0, n - 1){
        int a = 0;
        if(adj[i].size() == 1) a = 1;
        else {
            if(dp[i].size()) a += dp[i].front().s; else a += 1;
            if(dp2[i].size()) a += dp2[i].front().s; else a += 1;
        }
        cout << (int)a << endl;
    }
}
