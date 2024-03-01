#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)

#define f first
#define s second

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
    int n, q; cin >> n >> q;
    int a[n + 1], r[q + 1]; 
    FOR(i, 1, n) cin >> a[i];
    vector<pair<int, int>> qs[n + 1];
    FOR(i, 1, q) {
        int l, r; cin >> l >> r;
        qs[r].push_back({l, i});
    }

    FenwickTree t(n + 1);
    stack<int> st;
    FOR(i, 1, n){
        while(!st.empty() && a[st.top()] > a[i]) st.pop();
        if(!st.empty() && a[st.top()] == a[i]) {
            t.update(st.top(), 1);
            st.top() = i;
        }else st.push(i);
        for(auto qr : qs[i]) r[qr.s] = 1 + i - qr.f - (t.sum(i) - t.sum(qr.f - 1));
    }
    
    FOR(i, 1, q) cout << r[i] << endl;
}
