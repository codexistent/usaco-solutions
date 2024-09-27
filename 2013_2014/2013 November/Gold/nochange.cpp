#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 100005
#define LOGN 65536
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

ll n, m, c[20], pfx[MAXN];
pair<ll, ll> dp[LOGN];

int main(){
    ifstream cin("nochange.in");
    ofstream cout("nochange.out");

    cin >> m >> n;
    FOR(i, 1, m) cin >> c[i];
    pfx[0] = 0; FOR(i, 1, n) {
        cin >> pfx[i];
        pfx[i] += pfx[i - 1];
    }

    ll logn = pow(2, m);
    FOR(j, 0, logn - 1) dp[j] = {-1, -1};
    dp[0] = {0, 0};
    FOR(msk, 0, logn - 1){
        if(dp[msk].first == -1) continue;
        FOR(ci, 1, m) if((msk & (1 << (ci - 1))) == 0) {
            ll st = dp[msk].first, sv = dp[msk].second;

            ll lo = st, hi = n;
            while(lo < hi){
                ll md = (lo + hi + 1) / 2;
                if(pfx[md] - pfx[st] <= c[ci]){
                    lo = md;
                }else{
                    hi = md - 1;
                }
            }

            dp[msk | (1 << (ci - 1))] = max(dp[msk | (1 << (ci - 1))], {lo, sv});
            dp[msk | (1 << (ci - 1))] = max(dp[msk | (1 << (ci - 1))], {st, sv + c[ci]});
        }
    }

    ll r = (dp[logn - 1].first == n) ? dp[logn - 1].second : -1;
    cout << r << endl;
}
