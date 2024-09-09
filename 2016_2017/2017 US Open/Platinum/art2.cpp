#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 1005
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

ll n, d[MAXN][MAXN], pfx[MAXN][MAXN], g[MAXN][MAXN];
ll ct[MAXN * MAXN], ctn = 0;
pair<ll, ll> xr[MAXN * MAXN], yr[MAXN * MAXN];

int main(){
    ifstream cin("art.in");
    ofstream cout("art.out");

    cin >> n;
    FOR(i, 1, n * n) ct[i] = 0, xr[i].first = yr[i].first = LLONG_MAX, yr[i].second = xr[i].second = LLONG_MIN;
    FOR(i, 0, n + 1) FOR(j, 0, n + 1) d[i][j] = 0, pfx[i][j] = 0;
    FOR(i, 1, n){
        FOR(j, 1, n){ 
            cin >> g[i][j];
            if(g[i][j]) {
                ct[g[i][j]]++;

                xr[g[i][j]].first = min(xr[g[i][j]].first, i);
                xr[g[i][j]].second = max(xr[g[i][j]].second, i);
                yr[g[i][j]].first = min(yr[g[i][j]].first, j);
                yr[g[i][j]].second = max(yr[g[i][j]].second, j);
            }
        }
    }
    FOR(i, 1, n * n) if(xr[i].first != LLONG_MAX) {
        d[xr[i].first][yr[i].first] += 1;
        d[xr[i].first][yr[i].second + 1] += -1;

        d[xr[i].second + 1][yr[i].first] += -1;
        d[xr[i].second + 1][yr[i].second + 1] += 1;
        ctn++;
    }
    if(ctn == 1) {
        cout << (n * n - 1) << endl;
        return 0;
    }

    ll cd[MAXN];
    FOR(i, 0, n) cd[i] = 0;
    FOR(i, 1, n){
        ll s = 0;
        FOR(j, 1, n){
            cd[j] += d[i][j];
            s += cd[j];

            pfx[i][j] = pfx[i - 1][j] + pfx[i][j - 1] - pfx[i - 1][j - 1] + (s >= 2); 
        } 
    }

    ll r = 0;
    FOR(i, 1, n * n) {
        if(ct[i] == 0) {
            r++;
            continue;
        }

        r += ((xr[i].second - xr[i].first + 1) * (yr[i].second - yr[i].first + 1) - ct[i]) == (pfx[xr[i].second][yr[i].second] - pfx[xr[i].first - 1][yr[i].second] - pfx[xr[i].second][yr[i].first - 1] + pfx[xr[i].first - 1][yr[i].first - 1]);
    }

    cout << r << endl;
}
