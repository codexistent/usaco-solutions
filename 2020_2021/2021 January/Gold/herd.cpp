#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define BITMAX 1048576
#define mp make_pair

int main(){
    int n;
    string s;
    cin >> s;
    n = s.length();

    map<char, int> ID;
    for(char c : s) if(ID.find(c) == ID.end()) ID.insert(mp(c, ID.size()));

    int adj[20][20], c[20]; 
    FOR(i, 0, 19) FOR(j, 0, 19) adj[i][j] = 0;
    FOR(i, 0, 19) c[i] = 0; 
    FOR(i, 1, n - 1) adj[ID.at(s[i - 1])][ID.at(s[i])]++;
    FOR(i, 0, n - 1) c[ID.at(s[i])]++;


    int dp[BITMAX];
    FOR(m, 0, BITMAX - 1) dp[m] = n;
    dp[0] = 0;

    for(int m = 1; m < BITMAX; m++){
        for(int i = 0; i <= 19; i++){
            if(m & (1 << i)){
                int v2 = dp[m & ~(1 << i)] + c[i];
                for(int j = 0; j <= 19; j++) if(i != j && m & (1 << j)) {
                    v2 -= adj[j][i];
                }
                dp[m] = min(dp[m], v2);
            }
        }
    }

    cout << dp[BITMAX - 1] << endl;
}
