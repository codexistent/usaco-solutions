#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 200005
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define f first
#define s second

ll n, l, r[MAXN];
pair<ll, ll> p[MAXN], j[MAXN][20];
vector<pair<ll, ll>> c[MAXN];

void jdfs(int i = 1, ll d = 0){
    for(ll jsz = 2, idx = 1; jsz <= d; jsz *= 2, idx++){
        j[i][idx] = {j[j[i][idx - 1].f][idx - 1].f, j[i][idx - 1].s + j[j[i][idx - 1].f][idx - 1].s};
    }
    
    for(auto i2 : c[i]) jdfs(i2.f, d + 1);
}

pair<ll, ll> jump(int i, ll jsz){
    ll ri = i, rsz = 0;
    FOR(ji, 0, 19) if(jsz & (1 << ji)) {
        rsz += j[ri][ji].s;
        ri = j[ri][ji].f;
    }
    return {ri, rsz};
}

void dfs(int i = 1, ll d = 0){
    ll da = 0, db = d;
    while(da != db){
        ll m = (da + db + 1) / 2;
        if(jump(i, m).s <= l){
            da = m;
        }else{
            db = m - 1;
        }
    }
    if(da != 0){
        pair<ll, ll> di = jump(i, da);
        r[p[i].f]++, r[p[di.f].f]--;
    }
    
    for(auto i2 : c[i]){
        dfs(i2.f, d + 1);
        r[i] += r[i2.f];
    }
}

int main(){
    ifstream cin("runaway.in");
    ofstream cout("runaway.out");

    cin >> n >> l;
    FOR(i, 2, n){
        cin >> p[i].f >> p[i].s;
        c[p[i].f].push_back({i, p[i].s});
    }

    FOR(i, 1, n) j[i][0] = p[i];
    jdfs();

    FOR(i, 1, n) r[i] = 0;
    p[1] = {0, 0}, dfs();

    FOR(i, 1, n) cout << (r[i] + 1) << endl;
}
