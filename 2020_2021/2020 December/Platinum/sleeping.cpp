#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 3005
#define MOD 1000000007

long long mod_s(long long a, long long b){ // mod sum
    return (a + b + MOD) % MOD; 
}
long long mod_p(long long a, long long b){ // mod product
    return (a * b + MOD) % MOD; 
}

int N;
long long DP[2][MAXN][2];
pair<int, int> S[MAXN * 2];

int main(){
    cin >> N;
    for(int i = 1, x; i <= N; i++){
        cin >> x;
        S[i] = make_pair(x, 0);
    }
    for(int i = 1, x; i <= N; i++){
        cin >> x;
        S[i + N] = make_pair(x, 1);
    }
    sort(S + 1, S + 1 + 2 * N, [](const pair<int, int>& a, pair<int, int>& b){ return (a.first != b.first) ? (a.first < b.first) : (a.second < b.second); });

    for(int j = 0; j < MAXN; j++) DP[0][j][0] = DP[0][j][1] = 0;
    DP[0][0][0] = 1;
    for(int i = 1; i <= 2*N; i++){
        int c = i % 2, p = (i + 1) % 2;
        for(int j = 0; j < MAXN; j++) DP[c][j][0] = DP[c][j][1] = 0;
        for(int j = 0; j <= N; j++){
            // CASE A) k == 0 ~ all cows assigned
            if(S[i].second == 0){ // cow
                if(j - 1 >= 0) DP[c][j][0] = mod_s(DP[c][j][0], DP[p][j - 1][0]); // assign cow
            }else{ // barn
                DP[c][j][0] = mod_s(DP[c][j][0], mod_p(DP[p][j + 1][0], j + 1)); // use barn
                DP[c][j][0] = mod_s(DP[c][j][0], DP[p][j][0]); // skip barn
            }

            // CASE B) k == 1
            if(S[i].second == 0){ // cow
                if(j - 1 >= 0) DP[c][j][1] = mod_s(DP[c][j][1], DP[p][j - 1][1]); // assign cow
                DP[c][j][1] = mod_s(DP[c][j][1], mod_s(DP[p][j][0], DP[p][j][1])); // skip cow
            }else{ // barn
                DP[c][j][1] = mod_s(DP[c][j][1], mod_p(DP[p][j + 1][1], j + 1)); // use barn
            }
        }
    }

    cout << mod_s(DP[0][0][0], DP[0][0][1]) << endl;
}
