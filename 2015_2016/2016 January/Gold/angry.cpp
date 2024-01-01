#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define RFOR(i, a, b) for(int i = a; i >= b; i--)
#define MAXN 50005

int N, X[MAXN];
int PFX[MAXN], SFX[MAXN];

bool valid(int r){
    int p2 = 0;
    bool R = false;
    FOR(p1, 0, N - 1){
        while(p2 + 1 <= N - 1 && X[p2 + 1] - X[p1] <= r) p2++;
        R |= PFX[p1] * 2 <= max(0, r - 2) && SFX[p2] * 2 <= max(0, r - 2);
    }

    return R;
}

int main(){
    ifstream cin ("angry.in");
    ofstream cout ("angry.out");

    cin >> N;
    FOR(i, 0, N - 1) cin >> X[i];
    sort(X, X + N);

    PFX[0] = 0;
    int ppow = 0, lpos = 0;
    FOR(i, 1, N - 1) {
        if(X[i] - X[i - 1] > PFX[i - 1]){
            PFX[i] = X[i] - X[i - 1];
            ppow = PFX[i];
            lpos = i;
        }else{
            if(X[i] - X[lpos] > ppow + 1){
                ppow = PFX[i - 1];
                lpos = i - 1;
            }
            PFX[i] = ppow + 1;
        }
    }
    SFX[N - 1] = 0, ppow = 0, lpos = N - 1;
    RFOR(i, N - 2, 0) {
        if(X[i + 1] - X[i] > SFX[i + 1]){
            SFX[i] = X[i + 1] - X[i];
            ppow = SFX[i];
            lpos = i;
        }else{
            if(X[lpos] - X[i] > ppow + 1){
                ppow = SFX[i + 1];
                lpos = i + 1;
            }
            SFX[i] = ppow + 1;
        }
    }

    int a = 0, b = 2000000000;
    while(a < b){
        int m = (a + b) / 2;
        if(valid(m)){
            b = m;
        }else{
            a = m + 1;
        }
    }

    cout << fixed << setprecision(1) << (double)a / 2 << endl;
}
