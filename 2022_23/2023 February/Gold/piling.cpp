#include <iostream>
#include <cstring>
using namespace std;
#define MAXN 305
#define MAXD 20
#define MOD 1000000007

int N, Q, Al, Bl;
long long L[MAXN][MAXN], R[MAXN][MAXN];
char A[MAXD], B[MAXD], P[MAXN];

int status(char a, char b){
    if(a > b) return 2;
    return (a == b);
}

void solve(long long (&DP)[MAXN][MAXN], int Pl, char T[], int Tl){
    for(int i = 1; i <= Pl; i++){ // for each
        long long dp[Tl + 1][Tl + 1][3]; //  segment   //   dp[i][j][k] = ways to get (0)< /(1)= /(2)> indicies i to j(where i <= j) of target w/ pile digits j to pile.length()
        for(int x = 0; x <= Tl; x++) /* representing  */ for(int y = 0; y <= Tl; y++) for(int z = 0; z <= 2; z++) dp[x][y][z] = 0;
        for(int j = i; j <= Pl; j++) { // pile digits i to j(where i <= j)

            for(int x = 1; x <= Tl; x++) for(int y = Tl; x < y; y--){  // for each x, y, representing target digits x to y(where x < y)
                // {CASE A} ADD DIGIT J TO FRONT/LARGEST PLACE VALUE
                if(P[j] > T[x]){ // if pile digit j greater than target digit x
                    for(int k = 0; k <= 2; k++) dp[x][y][2] += dp[x + 1][y][k]; // status stays greater
                } else if(P[j] == T[x]){ // if pile digit j equal to target digit x
                    for(int k = 0; k <= 2; k++) dp[x][y][k] += dp[x + 1][y][k]; // status stays equal
                } else{ // if pile digit j less than target digit x
                    for(int k = 0; k <= 2; k++) dp[x][y][0] += dp[x + 1][y][k]; // status stays less than
                }

                // {CASE B} ADD DIGIT J TO BACK/LEAST PLACE VALUE
                dp[x][y][0] += dp[x][y - 1][0];
                dp[x][y][status(P[j], T[y])] += dp[x][y - 1][1];
                dp[x][y][2] += dp[x][y - 1][2];
                
                for(int k = 0; k <= 2; k++) dp[x][y][k] %= MOD;
            } 

            // {CASE C} ADD DIGIT J ALONE/AS SINGLE DIGIT
            for(int x = 1; x <= Tl; x++) {
                dp[x][x][status(P[j], T[x])] += 2;
            }
            
            // update answer
            for(int x = 1; x <= Tl; x++){
                DP[i][j] += dp[x][Tl][0];
                DP[i][j] += dp[x][Tl][1];
                if(x != 1) DP[i][j] += dp[x][Tl][2];
                DP[i][j] %= MOD;
            }
        }
    }
}

int main(){
    long long a, b;
    cin >> N >> a >> b;
    Al = to_string(--a).length(), Bl = to_string(b).length();
    strcpy(A, (' ' + to_string(a)).c_str()); if(a == 0) A[1] = '0';
    strcpy(B, (' ' + to_string(b)).c_str());
    for(int i = 1, p; i <= N; i++) {
        cin >> p; P[i] = p + '0';
    }

    solve(L, N, A, Al);
    solve(R, N, B, Bl);

    cin >> Q;
    for(int i = 1, l, r; i <= Q; i++){
        cin >> l >> r;
        long long ANS = R[l][r] - L[l][r];
        ANS += MOD;
        ANS %= MOD;
        cout << ANS << endl;
    }
}
