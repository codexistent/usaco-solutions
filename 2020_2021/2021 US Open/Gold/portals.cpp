#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 100005
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define f first
#define s second

ll n, p[MAXN * 2], sz[MAXN * 2], r = 0;
priority_queue<pair<ll, pair<ll, ll>>> pq;

ll find(ll x) { return (p[x] == x) ? x : (p[x] = find(p[x])); }
bool onion(ll a, ll b){
    a = find(a), b = find(b);
    if(a == b) return false;

    if(sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    p[a] = p[b] = a;
    return true;
}

int main(){
    cin >> n;
    FOR(i, 1, 2 * n) p[i] = i, sz[i] = 1;
    FOR(i, 1, n){
        ll c; cin >> c;
        ll a, b, a2, b2; cin >> a >> b >> a2 >> b2;
        pq.push({0, {a, b}}), pq.push({0, {a2, b2}});
        pq.push({-c, {a, a2}});
    }

    while(pq.size()){
        auto pqi = pq.top(); pq.pop();
        r -= onion(pqi.s.f, pqi.s.s) * pqi.f;
    }

    cout << r << endl;
}
