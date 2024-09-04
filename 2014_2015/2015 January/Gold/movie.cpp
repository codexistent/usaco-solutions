#include <bits/stdc++.h>
using namespace std;
#define MAXN 25
#define BITSZ 1048576
#define ll long long
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

ll n, l, dp[BITSZ];
pair<ll, ll> r;
vector<pair<ll, ll>> sfx[MAXN];

int main(){
    cin >> n >> l;
    FOR(m, 0, BITSZ -1) dp[m] = 0; 
    FOR(i, 1, n){
        vector<ll> s;
        ll d, m; cin >> d >> m;
        FOR(j, 1, m){
            ll a; cin >> a;
            s.push_back(a);
        }
        sort(s.begin(), s.end());

        sfx[i].push_back({0, 0});
        FOR(j, 1, m) {
            sfx[i].push_back({s[i][j - 1].first, max(sfx[i][j - 1].second, s[j - 1] + d)});
        }
    }

    r = {-1, n + 1};
    ll BITSZn = pow(2, n);
    FOR(m, 1, BITSZn - 1){
        ll mv = 0;
        FOR(i, 1, n) if(m & (1 << (i - 1))) {
            mv++;
            ll m2 = m & ~(1 << (i - 1));

            ll a = 0, b = sfx[i].size() - 1;
            while(a != b){
                ll c = (a + b + 1) / 2;
                
            }

        }
    }


}
