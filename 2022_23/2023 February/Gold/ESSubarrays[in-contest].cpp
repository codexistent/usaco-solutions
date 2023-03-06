// Mon, Feb 27th, 2023 || all test cases
#include <iostream>
#include <algorithm>
#include <set>
#include <climits>
using namespace std;
#define MAXN 505

class Pair{
    public:
        int i, j;
};

int N, M;
long long A[MAXN];
long long s[MAXN][MAXN];
Pair S[MAXN * MAXN];

bool cmpP(Pair a, Pair b){
    return s[a.i][a.j] < s[b.i][b.j];
}

long long change(int x){
    long long MIN = LONG_MAX;

    for(int i = 2; i <= M; i++){
        bool a = S[i - 1].i <= x && x <= S[i - 1].j;
        bool b = S[i].i <= x && x <= S[i].j;

        if(a != b) MIN = min(MIN, abs(s[S[i - 1].i][S[i - 1].j] - s[S[i].i][S[i].j]));
    }

    return MIN;
}

int main(){
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
        s[i][i] = A[i];
    }

    M = 1;
    for(int l = 1; l <= N; l++){
        for(int a = 1, b = a + l - 1; b <= N; a++, b++){
            Pair p;
            p.i = a;
            p.j = b;

            s[a][b] = s[a][b - 1] + A[b];
            
            S[M] = p;
            M++;
        }
    }
    M--;
    sort(S + 1, S + 1 + M, cmpP);

    for(int i = 1; i <= N; i++) cout << change(i) << "\n";
}
