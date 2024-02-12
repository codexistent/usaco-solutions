#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

bool ccw(pair<ll, ll> i, pair<ll, ll> j, pair<ll, ll> k){
    long long cross = ((ll)i.first - (ll)j.first)*((ll)k.second - (ll)j.second) - (ll)(k.first - j.first)*(ll)(i.second - j.second);
    return (cross < 0);
}

int main(){
    ifstream cin ("balance.in");
    ofstream cout ("balance.out");

    ll n; cin >> n;
    ll f[n + 2];
    f[0] = f[n + 1] = 0;
    FOR(i, 1, n) cin >> f[i];

    vector<pair<ll, ll>> ch; ch.push_back({0, 0});
    FOR(i, 1, n + 1){
        while(ch.size() >= 2 && ccw(ch[ch.size() - 2], ch[ch.size() - 1], {i, f[i]})) ch.pop_back();
        ch.push_back({i, f[i]});
    }

    pair<ll, ll> p1 = {0, 0}, p2 = ch[1];
    ll chi = 1;
    FOR(i, 1, n){
        ll r = 100000LL * (ll)(p1.second * (p2.first - p1.first) + (i - p1.first) * (ll)(p2.second - p1.second)) /  (p2.first - p1.first);
        cout << r << endl;

        if(i == p2.first && chi + 1 < ch.size()){
            swap(p1, p2), p2 = ch[++chi];
        }
    }
}
