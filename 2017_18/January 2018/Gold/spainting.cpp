#include <iostream>
#include <cmath>
using namespace std;
#define MAXN 1000005
#define MOD 1000000007

long long N, M, K, RET = 1;
long long DP[MAXN];

int main(){
    cin >> N >> M >> K;
    for(int i = 1; i <= N; i++) DP[i] = (M * (DP[i - 1]) + ((i < K) ? M : (-1)*((M - 1) * DP[i - K]) )) % MOD;
    for(int i = 1; i <= N; i++) RET = (RET * M) % MOD;
    cout << (MOD + RET - (DP[N] - DP[N - 1]) % MOD) % MOD; 
}
