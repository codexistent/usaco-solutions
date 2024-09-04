#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define MAXN 1005
#define ll long long

ll n, dp[MAXN][MAXN][2];
vector<ll> p;

int main(){
    ifstream cin("cowrun.in");
    ofstream cout("cowrun.out");

    cin >> n; n++;
    FOR(i, 1, n - 1){
        ll x; cin >> x;
        p.push_back(x);
    }
    p.push_back(0);
    sort(p.begin(), p.end());
    
    FOR(i, 0, MAXN - 1) {
        FOR(j, 0, MAXN - 1) dp[i][j][0] = dp[i][j][1] = -1;
        if(i < p.size() && p[i] == 0) dp[i][i][0] = dp[i][i][1] = 0;
    }

    FOR(l, 2, n){
        FOR(i, 0, n - 1) FOR(j, i + l - 1, n - 1){
            // ends at left
            if(dp[i + 1][j][0] != -1) dp[i][j][0] = (dp[i][j][0] == -1) ? (dp[i + 1][j][0] + (n - l + 1) * abs(p[i] - p[i + 1])) : min(dp[i][j][0], dp[i + 1][j][0] + (n - l + 1) * abs(p[i] - p[i + 1]));
            if(dp[i + 1][j][1] != -1) dp[i][j][0] = (dp[i][j][0] == -1) ? (dp[i + 1][j][1] + (n - l + 1) * abs(p[i] - p[j])) : min(dp[i][j][0], dp[i + 1][j][1] + (n - l + 1) * abs(p[i] - p[j]));
            
            // ends at right
            if(dp[i][j - 1][0] != -1) dp[i][j][1] = (dp[i][j][1] == -1) ? (dp[i][j - 1][0] + (n - l + 1) * abs(p[j] - p[i])) : min(dp[i][j][1], dp[i][j - 1][0] + (n - l + 1) * abs(p[j] - p[i]));
            if(dp[i][j - 1][1] != -1) dp[i][j][1] = (dp[i][j][1] == -1) ? (dp[i][j - 1][1] + (n - l + 1) * abs(p[j] - p[j - 1])) : min(dp[i][j][1], dp[i][j - 1][1] + (n - l + 1) * abs(p[j] - p[j - 1]));
        }
    }

    cout << min(((dp[0][n - 1][0] != -1) ? dp[0][n - 1][0] : INT_MAX), (dp[0][n - 1][1] != -1 ? dp[0][n - 1][1] : INT_MAX)) << endl;
}
