#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000009
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define ll long long

void ma(ll& a, ll b) { a = (a + b) % MOD; }
void ms(ll& a, ll b) { a = (a - b + MOD) % MOD; }

int main(){
    ifstream cin("team.in");
    ofstream cout("team.out");
    
    ll N, M, K;
    cin >> N >> M >> K;
    ll J[N + 1], P[M + 1];
    FOR(i, 1, N) cin >> J[i];
    FOR(i, 1, M) cin >> P[i];
    sort(J + 1, J + N + 1), sort(P + 1, P + M + 1);

    ll DP[N + 1][M + 1][K + 1];
    FOR(i, 0, N) FOR(j, 0, M) FOR(k, 0, K) { DP[i][j][k] = 0; }
    FOR(i, 0, N) DP[i][0][0] = 1;
    FOR(i, 0, M) DP[0][i][0] = 1;

    FOR(i, 1, N) {
        FOR(j, 1, M){
            FOR(k, 0, K){
                if(i > 0) ma(DP[i][j][k], DP[i - 1][j][k]);
                if(j > 0) ma(DP[i][j][k], DP[i][j - 1][k]);
                if(i > 0 && j > 0) ms(DP[i][j][k], DP[i - 1][j - 1][k]);

                if(J[i] > P[j] && k != 0) ma(DP[i][j][k], DP[i - 1][j - 1][k - 1]);
            }
        }
    }

    cout << DP[N][M][K];
}
