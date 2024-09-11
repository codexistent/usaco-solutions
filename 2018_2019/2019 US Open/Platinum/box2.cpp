#include "grader.h"
#define MAXN 100005
#define LOGN 17
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define FILL_ARR(arr, a, b, v) FOR(i, a, b) arr[i] = v;
 
int j[MAXN][LOGN], sz[MAXN], p[MAXN], d[MAXN];
pair<int, int> f[MAXN];
vector<int> e[MAXN], c[MAXN];
 
// helper functions
int setup(int i){
    for(int c = 1, jsz = 2; jsz <= d[i]; c++, jsz *= 2){
        j[i][c] = j[j[i][c - 1]][c - 1];
    }

    sz[i] = 1;
    for(int i2 : e[i]) if(i2 != p[i]) {
        c[i].push_back(i2);
        j[i2][0] = i, p[i2] = i, d[i2] = d[i] + 1;
        setup(i2);
 
        sz[i] += sz[i2];
    }
}
 
void setupFarms(int id, pair<int, int> tl, pair<int, int> br){
    f[id] = tl;
 
    int x = br.first, y = tl.second;
    for(int id2 : c[id]){
        x += sz[id2];
        setupFarms(id2, {x, y}, {x - sz[id2], y - sz[id2]});
        y -= sz[id2];
    }
}
 
pair<int, pair<int, int>> lca(int a, int b){
    if(d[a] > d[b]) swap(a, b);
    int dj = d[b] - d[a];
    for(int i = 0, jsz = 1; i < LOGN; i++, jsz *= 2){
        if(dj & jsz) b = j[b][i];
    }
 
    if(a == b) return {1, {a, a}};
 
    for(int i = LOGN - 1; i >= 0; i--){
        if(j[a][i] != j[b][i]){
            a = j[a][i];
            b = j[b][i];
        }
    }
    return {2, {a, b}};
}
 
// main functions
void addRoad(int a, int b){
    a++, b++;
    e[a].push_back(b);
    e[b].push_back(a);
}
 
void buildFarms(){
    j[1][0] = 0, p[1] = 0, d[1] = 0, setup(1);
 
    setupFarms(1, {sz[1], sz[1]}, {0, 0});
    FOR(i, 0, getN() - 1) setFarmLocation(i, f[i + 1].first, f[i + 1].second);
}
 
void notifyFJ(int a, int b){
    a++, b++;
 
 
    pair<int, pair<int, int>> c = lca(a, b);
    if(c.first == 1){
        if(c.second.first == a) swap(a, b);
        addBox(f[a].first, f[a].second, f[c.second.first].first, f[c.second.first].second);
    }else{
        int p2 = a, dj = d[a] - d[p[c.second.first]] - 1;
        for(int i = 0, jsz = 1; i < LOGN; i++, jsz *= 2){
            if(dj & jsz) p2 = j[p2][i];
        }
 
        addBox(f[a].first, f[a].second, f[p2].first, f[p2].second);
        addBox(f[b].first, f[b].second, f[p[c.second.first]].first, f[p[c.second.first]].second);
    }
}
