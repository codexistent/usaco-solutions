#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define PRM 211
#define MOD 1000000007
#define ll long long

int N;
vector<pair<ll, ll>> B;

ll prev(int i) { return (i == 0) ? (N - 1) : i - 1; }
ll next(int i) { return (i + 1) % N; }
ll dist(int a, int b) {
    auto i = B[a], j = B[b];
    return abs(i.first - j.first) + abs(i.second - j.second);
}
ll cw_c_ccw(int a, int b, int c){
    if(b == 0) return 3; 
    auto i = B[a], j = B[b], k = B[c];
    long long cross = (i.first - j.first)*(k.second - j.second) - (k.first - j.first)*(i.second - j.second);
    return (cross > 0) ? 1 : 2;
}


int main(){
    ifstream cin ("lightsout.in");
    ofstream cout ("lightsout.out");

    cin >> N;
    B.resize(N);
    FOR(i, 0, N - 1) {
        int x, y;
        cin >> x >> y;
        B[i] = make_pair(x, y);
    }

    ll P[2*N + 1];
    P[0] = 1; FOR(i, 1, 2*N) P[i] = (P[i - 1] * PRM) % MOD;
    
    map<ll, ll> ID;
    FOR(i, 0, N - 1) if(ID.find(dist(i, next(i))) == ID.end()) ID.insert(make_pair(dist(i, next(i)), ID.size() + 1));

    unordered_set<ll> h1, mult;
    FOR(i, 0, N - 1){
        ll hash = cw_c_ccw(prev(i), i, next(i));
        if(h1.find(hash) == h1.end()) h1.insert(hash); else mult.insert(hash); 
        FOR(s, 1, N){
            hash = (hash + ID[dist(prev((i + s) % N), (i + s) % N)] * P[s * 2 - 1] % MOD) % MOD;
            hash = (hash + cw_c_ccw(prev((i + s) % N), (i + s) % N, next((i + s) % N)) * P[s * 2] % MOD) % MOD;

            if(h1.find(hash) == h1.end()) h1.insert(hash); else mult.insert(hash); 
        }
    }

    ll CW[N][N];
    FOR(i, 0, N - 1){
        CW[i][i] = 0;
        for(int j = next(i); j != i; j = next(j)){
            CW[i][j] = (CW[i][prev(j)] + dist(prev(j), j));
        }
    }
    ll CCW[N][N];
    FOR(i, 0, N - 1){
        CCW[i][i] = 0;
        for(int j = prev(i); j != i; j = prev(j)){
            CCW[i][j] = CCW[i][next(j)] + dist(next(j), j);
        }
    }

    ll R = 0;
    FOR(i, 0, N - 1){
        int s = 0;
        ll hash = cw_c_ccw(prev(i), i, next(i));
        if(mult.find(hash) == mult.end()) goto updateR;
        for(s = 1; s <= N; s++){
            hash = (hash + ID[dist(prev((i + s) % N), (i + s) % N)] * P[s * 2 - 1] % MOD) % MOD;
            hash = (hash + cw_c_ccw(prev((i + s) % N), (i + s) % N, next((i + s) % N)) * P[s * 2] % MOD) % MOD;

            if(mult.find(hash) == mult.end() || (i + s) % N == 0) break;
        }

        updateR:;
        R = max(R, CW[i][(i + s) % N] + min(CW[(i + s) % N][0], CCW[(i + s) % N][0]) - min(CW[i][0], CCW[i][0]));
    }

    cout << R << endl;
}
