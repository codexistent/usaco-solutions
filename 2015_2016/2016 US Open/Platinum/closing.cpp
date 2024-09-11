#include <bits/stdc++.h>
using namespace std;
#define MAXN 200005
#define FOR(i, a, b) for(int i = a; i <= b; i++)

int n, m, p[MAXN], sz[MAXN], ord[MAXN];
bool on[MAXN];
vector<int> adj[MAXN];
vector<bool> res;

int find(int x){
    return (p[x] == x) ? x : (p[x] = find(p[x]));
}

void onion(int a, int b){
    a = find(a), b = find(b);
    if(a == b) return;

    if(sz[a] > sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b]; 
}

int main(){
    ifstream cin ("closing.in");
    ofstream cout ("closing.out");

    cin >> n >> m;
    FOR(i, 1, m){
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    FOR(i, 1, n) cin >> ord[i];

    FOR(i, 1, n) p[i] = i, sz[i] = 1;
    for(int i = n; i >= 1; i--){
        for(int j : adj[ord[i]]) if(on[j]) {
            onion(j, ord[i]);
        }
        on[ord[i]] = true;
        res.push_back(sz[find(ord[i])] == n - i + 1);
    }

    for(int i = res.size() - 1; i >= 0; i--){
        if(res[i]) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
