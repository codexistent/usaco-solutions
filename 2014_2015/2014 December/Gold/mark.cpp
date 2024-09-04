#include <bits/stdc++.h>
using namespace std;
#define MAXN 25
#define BITSZ 1048576
#define ll long long
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

struct Cow{ ll h, w, s; };

ll n, h, dp[BITSZ], mx = -1;
Cow c[MAXN];

int main() {
    ifstream cin("guard.in");
    ofstream cout("guard.out");

    cin >> n >> h;
    FOR(i, 0, BITSZ - 1) dp[i] = -1;
    FOR(i, 1, n) {
        cin >> c[i].h >> c[i].w >> c[i].s;
        dp[1 << (i - 1)] = c[i].s;
    }
    
    ll BITSZn = pow(2, n);
    FOR(m, 1, BITSZn - 1){
        if((m & (m - 1)) == 0) {  
            continue;
        }

        ll hsum = 0;
        FOR(i, 1, n) if(m & (1 << (i - 1))) {
            hsum += c[i].h;
            ll m2 = m & ~(1 << (i - 1));
            if(dp[m2] - c[i].w >= 0){
                dp[m] = max(dp[m], min(dp[m2] - c[i].w, c[i].s));
            }
        }

        if(hsum >= h){
            mx = max(mx, dp[m]);
        }
    }

    if(mx == -1){
        cout << "Mark is too tall" << endl;
    }else{
        cout << mx << endl;
    }
}
