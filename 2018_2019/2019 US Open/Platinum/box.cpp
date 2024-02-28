#include <bits/stdc++.h>
using namespace std;
#include "grader.h"
#define ll long long
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define maxn 100005
#define logn 20

int n = 1, d[maxn], jp[maxn][logn], sz[maxn];
vector<int> adj[maxn];
pair<int, int> f[maxn];

void computeJp(int v = 0, int p = -1, int dn = 0){
    d[v] = dn;
    int j = 1;
    while(jp[v][j - 1] != -1 && j < logn) {
        jp[v][j] = jp[jp[v][j - 1]][j - 1], j++;
    }

    sz[v] = 0;
    for(int v2 : adj[v]) if(v2 != p) jp[v2][0] = v, computeJp(v2, v, dn + 1), sz[v] += 1 + sz[v2];
}
int jump(int a, int k){
    int origa = (a == 0);
    FOR(i, 0, logn - 1) if((int)(k & (1 << i))) {
        a = jp[a][i]; 
    }
    return a;
}
int lca(int a, int b){
    if(d[a] < d[b]) swap(a, b);
    a = jump(a, d[a] - d[b]);

    for(int i = logn - 1; i >= 0; i--){
        if(jp[a][i] != jp[b][i] && jp[a][i] != -1) a = jp[a][i], b = jp[b][i];
    }

    if(a == b) return a;
    return jp[a][0];
}

void computeF(int v = 0, int p = -1){
    int cx = f[v].first - sz[v] - 1, cy = f[v].second;
    for(int v2 : adj[v]) if(v2 != p) {
        f[v2] = {cx + sz[v2] + 1, cy - 1};
        cx += sz[v2] + 1, cy -= sz[v2] + 1;
        computeF(v2, v);
    }
}

void addRoad(int a, int b){
	n++;
    adj[a].push_back(b), adj[b].push_back(a);
}

void buildFarms(){
	memset(jp, -1, sizeof(jp));
    computeJp();

    f[0] = {n, n};
    computeF();

    FOR(i, 0, n - 1) setFarmLocation(i, f[i].first, f[i].second);
}

void notifyFJ(int a, int b){
	int k = lca(a, b);
    if(b == k) swap(a, b);
    if(a == k){
        addBox(f[b].first, f[b].second, f[a].first, f[a].second);
    }else{
        addBox(f[b].first, f[b].second, f[k].first, f[k].second);
        int k2 = jump(a, d[a] - d[k] - 1);
        addBox(f[a].first, f[a].second, f[k2].first, f[k2].second);
    }
}
