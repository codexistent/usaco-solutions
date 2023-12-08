#include <bits/stdc++.h>
using namespace std;

struct RangeFenwick {
    vector<int> bit[2];
    int size;

    RangeFenwick(int n){
        size = n + 1;
        bit[0].assign(size + 1, 0), bit[1].assign(size + 1, 0);
    }
    
    void add(bool t, int i, int x){
        for(; i < size; i += i & -i) bit[t][i] += x;
    }

    void range_add(int l, int r, int x){
        add(0, l, x), add(0, r + 1, -x);
        add(1, l, x * (l - 1)), add(1, r + 1, -x * r);
    }

    int sum_helper(int t, int i){
        int r = 0;
        for(; i > 0; i -= i & -i) r += bit[t][i];

        return r;
    }

    int sum(int i){
        return sum_helper(0, i)*i - sum_helper(1, i);
    }
};

int main() {
  
}
