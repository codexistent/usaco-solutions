#include <bits/stdc++.h>
using namespace std;
#define MAXN 100005
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define f first
#define s second
#define int long long

int n, tsz = 0, sz[MAXN], tn = 1, r = 0;
vector<pair<int, bool>> adj[MAXN], st;
bool del[MAXN];
int ct[2 * MAXN][2], lt[2 * MAXN][2];

void getsz(int i, int p){
    tsz++;
    sz[i] = 1;
    for(auto i2 : adj[i])  if(i2.f != p && !del[i2.f]){
        getsz(i2.f, i);
        sz[i] += sz[i2.f];
    }
}

pair<int, int> getctd(int i, int p){
    pair<int, int> ctd = {i, tsz - sz[i]};
    for(auto i2 : adj[i]) if(i2.f != p && !del[i2.f]) ctd.s = max(ctd.s, sz[i2.f]);

    for(auto i2 : adj[i]) if(i2.f != p && !del[i2.f]){
        pair<int, int> ctd2 = getctd(i2.f, i);
        if(ctd2.s < ctd.s) swap(ctd, ctd2);
    }
    return ctd;
}

void paths(unordered_multiset<int> &pfx, int i, int p, int sm){
    st.push_back({sm, pfx.find(sm) != pfx.end()});
    pfx.insert(sm);

    for(auto i2 : adj[i]) if(i2.f != p && !del[i2.f]){
        paths(pfx, i2.f, i, sm + ((i2.s == 0) ? -1 : 1));
    }

    pfx.erase(pfx.find(sm));
}

void dfs(int rt){
    tn++;
    tsz = 0, getsz(rt, -1);
    int ctd = getctd(rt, -1).f;
    del[ctd] = true;

    int tnmn = tn;
    for(auto i2 : adj[ctd]) if(!del[i2.f]) {
        tn++, st.clear();
        unordered_multiset<int> pfx;
        paths(pfx, i2.f, ctd, (i2.s == 0) ? -1 : 1);

        for(auto sti : st){
            int sm = sti.f;
            int og = r;

            if(sm == 0 && sti.s) r++;
            r += (tnmn <= lt[-sm + n][1]) * ct[-sm + n][1];
            if(sti.s || sm == 0) r += (tnmn <= lt[-sm + n][0]) * ct[-sm + n][0];
        }

        for(auto sti : st){
            if(lt[sti.f + n][sti.s] < tnmn){
                lt[sti.f + n][sti.s] = tn;
                ct[sti.f + n][sti.s] = 0;
            }
            ct[sti.f + n][sti.s]++;
        }
    }

    for(auto i2 : adj[ctd]) if(!del[i2.f]) {
        dfs(i2.f);
    }
}

main(){
    ifstream cin("yinyang.in");
    ofstream cout("yinyang.out");

    cin >> n;
    FOR(i, 1, n - 1){
        int a, b; bool t;
        cin >> a >> b >> t;
        adj[a].push_back({b, t}), adj[b].push_back({a, t});
    }
    FOR(i, 1, n) del[i] = false;
    FOR(i, 0, MAXN * 2 - 1) lt[i][0] = lt[i][1] = 0;

    dfs(1);

    cout << r << endl;
}
