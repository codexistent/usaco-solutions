#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define RFOR(i, a, b) for(int i = a; i >= b; i--)

int main(){
    ifstream cin ("feast.in");
    ofstream cout ("feast.out");

    int T, A, B;
    cin >> T >> A >> B;
    bool DP[T + 1][2];
    FOR(i, 0, T) DP[i][0] = DP[i][1] = false;

    DP[0][0] = DP[0][1] = true;
    FOR(t, 1, T) {
        if(t - A >= 0) DP[t][0] |= DP[t - A][0];
        if(t - B >= 0) DP[t][0] |= DP[t - B][0];
    }
    FOR(t, 1, T) {
        if(t * 2 <= T) DP[t][1] |= DP[t * 2][0];
        if(t * 2 + 1 <= T) DP[t][1] |= DP[t * 2 + 1][0];
        if(t - A >= 0) DP[t][1] |= DP[t - A][1];
        if(t - B >= 0) DP[t][1] |= DP[t - B][1];
    }

    RFOR(i, T, 0) if(DP[i][0] || DP[i][1]) {
        cout << i << endl;
        break;
    }
}
