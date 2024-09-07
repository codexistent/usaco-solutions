#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 300005
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

ll n, k, pfx[MAXN], dp[MAXN];
string s;

int main(){
    ifstream cin("redistricting.in");
    ofstream cout("redistricting.out");

    cin >> n >> k >> s;
    pfx[0] = 0;
    FOR(i, 1, n) pfx[i] = pfx[i - 1] + ((s[i - 1] == 'H') ? 1 : -1);

    multiset<pair<ll, ll>> ms; 
    dp[0] = 0, ms.insert({dp[0], pfx[0]});
    FOR(i, 1, n){
        dp[i] = (*ms.begin()).first + (pfx[i] - (*ms.begin()).second <= 0);
        ms.insert({dp[i], pfx[i]});
        if(k <= i) ms.erase(ms.find({dp[i - k], pfx[i - k]}));
    }

    cout << dp[n] << endl;
}
