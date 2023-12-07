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

    int sum(int i){
        int r = 0;
        for(; i > 0; i -= i & -i) r += bit[i];

        return r;
    }

    void update(int i, int x){
        for(; i < size; i += i & -i) bit[i] += x;
    }
};

int main() {
  
}
