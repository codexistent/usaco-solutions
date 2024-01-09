#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)

int main(){
    ifstream cin("subrev.in");
    ofstream cout("subrev.out");

    int N;
    cin >> N;
    int V[N + 1];
    FOR(i, 1, N) cin >> V[i];

    int DP[N + 2][N + 2][52][52];
    FOR(i, 0, N + 1) FOR(j, 0, N + 1) FOR(k, 0, 51) FOR(l, 0, 51) DP[i][j][k][l] = 0;

    FOR(l, 1, N) for(int a = 1, b = a + l - 1; b <= N; a++, b++){
        FOR(r, 1, 50) for(int mn = 1, mx = mn + r - 1; mx <= 50; mn++, mx++){
            DP[a][b][mn][mx] = max(
                max(DP[a + 1][b][mn][mx], DP[a][b - 1][mn][mx]),
                max(DP[a][b][mn + 1][mx], DP[a][b][mn][mx - 1])
            );

            // swap a & b
            if(V[b] == mn || V[a] == mx) DP[a][b][mn][mx] = max(DP[a][b][mn][mx], DP[a + 1][b - 1][mn][mx] + 1);
            if(V[b] == mn && V[a] == mx && a != b) DP[a][b][mn][mx] = max(DP[a][b][mn][mx], DP[a + 1][b - 1][mn][mx] + 2);

            // don't swap a & b
            if(V[a] == mn) DP[a][b][mn][mx] = max(DP[a][b][mn][mx], DP[a + 1][b][mn][mx] + 1);
            if(V[b] == mx) DP[a][b][mn][mx] = max(DP[a][b][mn][mx], DP[a][b - 1][mn][mx] + 1);
            if(V[a] == mn && V[b] == mx && a != b) DP[a][b][mn][mx] = max(DP[a][b][mn][mx], DP[a + 1][b - 1][mn][mx] + 2);
        }
    }

    cout << DP[1][N][1][50] << endl;
}
