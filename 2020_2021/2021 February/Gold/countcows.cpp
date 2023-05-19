#include <iostream>
using namespace std;
#define MAXQ 10005
#define FOR(i, a, b) for(int i = a; i < b; i++)

long long Q, X, Y, D, P[45], DP[3][2][2], dp[3][2][2];

int trite(long long x, int pv) { return (x / P[pv - 1]) % 3; }

void solve(){
    cin >> D >> X >> Y;

    FOR(i, 0, 3) FOR(j, 0, 2) FOR(k, 0, 2) dp[i][j][k] = 0; // set dp array to zero
    dp[1][0][0] = 1; // base case

    for(int i = 1; i < 40; i++){ // for each (i - 1)^3 trite place value; we're determining trite i
        FOR(i2, 0, 3) FOR(j2, 0, 2) FOR(k2, 0, 2) DP[i2][j2][k2] = 0;
        // bottom- up dp
        int dd = trite(D, i), xd = trite(X, i), yd = trite(Y, i);
        for(int cmp = 0; cmp <= 2; cmp++) for(int xc = 0; xc <= 1; xc++) for(int yc = 0; yc <= 1; yc++) { // for each prior state (cmp to d, x carry, y carry)
            for(int j = 0; j < 3; j++){
                int XD = (xd + xc + j) % 3, YD = (yd + yc + j) % 3;
                int XC = (xd + xc + j) / 3, YC = (yd + yc + j) / 3;
                int CMP = (j < dd) ? 0 : (dd < j) ? 2 : cmp;
                if(XD % 2 == YD % 2) DP[CMP][XC][YC] += dp[cmp][xc][yc];
            }
        }
        swap(dp, DP); // 2-row mem. optimization
    }

    cout << dp[0][0][0] + dp[1][0][0] << endl;
}

int main(){
    cin >> Q; P[0] = 1;
    for(int i = 1; i < 40; i++) P[i] = P[i - 1] * 3ll; // P[i] = 3^i

    for(int i = 1; i <= Q; i++) solve();
}
