#include <iostream>
#include <vector>
using namespace std;
#define MAXN 100005
#define INF 1000000007

int T, N, K, UPW;
int X[MAXN], W[MAXN], C[MAXN], Cs; // Cs = chain size

bool odd(int i){
    return i % 2;
}

int solve(){
    int R = INF;

if(T == 1){ // CASE A : MIN LEFTOVER
    if(!odd(Cs)) return 0; // if even # cows in chain pair all up; if odd -VVV-

    for(int i = 1; i <= Cs; i++){ // for each i cow 1...Cs(chain size) 
        if(odd(i) || X[C[i + 1]] - X[C[i - 1]] <= K) // if cow i @ edge of chain OR odd chain index
            R = min(R, W[C[i]]); // take min(current return, weight of cow i) for return value
    }

}else if(T == 2){ // CASE B : MAX LEFTOVER
    int dp[Cs + 2][2], c2 = Cs + 1; // dp[i][j] = max. leftover weight w/ cows i...Cs and j(1/0) yet-to-be-paired cows 
    dp[Cs + 1][0] = 0, dp[Cs + 1][1] = -INF; // set defaults

    for(int i = Cs; 1 <= i; i--){ // for each cow Cs(chain size)...i
        dp[i][0] = dp[i + 1][1], dp[i][1] = dp[i + 1][0]; // CASE B.A : COW i is PAIRED

        // CASE B.B : COW i IS UNPAIRED
        while(i < c2 - 1 && X[C[c2 - 1]] - X[C[i]] > K) c2--; // update leftmost cow that is unpairable if i unpaired
        
        int g = c2 - i - 1; // g = gap/# paired cows between i and c2
        dp[i][0] = max(dp[i][0], dp[c2][odd(g)] + W[C[i]]); // update dp for cow i with no unpaired cows remaining
        if(i == 1 || i == Cs || X[C[i + 1]] - X[C[i - 1]] <= K){ // if cow i @ edge of chain OR i+1 and i-1 gap <= K 
            dp[i][1] = max(dp[i][1], dp[c2][!odd(g)] + W[C[i]]); // update dp for cow i with 1 unpaired cow remaining
        }
    }

    R = dp[1][0];
    if(!odd(Cs)) R = max(R, 0);
}
    return R;
}

int main(){
    cin >> T >> N >> K;
    for(int i = 1; i <= N; i++){
        cin >> X[i] >> W[i];
        if(!(Cs == 0 || X[i] - X[i - 1] <= K)) { // if end of current chain
            UPW += solve(); // solve chain
            Cs = 0; // refresh chain to size 0
        }

        if(Cs == 0 || X[i] - X[i - 1] <= K){ // update chain 
            Cs++;
            C[Cs] = i;
        }
    }
    if(Cs != 0) UPW += solve(); // solve one more time if remaining chain is not empty
    cout << UPW;
}
