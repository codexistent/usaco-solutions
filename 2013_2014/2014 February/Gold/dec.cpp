#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 25
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

ll n, m, s[MAXN][MAXN];
vector<pair<ll, ll>> b[MAXN];

ll bonus(ll k, ll cp){
    FOR(i, 1, b[k].size()){
        if(b[k][i - 1].first <= cp){
            cp += b[k][i - 1].second;
        } else break;
    }
    return cp;
}

int main(){
    ifstream cin("dec.in");
    ofstream cout("dec.out");

    cin >> n >> m;
    FOR(i, 1, m){
        ll ki, pi, ai;
        cin >> ki >> pi >> ai;
        b[ki].push_back({pi, ai});
    }
    FOR(i, 1, n) FOR(j, 1, n) cin >> s[i][j];
    FOR(i, 0, n) sort(begin(b[i]), end(b[i]));

    ll MXMSK = pow(2, n), dp[MXMSK];
    FOR(msk, 0, MXMSK - 1) dp[msk] = 0;
    dp[0] = bonus(0, dp[0]);

    FOR(msk, 1, MXMSK - 1){
        ll k = 0;
        FOR(i, 1, n) if(msk & (1 << (i - 1))) k++;

        FOR(i, 1, n) if(msk & (1 << (i - 1))) {
            dp[msk] = max(dp[msk], dp[msk & ~(1 << (i - 1))] + s[i][k]); 
        }
        dp[msk] = bonus(k, dp[msk]);
    }

    cout << dp[MXMSK - 1] << endl;
}
