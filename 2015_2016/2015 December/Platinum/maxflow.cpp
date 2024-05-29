#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define FILL_ARR(arr, a, b, v) for(int i = a; i <= b; i++) arr[i] = v;
#define MAXN 10005
#define LOGN 15

int n, q, j[MAXN][LOGN], d[MAXN];
vector<int> c[MAXN];

void setup(int v){
    if(v == 0) d[v] = 0;
    else d[v] = d[j[v][0]] + 1;

    FILL_ARR(j[v], 1, LOGN - 1, -1);
    for(int i = 1, jsz = 2; jsz <= d[v]; i++, jsz *= 2){
        j[v][i] = j[j[v][i - 1]][i - 1];
    }

    for(int i : c[v]){
        setup(i);
    }
}

int lca(int a, int b){
    if(d[a] > d[b]) swap(a, b);
    
    int dj = d[b] - d[a];
    for(int i = 0, jsz = 1; i < LOGN; i++, jsz *= 2){
        if(dj & jsz){
            b = j[b][i];
        }
    }

    if(a == b) return a;

    for(int i = LOGN - 1; i >= 0; i--){
        if(j[a][i] != j[b][i]){
            a = j[a][i];
            b = j[b][i];
        }
    }

    return j[a][0];
}

int main(){
    cin >> n;
    FOR(i, 0, n - 1){
        int m; cin >> m;
        FOR(ch, 1, m){
            int x; cin >> x;
            c[i].push_back(x), j[x][0] = i;
        }
    }

    setup(0);

    cin >> q;
    FOR(i, 1, q){
        int a, b; cin >> a >> b;
        cout << lca(a, b) << endl;
    }
}
