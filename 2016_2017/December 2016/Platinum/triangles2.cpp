#include <bits/stdc++.h>
using namespace std;
#define MAXN 305
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define x first
#define y second

int n, pfx[MAXN][MAXN], r[MAXN];
pair<int, int> p[MAXN];

bool under(pair<int, int> pt, pair<pair<int, int>, pair<int, int> > ln){
    if(ln.first.x == ln.second.x) return pt.y < ln.first.y;
    return (double)(pt.y - ln.first.y) * (ln.second.x - ln.first.x) <= (double)(ln.second.y - ln.first.y) * (pt.x - ln.first.x);
}

int main(){
    ifstream cin("triangles.in");
    ofstream cout("triangles.out");
    
    cin >> n;
    FOR(i, 1, n) cin >> p[i].x >> p[i].y;
    sort(p + 1, p + 1 + n);

    FOR(i, 1, n) FOR(j, i, n){
        FOR(k, 1, n) 
            if(k != i && k != j) if(p[i].x <= p[k].x && p[k].x <= p[j].x) pfx[i][j] += under(p[k], {p[i], p[j]});
    }
    
    fill(r, r + MAXN - 1, 0);
    FOR(a, 1, n) FOR(b, a + 1, n) FOR(c, b + 1, n) {
        if(under(p[b], {p[a], p[c]})) r[pfx[a][c] - (pfx[a][b] + pfx[b][c] - pfx[b][b]) - 1]++;
        else r[(pfx[a][b] + pfx[b][c] - pfx[b][b]) - pfx[a][c]]++;
    }

    FOR(i, 0, n-3) cout << r[i] << endl;
}
