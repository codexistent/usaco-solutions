#include <fstream>
#include <climits>
using namespace std;
#define MAXK 10
#define MAXN 1005

int N, K, R[MAXN], S = 1;
long long C[2*MAXN][2*MAXN], DP[MAXN][MAXK], M = LONG_MAX; // DP[i][j] = min. total cost for all cows in doors j...(S + N) to reach destination, w/ k doors and last door at j

long long cost(int i, int j){ return C[S + i - 1][S + j - 1]; } // cost accounting for offset(or the changing starting door S)

void dp(int l, int r, int sl/*search left bound*/, int sr/*search right bound*/, int k){ // divide-and-conquer dp
    if(l > r) return;
    int m = (l + r) / 2; DP[m][k] = LONG_MAX; 

    int sm = -1; /*optimal previous door for DP[m][k]*/
    for(int i = max(m, sl); i <= sr + 1; i++) if(cost(m, i) + ((i + 1 == N + 1) ? 0 : DP[i + 1][k - 1]) < DP[m][k]) {
        DP[m][k] = cost(m, i) + ((i + 1 == N + 1) ? 0 : DP[i + 1][k - 1]);
        sm = i;
    }
    dp(l, m - 1, sl, sm, k);
    dp(m + 1, r, sm, sr, k);
}

void solve(){ 
    for(int i = 1; i <= N; i++) DP[i][1] = cost(i, N); // base case

    for(int i = 2; i <= K; i++) dp(1, N, 1, N, i); // for total used doors i in range 1...K
    
    M = min(M, DP[1][K]);
}

int main(){
    ifstream cin("cbarn.in");
    ofstream cout("cbarn.out");

    // read data
    cin >> N >> K;
    for(int i = 1; i <= N; i++) cin >> R[i];

    // C[i][j] = cost for all cows in rooms i...j(clockwise) to reach destination
    for(int i = 1; i <= 2*N; i++){
        C[i][i] = 0;
        for(int j = i + 1; j <= 2*N; j++) C[i][j] = C[i][j - 1] + R[(j - 1) % N + 1] * (long long)(j - i); // build cost array
    }

    // for every starting door S, run dp
    for(S = 1; S <= N; S++) solve();

    cout << M;
}
