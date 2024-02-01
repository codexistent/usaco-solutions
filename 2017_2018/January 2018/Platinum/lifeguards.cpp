// inspo: https://github.com/jessechoe10/USACO/blob/9a81febe689d0dcbd9c06eadf118edc639bf30c8/Plat/lifeguards.cpp#L21

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define f first
#define s second
#define pb push_back
#define mp make_pair

int main() {
    ifstream cin ("lifeguards.in");
    ofstream cout ("lifeguards.out");

    ll n, k; cin >> n >> k;
    vector<pair<ll, ll>> c(n), c2;
    FOR(i, 0, n - 1) cin >> c[i].f >> c[i].s;
    sort(begin(c), end(c));

    for(auto i : c) if(!c2.size() || (c2.size() && c2.back().s < i.s)) c2.pb(i); else k--;
    swap(c, c2), k = max(k, 0LL);

    ll r = 0, l = 0, dp[n][k + 1], mx[n][k + 1];
    FOR(i, 0, c.size() - 1){
        while(c[l].s < c[i].f) l++;
        FOR(j, 0, k){
            if(j > i) dp[i][j] = LLONG_MIN + 2000000005;
            else {
                dp[i][j] = 0;
                if(l < i) dp[i][j] = max(dp[i][j], dp[l][max(0LL, j - (i - l - 1))] + c[i].s - c[l].s);
                dp[i][j] = max(dp[i][j], (l ? mx[l - 1][max(0LL, j - (i - l))] : 0) + c[i].s - c[i].f);
            }
            mx[i][j] = dp[i][j];
            if(i && j) mx[i][j] = max(mx[i][j], mx[i - 1][j - 1]);
        }
        r = max(r, dp[i][max(0LL, k - ((ll)c.size() - (i + 1)))]);
    }
    cout << r << endl;
}
