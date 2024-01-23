#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define ll long long

void mxset(ll& a, ll b, ll c) { a = max(a, max(b, c)); }

int main(){
    ifstream cin ("pieaters.in");
    ofstream cout ("pieaters.out");

    ll n, m;
    cin >> n >> m;
    ll mxw[n + 2][n + 2][n + 2], dp[n + 2][n + 2];
    FOR(i, 0, n + 1) FOR(j, 0, n + 1) {
        dp[i][j] = 0;
        FOR(inc, 0, n + 1) mxw[i][j][inc] = 0;
    }
    FOR(i, 1, m) {
        ll w, l, r; cin >> w >> l >> r;
        FOR(inc, l, r) mxw[l][r][inc] = max(mxw[l][r][inc], w);
    }

    FOR(l, 1, n) for(int a = 1, b = l; b <= n; a++, b++){
        FOR(inc, a, b){
            mxset(mxw[a][b][inc], mxw[a + 1][b][inc], mxw[a][b - 1][inc]);
        }
    }

    FOR(l, 1, n) for(int a = 1, b = l; b <= n; a++, b++){
        FOR(i, a, b) {
            mxset(dp[a][b], dp[a][i] + dp[i + 1][b], dp[a][i - 1] + mxw[a][b][i] + dp[i + 1][b]);
        }
    }

    cout << dp[1][n] << endl;
}
