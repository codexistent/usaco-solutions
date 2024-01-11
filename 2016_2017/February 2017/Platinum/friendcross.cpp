#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef pair<int, int> pii;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> OST;
#define mp make_pair
#define MAXN 100005
#define f first
#define s second
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define ll long long

OST bit[MAXN];

void insert(int x, int y){
    for(int i = x; i < MAXN; i += i & -i) {
        bit[i].insert(mp(y, x));
        if(i == (i + (i & -i))) ;
    }
}

void remove(int x, int y){
    for(int i = x; i < MAXN; i += i & -i){
        bit[i].erase(mp(y, x));
    }
}

int query(int x, int y){
    int r = 0;
    for(int i = x; i > 0; i -= i & -i){
        r += bit[i].order_of_key(mp(y + 1, 0));
    }
    return r;
}

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
    ifstream cin("friendcross.in");
    ofstream cout("friendcross.out");

    int N, K;
    cin >> N >> K;
    pii B[N + 1], P[N + 1];
    FOR(i, 1, N) {
        cin >> B[i].f;
        P[B[i].f].f = i;
    }
    FOR(i, 1, N) {
        cin >> B[i].s;
        P[B[i].s].s = i;
    }

    ll R = 0;
    FenwickTree bit1(N + 1);
    FOR(i, 1, N) bit1.update(P[B[i].f].s, 1), R += i - bit1.sum(P[B[i].f].s);

    int l = 1, r = 0;
    FOR(b, 1, N){
        while(r < b + K && r < N) {
            r++;
            insert(P[r].f, P[r].s);
        }
        while(l < b - K) {
            remove(P[l].f, P[l].s);
            l++;
        }

        R -= query(P[b].f, MAXN - 1) - query(P[b].f, P[b].s);
    }

    cout << R << endl;
}
