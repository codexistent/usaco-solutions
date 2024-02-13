#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)

int main(){
    ifstream cin("redistricting.in");
    ofstream cout ("redistricting.out");
    int n, k; string s; cin >> n >> k >> s;
    int pfx[n + 1]; pfx[0] = 0;
    FOR(i, 1, n) if(s[i - 1] == 'H') pfx[i] = pfx[i - 1] + 1; else pfx[i] = pfx[i - 1] - 1;

    int dp[n + 1];
    multiset<pair<int, int>> dps;
    dp[0] = 0, dps.insert(make_pair(0, 0));
    FOR(i, 1, n){
        dp[i] = (*dps.begin()).first + (pfx[i] - (*dps.begin()).second <= 0);
        dps.insert(make_pair(dp[i], pfx[i]));
        if(0 <= i - k) dps.erase(dps.find(make_pair(dp[i - k], pfx[i - k])));
    }

    cout << dp[n] << endl;
}
