#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)

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

    int pfx(int i){
        int r = 0;
        for(; i > 0; i -= i & -i) r = max(r, bit[i]);

        return r;
    }

    void update(int i, int x){
        for(; i < size; i += i & -i) bit[i] = max(bit[i], x);
    }
};

int main() {
    ifstream cin("nocross.in");
    ofstream cout("nocross.out");

    int N;
    cin >> N;
    int B1[N + 1], P2[N + 1];
    FOR(i, 1, N) cin >> B1[i];
    FOR(i, 1, N) {
        int x; cin >> x;
        P2[x] = i;
    }

    FenwickTree FT(N);
    FOR(i, 1, N){
        stack<pair<int, int>> upd;
        FOR(j, max(B1[i] - 4, 1), min(B1[i] + 4, N)) upd.push(make_pair(P2[j], FT.pfx(P2[j] - 1) + 1));
        while(!upd.empty()) FT.update(upd.top().first, upd.top().second), upd.pop();
    }

    cout << FT.pfx(N);
}
