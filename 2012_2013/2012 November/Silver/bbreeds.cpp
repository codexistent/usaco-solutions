#include <bits/stdc++.h>
using namespace std;
#define MAXN 1005
#define ll long long
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

string s;
ll n, d[MAXN], dp[MAXN][MAXN];

int main(){
    ifstream cin("bbreeds.in");
    ofstream cout("bbreeds.out");

    cin >> s;
    n = s.length();
    d[0] = 0;
    FOR(i, 1, n){
        d[i] = d[i - 1] + (s[i - 1] == '(') - (s[i - 1] == ')');
        if(d[i] < 0) {
            cout << 0 << endl;
            return 0;
        }
    }

    FOR(i, 0, n) FOR(j, 0, n) dp[i][j] = 0;
    dp[0][0] = 1;
    FOR(i, 1, n){
        FOR(dh, 0, d[i]){
            ll dg = d[i] - dh;

            if(s[i - 1] == '('){
                if(dh != 0) dp[i][dh] = dp[i - 1][dh - 1] % 2012;
                if(dg != 0) dp[i][dh] = (dp[i][dh] + dp[i - 1][dh]) % 2012;
            }else{
                dp[i][dh] = dp[i - 1][dh + 1] % 2012;
                dp[i][dh] = (dp[i][dh] + dp[i - 1][dh]) % 2012;
            }
        }
    }
    
    ll r = 0;
    FOR(i, 0, d[n]) r = (r + dp[n][i]) % 2012;

    cout << r << endl;
}
