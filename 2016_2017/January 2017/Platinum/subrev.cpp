#include <fstream>
using namespace std;
#define MAXN 55
#define FOR(i, a) for(int i = 1; i <= a; i++)
#define SET_MAX(a, b) a = max(a, b);

int N, A[MAXN], DP[MAXN][MAXN][MAXN][MAXN], R = -1;

int main(){
    ifstream cin("subrev.in");
    ofstream cout("subrev.out");

    // [STEP 1 : GET/SET DATA]
    cin >> N;
    FOR(i, N) cin >> A[i];
    FOR(i, MAXN - 1) FOR(j, MAXN - 1) FOR(k, MAXN - 1) FOR(l, MAXN - 1) DP[i][j][k][l] = -1;
    
    // [STEP 2 : DOWN-UP DP]
    for(int l = 0; l <= N; l++){ // for l length of range 
        for(int a = 1, b = l; b <= N; a++, b++){ // for ranges a...b of length l
            for(int mn = 1; mn <= 50; mn++) for(int mx = mn; mx <= 50; mx++){ // for mn, mx min/max values in subseq
                if(l == 0 || (l == 1 && mn <= A[a] && A[a] <= mx)) DP[a][b][mn][mx] = l;
                if(DP[a][b][mn][mx] == -1) continue; 

                // [i, j] -> [i - 1, j]
                if(1 <= a - 1){ 
                    if(A[a - 1] <= mn) SET_MAX(DP[a - 1][b][A[a - 1]][mx], DP[a][b][mn][mx] + 1); // add A[a - 1] to subseq
                    SET_MAX(DP[a - 1][b][mn][mx], DP[a][b][mn][mx]); // dont add to subseq
                }

                // [i, j] -> [i, j + 1]
                if(b + 1 <= N){
                    if(mx <= A[b + 1]) SET_MAX(DP[a][b + 1][mn][A[b + 1]], DP[a][b][mn][mx] + 1); // add A[b + 1] to subseq
                    SET_MAX(DP[a][b + 1][mn][mx], DP[a][b][mn][mx]); // dont add to subseq
                }

                // [i, j] -> [i - 1, j + 1] & SWAP
                if(1 <= a - 1 && b + 1 <= N){
                    if(A[b + 1] <= mn) SET_MAX(DP[a - 1][b + 1][A[b + 1]][mx], DP[a][b][mn][mx] + 1); // add A[b + 1] to front of subseq
                    if(mx <= A[a - 1]) SET_MAX(DP[a - 1][b + 1][mn][A[a - 1]], DP[a][b][mn][mx] + 1); // add A[a - 1] to back of subseq
                    if(A[b + 1] <= mn && mx <= A[a - 1]) SET_MAX(DP[a - 1][b + 1][A[b + 1]][A[a - 1]], DP[a][b][mn][mx] + 2); // add A[b + 1] & A[a - 1]
                }

                R = max(R, DP[a][b][mn][mx]);
            }
        }
    }
    cout << R;
}
