#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXK 11
#define MAXN 50005
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

string s[MAXK];
ll k, n, r = 0, st[MAXK][MAXN * 4], pfx[MAXK][MAXN];
map<vector<ll>, vector<ll>> mp;

void update(ll sti, ll i, ll l, ll r, pair<ll, ll> upd){
    if(upd.first < l || r < upd.first) return;

    if(l == r){
        st[sti][i] = upd.second;
        return;
    }
    update(sti, i * 2, l, (l + r) / 2, upd);
    update(sti, i * 2 + 1, (l + r) / 2 + 1, r, upd);
    st[sti][i] = min(st[sti][i * 2], st[sti][i * 2 + 1]);
}

ll query(ll sti, ll i, ll l, ll r, pair<ll, ll> qry){
    if(qry.second < l || r < qry.first) return LLONG_MAX;

    if(qry.first <= l && r <= qry.second) return st[sti][i];

    return min(query(sti, i * 2, l, (l + r) / 2, qry), query(sti, i * 2 + 1, (l + r) / 2 + 1, r, qry)); 
}

int main(){
    ifstream cin("cbs.in");
    ofstream cout("cbs.out");

    cin >> k >> n;
    FOR(i, 1, k) {
        cin >> s[i];
        pfx[i][0] = 0;
        update(i, 1, 0, n, {0, 0});
    }
    if(true){
        vector<ll> v, v2;
        FOR(i, 1, k) v.push_back(0);
        v2.push_back(0);
        mp.insert({v, v2});
    }

    FOR(i, 1, n){
        ll rngf = -1;
        vector<ll> v;
        FOR(ki, 1, k){
            if(s[ki][i - 1] == '('){
                pfx[ki][i] = pfx[ki][i - 1] + 1;
            }else{
                pfx[ki][i] = pfx[ki][i - 1] - 1;
            }

            update(ki, 1, 0, n, {i, pfx[ki][i]});
            v.push_back(pfx[ki][i]);

            ll lo = 0, hi = i;
            while(lo < hi){
                ll md = (lo + hi) / 2;
                if(query(ki, 1, 0, n, {md, i}) >= pfx[ki][i]){
                    hi = md;
                }else{
                    lo = md + 1;
                }
            }

            if(rngf == -1){
                rngf = lo;
            }else{
                rngf = max(rngf, lo);
            }
        }

        if(mp.find(v) != mp.end() && rngf <= mp[v][mp[v].size() - 1]){
            ll lo = 0, hi = mp[v].size() - 1;
            while(lo < hi){
                ll md = (lo + hi) / 2;
                if(rngf <= mp[v][md]){
                    hi = md;
                }else{
                    lo = md + 1;
                }
            }

            r += mp[v].size() - 1 - lo + 1;
        }

        if(mp.find(v) == mp.end()){
            vector<ll> v2;
            v2.push_back(i);

            mp.insert({v, v2});
        }else{
            mp[v].push_back(i);
        }
    }

    cout << r << endl;
}
