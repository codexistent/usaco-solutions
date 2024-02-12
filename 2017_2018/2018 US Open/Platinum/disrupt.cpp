#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define maxn 50005

int n, m;
vector<pair<int, int>> adj[maxn], w[maxn];
vector<int> r(50005, -1);

set<pair<int, int>> dfs(int v = 0, int p = -1){
    set<pair<int, int>> ws;
    for(auto v2 : adj[v]) if(v2.first != p){ 
        set<pair<int, int>> chw = move(dfs(v2.first, v));
        if(chw.size()) r[v2.second] = (*chw.begin()).first;

        if(chw.size() > ws.size()) swap(ws, chw);
        for(auto i : chw) if(ws.count(i)) ws.erase(i); else ws.insert(i);
    }
    
    for(auto i : w[v]) if(ws.count(i)) ws.erase(i); else ws.insert(i);

    return ws;
}

int main(){
    ifstream cin ("disrupt.in");
    ofstream cout ("disrupt.out");

    cin >> n >> m;
    FOR(i, 0, n - 2){
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(make_pair(b, i)), adj[b].push_back(make_pair(a, i));
    }

    FOR(i, 1, m){
        int a, b, c; 
        cin >> a >> b >> c; a--, b--;
        w[a].push_back(make_pair(c, i)), w[b].push_back(make_pair(c, i));
    }

    dfs();
    FOR(i, 0, n - 2) cout << r[i] << endl;
}
