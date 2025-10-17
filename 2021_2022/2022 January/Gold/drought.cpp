#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define FOR(ict, ist, ied) for(int ict = ist; ict <= ied; ict++)
#define RFOR(ict, ist, ied) for(int ict = ist; ict >= ied; ict--)
const ll MAXN = 1e2 + 5;
const ll MAXH = 1e3 + 5;
const ll MOD = 1e9 + 7;

ll n, mnh = LLONG_MAX, mxh = 0ll, dp[MAXN][MAXH];
vector<ll> h;

ll ct(){
    FOR(i, 0, MAXN - 5) FOR(j, 0, MAXH - 5) dp[i][j] = 0ll;
    // handle i = 2;
    FOR(j, 0, min(h[1], h[2])) dp[2][j] = 1;
    FOR(i, 3, n){
        ll sm = 0ll, ptr = 0;
        RFOR(j, h[i], 0){
            // We must satisfy: (j' <= h[i - 1] - j)
            while(ptr <= h[i - 1] && ptr + j <= h[i - 1]){
                sm = (sm + dp[i - 1][ptr]) % MOD;
                ptr++;
            }

            dp[i][j] = sm;
        }
    }

    ll r = 0ll;
    FOR(i, 0, h[n]) r = (r + dp[n][i]) % MOD;
    return r;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    h.resize(n + 1);
    FOR(i, 1, n) {
        cin >> h[i];
        mnh = min(mnh, h[i]), mxh = max(mxh, h[i]);
    }
    if(n == 1){
        cout << (int)(h[1] == 0) << endl;
        return 0;
    }

    ll r = ct();
    if(n % 2){
        FOR(mni, 1, mnh){
            FOR(i, 1, n) h[i] -= 1;
            r = (r + ct()) % MOD;
        }
    }

    cout << r << endl;
}
