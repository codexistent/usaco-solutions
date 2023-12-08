#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)

struct FenwickTree2D { // 1-based indexed 2D BIT/Fenwick Tree
    vector<vector<int> > bit;
    pair<int, int> size;

    FenwickTree2D(int d1, int d2){
        size = make_pair(d1 + 1, d2 + 1);
        bit.assign(size.first + 1, vector<int>(size.second + 1));
        FOR(i, 0, d1) FOR(j, 0, d2) bit[i][j] = 0;
    }
    FenwickTree2D(const vector<vector<int> > &a, int d1, int d2) : FenwickTree2D(d1, d2){
        FOR(i, 1, d1) FOR(j, 1, d2) update(make_pair(i, j), a[i - 1][j - 1]);
    }

    int sum(pair<int, int> i, pair<int, int> j){
        return sum(i) 
                - sum(make_pair(i.first, j.second - 1)) 
                - sum(make_pair(j.first - 1, i.second)) 
            + sum(make_pair(j.first - 1, j.second - 1));
    }
    int sum(pair<int, int> i){
        int r = 0;
        int x = i.first, y = i.second;
        for(; x > 0; x -= x & -x){
            for(y = i.second; y > 0; y -= y & -y){
                r += bit[x][y];
            }
        }

        return r;
    }

    void update(pair<int, int> i, int v){
        int x = i.first, y = i.second;
        for(; x < size.first; x += x & -x) {
            for(y = i.second; y < size.second; y += y & -y){
                bit[x][y] += v;
            }
        }
    }
};

int main(){
}
