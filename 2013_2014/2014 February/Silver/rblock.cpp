#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define MAXN 255
#define f first
#define s second

ll n, m, d[MAXN], d1, d2;
pair<ll, ll> pe[MAXN];
vector<pair<pair<ll, ll>, ll> > e[MAXN];

int main(){
    ifstream cin ("rblock.in");
    ofstream cout ("rblock.out");

    cin >> n >> m;
    FOR(i, 1, m){
        ll a, b, w; cin >> a >> b >> w;
        e[a].push_back({{b, w}, i});
        e[b].push_back({{a, w}, i});
    }

    priority_queue<pair<ll, ll>> pq;
    FOR(i, 1, n) d[i] = -1, pe[i] = {-1, -1}; d[1] = 0;
    pq.push({0, 1});
    while(pq.size()){
        auto i = pq.top(); pq.pop();
        if(d[i.s] != i.f) continue;

        for(auto ei : e[i.s]){
            ll i2 = ei.f.f;
            if(d[i2] == -1 || d[i2] > d[i.s] + ei.f.s){
                d[i2] = d[i.s] + ei.f.s, pe[i2] = {ei.s, i.s};
                pq.push({d[i2], i2});
            }
        }
    }
    d1 = d2 = d[n];

    vector<ll> eid;
    ll c = n;
    while(pe[c].first != -1){
        eid.push_back(pe[c].f);
        c = pe[c].s;
    }

    for(ll di : eid){
        FOR(i, 1, n) d[i] = -1; d[1] = 0;
        pq.push({0, 1});
        while(pq.size()){
            auto i = pq.top(); pq.pop();
            if(d[i.s] != i.f) continue;

            for(auto ei : e[i.s]){
                ll i2 = ei.f.f;
                if(d[i2] == -1 || d[i2] > d[i.s] + ei.f.s * (1 + (ei.s == di))){
                    d[i2] = d[i.s] + ei.f.s * (1 + (ei.s == di));
                    pq.push({d[i2], i2});
                }
            }
        }

        d2 = max(d2, d[n]);
    }

    cout << d2 - d1 << endl;
}
