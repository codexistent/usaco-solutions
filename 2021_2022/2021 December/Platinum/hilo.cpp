#include <iostream>
#define MAXN 5005
#define MOD 1000000007
using namespace std;

int N, X, Y;
long long R, I[MAXN];

int main(){
    cin >> N >> X;
    Y = N - X;

    // calculate modular inverses
    for(long long i = 1, j, mod; i < MAXN; i++){
        I[i] = 1, mod = MOD - 2, j = i;
        while(mod){
            if(mod & 1) I[i] *= j, I[i] %= MOD;
            mod >>= 1;
            j *= j, j %= MOD;
        }
    }

    // compute expected value w/ dynamic programming
    long long DP[X + 1][Y + 1][2], XPFX[X + 1], YPFX[Y + 1];
    fill(XPFX, XPFX + X + 1, 0), fill(YPFX, YPFX + Y + 1, 0);
    for(int x = 0; x <= X; x++){
        for(int y = 0; y <= Y; y++){
            DP[x][y][0] = (XPFX[x] + YPFX[y]) * I[x + y], DP[x][y][0] %= MOD;
            DP[x][y][1] = (XPFX[x] + YPFX[y] + x) * I[x + y], DP[x][y][1] %= MOD;

            XPFX[x] += DP[x][y][1], XPFX[x] %= MOD;
            YPFX[y] += DP[x][y][0], YPFX[y] %= MOD;
        }
    }

    // compute sum from expected value
    R = DP[X][Y][0];
    for(int i = 1; i <= N; i++) R *= i, R %= MOD;
    cout << R;
    return 1;
}
