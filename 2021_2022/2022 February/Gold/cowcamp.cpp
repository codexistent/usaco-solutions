#include <iostream>
#include <cmath>
using namespace std;
#define MAXT 1005 // **problem statement writes T <= 10^3, it's actually T <= 10^4

long long T, K;
long double E, P[MAXT], P2[MAXT];

long double expected(long double e1, long double a, long double b, long long q){
    return pow(a, q)*e1 + b * (1 - pow(a, q))/(1 - a);
}

int main(){
    cout.precision(20);
    cin >> T >> K; T--; K--;
    // [1 : PRECALC. PROBABILITIES]
    (T%2 ? P2 : P)[0] = 1;
    for(long long i = 1, i2 = T; i <= T; i++, i2--){
        for(long long j = 0; j <= T; j++){
            long double x = (!j) ? 0 : (i2%2 ? P2:P)[j - 1], y = (i2%2 ? P2:P)[j]; // if confusing do the math
            (i2%2 ? P:P2)[j] = (x + y) / 2;
        }
    }

    // [2 : EXPECTED VALUE]
    E = (long double)T/2; // E = expected value; starts at T/2
    for(long long f = 0; f <= T; f++) { // for floor f in range 1...T
        if(K == 0) break;
        if(f < floor(E)) continue; // skip iteration until expected value floored is <= f

        long double a = 0, b = 0;
        for(long long i = 0; i <= T; i++) if(i <= f) a += P[i]; else b += P[i]*i; // build a and b

        // binary search for q
        long long q1 = 1, q2 = 2;
        while(q1*2 <= K && expected(E, a, b, q1*2) < f + 1) q1 *= 2, q2 *= 2;
        while(q1 < q2){
            long long m = (q1 + q2) / 2;
            if(expected(E, a, b, m) < f + 1) q1 = m + 1; else q2 = m;
        }

        q1 = min(q1, K);
        E = expected(E, a, b, q1);
        K -= q1;
    }

    E += 1;
    cout << fixed << E << endl;
}
