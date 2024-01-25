// inspo : https://github.com/dolphingarlic/CompetitiveProgramming/blob/736d1084561c1d4235d8d5e5ae203dce6e0089ac/USACO/USACO%2018-itout.cpp#L4
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 100005
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define RFOR(i, a, b) for(int i = a; i >= b; i--)

ll n, k, a[MAXN], n2 = 0;
ll len[MAXN], lis[MAXN], bit[MAXN], dp[MAXN];
vector<int> has_len[MAXN];

void update(ll i, ll ln, ll v){
    for(; i <= n; i += i & (-i)){
        if(len[i] == ln) bit[i] = min(k + 1, bit[i] + v);
        else if(len[i] < ln) bit[i] = v, len[i] = ln;
    }
}
pair<ll, ll> query(ll i){
    pair<ll, ll> r;
    for(; i; i -= i & (-i)){
        if(len[i] == r.first) r.second = min(k + 1, r.second + bit[i]);
        else if(len[i] > r.first) r = {len[i], bit[i]}; 
    }
    return r;
}

int main() {
    ifstream cin ("itout.in");
    ofstream cout ("itout.out");

    cin >> n >> k;
    FOR(i, 1, n) cin >> a[i];
    RFOR(i, n, 1) {
        tie(lis[i], dp[i]) = query(n + 1 - a[i]);
        if(lis[i] == 0) dp[i]++;
        has_len[++lis[i]].push_back(i);
        n2 = max(n2, lis[i]);
        update(n + 1 - a[i], lis[i], dp[i]);
    }

    set<int> s;
    FOR(i, 1, n) s.insert(i);

    cout << n - n2 << '\n';
    ll prv = 0;
    RFOR(i, n2, 1) {
        sort(begin(has_len[i]), end(has_len[i]), [](ll x, ll y){return a[x] > a[y]; } ); // make indicies decreasing
        for(ll j : has_len[i]) if(j >= prv) {
            if(dp[j] >= k){
                s.erase(a[j]);
                prv = j;
                break;
            } else k -= dp[j];
        } 
    }

    for(int i : s) cout << i << '\n';
}
