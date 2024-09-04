#include <bits/stdc++.h>
using namespace std;
#define MAXN 505
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define f first
#define s second

int n, m, t, g[MAXN * MAXN], sz[MAXN * MAXN], p[MAXN * MAXN];
vector<int> u[MAXN * MAXN];
bool st[MAXN * MAXN];
long long res = 0;

int find(int x){
    return (p[x] == x) ? x : (p[x] = find(p[x]));
}

void onion(int a, int b, int w){
    a = find(a);
    b = find(b);
    if(a == b) return;

    if(sz[a] < sz[b]) swap(a, b);//, swap(u[a], u[b]), swap(sz[a], sz[b]);
    p[b] = a;

    if(sz[a] + sz[b] >= t){
        if(sz[a] < t){
            for(int i : u[a]){
                res = res + (long long)st[i] * w;
            }
        }
        if(sz[b] < t){
            for(int i : u[b]){
                res = res + (long long)st[i] * w;
            }
        }
    }

    sz[a] += sz[b];
    while(u[b].size()){
        u[a].push_back(u[b].back());
        u[b].pop_back();
    }
}

int main(){
    ifstream cin("skilevel.in");
    ofstream cout("skilevel.out");

    cin >> n >> m >> t;
    FOR(i, 1, n) FOR(j, 1, m) cin >> g[(i-1)*m+j];

    priority_queue<pair<int, pair<int, int>>> eq;
    FOR(i, 1, n) {
        FOR(j, 1, m) {
            cin >> st[(i-1)*m+j];
            if(i != n){
                eq.push({-abs(g[(i-1)*m+j] - g[(i)*m+j]), {(i-1)*m+j, (i)*m+j}});
            }
            if(j != m){
                eq.push({-abs(g[(i-1)*m+j] - g[(i-1)*m+j+1]), {(i-1)*m+j, {(i-1)*m+j+1}}});
            }
            sz[(i - 1) * m + j] = 1;
            p[(i - 1) * m + j] = (i - 1) * m + j;
            u[(i - 1) * m + j].push_back((i - 1) * m + j);
        }
    }

    while(eq.size()){
        auto nxt = eq.top();
        onion(nxt.second.first, nxt.second.second, -nxt.first);
        eq.pop();
    }
    cout << res << endl;
}
