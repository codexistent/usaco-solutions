#include <bits/stdc++.h>
using namespace std;
#define MAXN 50005
#define LOGN 17
#define FOR(i, a, b) for(int i = a; i <= b; i++)

int n, m, p[MAXN], d[MAXN], j[MAXN][LOGN], r[MAXN];
vector<pair<int, int>> e[MAXN];
vector<int> add[MAXN], rmv[MAXN];
multiset<int> ms[MAXN];

void setup(int v){
    for(int i = 1, jsz = 2; jsz <= d[v]; i++, jsz *= 2){
        j[v][i] = j[j[v][i - 1]][i - 1];
    }

    for(auto v2 : e[v]) if(v2.first != p[v]){
        p[v2.first] = v, d[v2.first] = d[v] + 1, j[v2.first][0] = v, setup(v2.first);
    }
}

int lca(int a, int b){
    if(d[a] > d[b]) swap(a, b);
    int dj = d[b] - d[a];
    for(int i = 0, jsz = 1; i < LOGN; i++, jsz *= 2){
        if(dj & jsz) b = j[b][i];
    }

    if(a == b) return a;

    for(int i = LOGN - 1; i >= 0; i--){
        if(j[b][i] != j[a][i]){
            a = j[a][i];
            b = j[b][i];
        }
    }
    return p[a];
}

void dfs(int v){
    int sz = -1, ch = -1, pid = 0;
    for(auto v2 : e[v]) {
        if(v2.first != p[v]){
            dfs(v2.first);

            if((int)(ms[v2.first].size()) > sz){
                sz = ms[v2.first].size();
                ch = v2.first;
            }
        } else {
            pid = v2.second;
        }
    }

    if(sz != -1) {
        swap(ms[v], ms[ch]);
        for(auto v2 : e[v]) if(v2.first != p[v] && v2.first != ch) {
            for(int i : ms[v2.first]){
                ms[v].insert(i);
            }
        }
    }

    for(int i : add[v]){
        ms[v].insert(i);
    }
    for(int i : rmv[v]){
        ms[v].erase(ms[v].find(i));
    }

    r[pid] = ms[v].empty() ? -1 : *(ms[v].begin());
}

int main(){
    ifstream cin("disrupt.in");
    ofstream cout("disrupt.out");

    cin >> n >> m;
    FOR(i, 0, MAXN - 1) FOR(k, 0, LOGN - 1) j[i][k] = 0;
    FOR(i, 1, n - 1){
        int a, b; cin >> a >> b;
        e[a].push_back({b, i});
        e[b].push_back({a, i});
    }
    p[1] = 0, d[1] = 0, j[1][0] = 0, setup(1);

    FOR(i, 1, m){
        int a, b, w;
        cin >> a >> b >> w;
        add[a].push_back(w), add[b].push_back(w);
        int c = lca(a, b);
        rmv[c].push_back(w), rmv[c].push_back(w);
    }

    dfs(1);
    FOR(i, 1, n - 1){
        cout << r[i] << endl;
    }
}
