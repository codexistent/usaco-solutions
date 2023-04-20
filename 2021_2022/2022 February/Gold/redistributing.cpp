#include <iostream>
#include <bitset>
using namespace std;
#define MAXN 20

int N, Q;
int P[MAXN];
long long DP[1 << MAXN][MAXN], R[1 << MAXN];

long long solve(){
    int h = 0, g = 0;
    string s;
    cin >> s;
    s = ' ' + s;
    for(int i = 1; i <= N; i++){
        if(s[i] == 'H') h |= (1 << i);
        else g |= (1 << i);
    }

    return R[h] * R[g];
}

int main() { // {1 - BASED INDEXING}
    // [1 : SET PREFERENCES]
    cin >> N;
    for(int i = 1; i <= N; i++){
        for(int j = 1, s = 0, g; j <= N; j++){
            cin >> g;
            if(s) continue;
            P[i] |= (1 << g), s |= (g == i);
        }
    }

    // [2 : DP]
    R[0] = 1;
    for(int i = 1; i <= N; i++) DP[1 << i][i] = 1; // for each i starting cow/largest cow in cycle there is 1 way to start
    for(int i = 1; i <= N; i++){ // for each i starting cow/largest cow in cycle
        for(int mask = (1 << i); mask < (1 << (i + 1)); mask++){ // for every bitmask 'mask' where cow i is visited
            for(int j = 1; j <= i; j++){ // for each j directly previous visited cow in cycle 
                // CASE A - EXTEND CYCLE
                for(int k = 1; k < i; k++){ // for each k possible next cow in cycle
                    if(!(mask & (1 << k)) && P[j] & (1 << k)) {
                        DP[mask ^ (1 << k)][k] += DP[mask][j]; // if not visited in cycle and more preferable by cow j
                    }
                }
                // CASE B - END CYCLE
                if(P[j] & (1 << i)) {
                    R[mask] += DP[mask][j];
                }
            }
            // CASE C - START NEW CYCLE
            for(int j = i + 1; j <= N; j++){ // for each j starting cow in new cycle
                DP[mask ^ (1 << j)][j] += R[mask];
            }
        }
    }

    // [3 : PROCESS QUERIES]
    cin >> Q;
    for(int i = 1; i <= Q; i++) cout << solve() << endl;
}
