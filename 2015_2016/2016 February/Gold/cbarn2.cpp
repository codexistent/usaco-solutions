#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

int main(){
    ifstream cin ("cbarn2.in");
    ofstream cout ("cbarn2.out");

    ll N, K;
    cin >> N >> K;
    vector<ll> r(N);
    FOR(i, 0, N - 1) {
        cin >> r[i];
    }

    ll R = LONG_LONG_MAX;
    FOR(i, 0, N - 1){
        ll dp[N + 1][N + 1][K + 2];
        FOR(j, 0, N) FOR(k, 0, N) FOR(l, 0, K + 1) dp[j][k][l] = LONG_LONG_MAX;

        dp[1][1][1] = 0;
        FOR(j, 1, N - 1) {
            FOR(k, 1, j) {
                FOR(l, 1, K){
                    if(dp[j][k][l] == LONG_LONG_MAX) continue;
                    dp[j + 1][k][l] = min(dp[j + 1][k][l], dp[j][k][l] + r[j] * (j + 1 - k));
                    dp[j + 1][j + 1][l + 1] = min(dp[j + 1][j + 1][l + 1], dp[j][k][l]);
                }
            }
        }
        FOR(j, 1, N) R = min(R, dp[N][j][K]);
        rotate(r.begin(), r.begin() + 1, r.begin() + N);
    }

    cout << R << endl;
}
