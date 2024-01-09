#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define ll long long

struct FenwickTree {
    vector<int> bit; // the tree
    int size;

    FenwickTree(int n){
        size = n + 1;
        bit.assign(size + 1, 0);
    }
    FenwickTree(const vector<int> &a) : FenwickTree(a.size()){
        FOR(i, 1, a.size()){
            update(i, a[i - 1]);
        }
    }

    int sum(int i){
        int r = 0;
        for(; i > 0; i -= i & -i) r += bit[i];

        return r;
    }

    void update(int i, int x){
        for(; i < size; i += i & -i) bit[i] += x;
    }
};

int main(){
    ifstream cin("mincross.in");
    ofstream cout("mincross.out");

    int N;
    cin >> N;
    int B[N + 1], P[N + 1];
    FOR(i, 1, N) cin >> B[i];
    FOR(i, 1, N){
        int x; cin >> x;
        P[x] = i;
    }

    ll r1 = 0;
    FenwickTree FT(N + 1);
    FOR(i, 1, N){
        r1 += i - 1 - FT.sum(P[B[i]]);
        FT.update(P[B[i]], 1);
    }

    ll R = r1, r = r1;
    FOR(i, 1, N) R = min(R, r += ((N - P[B[i]]) - (P[B[i]] - 1))); 
    r = r1;
    int B2[N + 1], P2[N + 1];
    FOR(i, 1, N) B2[P[i]] = P2[B[i]] = i;
    FOR(i, 1, N) R = min(R, r += ((N - P2[B2[i]]) - (P2[B2[i]] - 1))); 

    cout << R << endl;
}
