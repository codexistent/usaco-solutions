// inspo: https://codeforces.com/blog/entry/52094
// problems: http://www.usaco.org/index.php?page=viewproblem2&cpid=722
//           https://codeforces.com/contest/785/problem/E
//           https://www.codechef.com/problems/DISTNUM

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef pair<int, int> pii;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> OST;
#define mp make_pair
#define MAXN 200005

OST bit[MAXN];

void insert(int x, int y){
    for(int i = x; i < MAXN; i += i & -i) {
        bit[i].insert(mp(y, x));
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

int main(){
    
}
