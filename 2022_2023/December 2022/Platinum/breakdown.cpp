#include <iostream>
#include <cmath>
using namespace std;
#define MAXN 305
#define MAXK 10
#define INF 9000000000000

int N, K;
long long W[MAXN][MAXN], DP1[5][MAXN], DPN[5][MAXN], B[3][MAXN][MAXN], R[MAXN * MAXN];
pair<int, int> E[MAXN * MAXN];

int main(){
    cin >> N >> K;
    for(int i = 1; i <= N; i++) for(int j = 1; j <= N; j++) cin >> W[i][j];
    for(int i = 0; i < N * N; i++) cin >> E[N * N - i].first >> E[N * N - i].second;

    // set all dp values to +inf
    for(int i = 0; i < 5; i++) for(int j = 0; j < MAXN; j++) DP1[i][j] = DPN[i][j] = INF;
    for(int i = 0; i < 3; i++) for(int j = 0; j < MAXN; j++) for(int k = 0; k < MAXN; k++) B[i][j][k] = INF;

    for(int e = 1; e <= N * N; e++){
        int a = E[e].first, b = E[e].second, w = W[a][b];
        // A) find shortest path from a to b
        long long p = INF;
        for(int i = 1; i <= N; i++) {
            p = min(p, DP1[(int)ceil(K / 2.0)][i] + DPN[(int)floor(K / 2.0)][i]);
        }
        R[N * N - e + 1] = (p == INF) ? -1 : p;

        // B) update B(B[i][j][k] = minimum length/weight path between/from j to k with i edges)
        //  case A.1) B[1] ~ length 1 path
            B[1][a][b] = w;
        //  case A.2) B[2] ~ length 2 path (update DP1[2] & DPN[2] here as well)
            for(int i = 1; i <= N; i++) {
                B[2][a][i] = min(B[2][a][i], w + B[1][b][i]); // a->b is edge #1
                B[2][i][b] = min(B[2][i][b], B[1][i][a] + w); // a->b is edge #2

                if(a == 1) DP1[2][i] = min(DP1[2][i], B[2][a][i]);
                if(b == N) DPN[2][i] = min(DPN[2][i], B[2][i][b]);

                if(i == 1) DP1[2][b] = min(DP1[2][b], B[2][i][b]); 
                if(i == N) DPN[2][a] = min(DPN[2][a], B[2][a][i]); 
            }

        // C) update DP1 and DPN
        //  case B.1) DP1[1] & DPN[1] and DP1[2] & DPN[2]
            if(a == 1) DP1[1][b] = w;
            if(b == N) DPN[1][a] = w;
        //  case B.2) DP1[3] & DPN[3]
            DPN[3][a] = min(DPN[3][a], w + B[2][b][N]);
            DP1[3][b] = min(DP1[3][b], B[2][1][a] + w);
            for(int i = 1; i <= N; i++){
                // a->b is edge #1
                if(a == 1) DP1[3][i] = min(DP1[3][i], w + B[2][b][i]);

                // a->b is edge #2
                DP1[3][i] = min(DP1[3][i], B[1][1][a] + w + B[1][b][i]);
                DPN[3][i] = min(DPN[3][i], B[1][i][a] + w + B[1][b][N]);

                // a->b is edge #3
                if(b == N) DPN[3][i] = min(DPN[3][i], B[2][i][a] + w);
            }
        //  case B.2) DP1[4] & DPN[4]
            for(int i = 1; i <= N; i++){
                // a->b is edge #2
                DP1[4][i] = min(DP1[4][i], B[1][1][a] + w + B[2][b][i]);
                DPN[4][i] = min(DPN[4][i], B[1][i][a] + w + B[2][b][N]);

                // a->b is edge #3
                DP1[4][i] = min(DP1[4][i], B[2][1][a] + w + B[1][b][i]);
                DPN[4][i] = min(DPN[4][i], B[2][i][a] + w + B[1][b][N]);
            }

            // a->b is edge #1
            if(a == 1){
                for(int i = 1; i <= N; i++) for(int j = 1; j <= N; j++) DP1[4][j] = min(DP1[4][j], w + B[2][b][i] + B[1][i][j]);
            }
            for(int i = 1; i <= N; i++) DPN[4][a] = min(DPN[4][a], w + B[2][b][i] + B[1][i][N]);

            // a->b is edge #4
            for(int i = 1; i <= N; i++) DP1[4][b] = min(DP1[4][b], B[2][1][i] + B[1][i][a] + w);
            if(b == N){
                for(int i = 1; i <= N; i++) for(int j = 1; j <= N; j++) DPN[4][i] = min(DPN[4][i], B[2][i][j] + B[1][j][a] + w);
            }
    }

    for(int i = 1; i <= N*N; i++) cout << R[i] << endl;
}
