// inspo: https://github.com/walnutwaldo/Programming_Contests/blob/cd83bdb117d82b0eeb89701ed4ea719fe80313a8/USACO/2019-2020%20Season/US%20Open/Platinum/exercise.cpp#L4
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
#define FOR(i, a, b) for(int i = a; i <= b; i++)

int n;
ull m;
vector<ull> fact;
vector<bool> comp;

ull mml (ull a, ull b) { return (a * b) % m; }
ull mpow (ull b, ull e) { return e ? ((e & 1) ? mml(b, mpow(b, e - 1)) : mpow(mml(b, b), e >> 1)) : 1; }

ull without(ull z){
    ull r = 1;
    FOR(i, 1, n) if(i % z) r = r * i % (m - 1); else r = r * (i - 1) % (m - 1);
    return r;
}
ull with(ull z){
    return (fact[n] - without(z) + (m - 1)) % (m - 1);
}

int main() {
    ifstream cin("exercise.in");
    ofstream cout("exercise.out");

    cin >> n >> m;
    fact.assign(n + 1, 0), comp.assign(n + 1, false);
    fact[0] = 1;
    FOR(i, 1, n) fact[i] = fact[i - 1] * i % (m - 1);

    ull r = 1;
    FOR(i, 2, n) if(!comp[i]){
        for(int j = i * 2; j <= n; j += i) comp[j] = true;
        for(int j = i; j <= n; j *= i) r = mml(r, mpow(i, with(j)));
    }

    cout << r << endl;
}
