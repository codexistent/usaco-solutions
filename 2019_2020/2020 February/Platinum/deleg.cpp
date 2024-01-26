#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)

int n, k;
vector<vector<int>> adj;

bool valid2(const vector<int>& l, int m){
    int a = 0, b = l.size() - 1;
    while(a < b){
        if(a == m) a++;
        if(b == m) b--;
        if(l[a] + l[b] < k) return false;

        a++, b--;
    }
    return true;
}

int valid(int v, int p){
    vector<int> l;
    for(int v2 : adj[v]) if(v2 != p) {
        int r = valid(v2, v);
        if(r == -1) return -1;
        l.push_back(r + 1);
    }
    sort(begin(l), end(l));

    auto l2 = l; if(l.size() & 1) l2.insert(l2.begin(), 0);
    bool al = valid2(l2, -1);

    if(!(l.size() & 1)) l.insert(begin(l), 0);
    int a = -1, b = l.size() - 1;
    while(a < b){
        int m = (a + b + 1) / 2;
        if(valid2(l, m)){
            a = m;
        }else{
            b = m - 1;
        }
    }

    
    if(v == 0 && !al) return -1;
    if(a >= 0) return l[a];
    if(al) return 0;
    return -1;
}

int main(){
    ifstream cin ("deleg.in");
    ofstream cout ("deleg.out");

    cin >> n;
    adj.resize(n);
    FOR(i, 1, n - 1) {
        int a, b; cin >> a >> b; a--, b--;
        adj[a].push_back(b), adj[b].push_back(a);
    }

    int a = 1, b = n;
    while(a < b){
        k = (a + b + 1) / 2;
        int r = valid(0, -1);
        if(r != -1){
            a = k;
        }else{
            b = k - 1;
        }
    }
    cout << a << endl;
}
