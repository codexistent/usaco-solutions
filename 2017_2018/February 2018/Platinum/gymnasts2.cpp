#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define ll long long
#define MOD 1000000007
ll fastpow(ll b, ll e){
    if(e == 0) return 1;
    return (((e % 2) ? b : 1) * (fastpow(b, e / 2)) % MOD * (fastpow(b, e / 2)) % MOD) % MOD;
}

ll N, r = 0;
vector<ll> p;
map<ll, int> e;

void go(int pi = 0, ll d = 1, ll a = 1, ll b = 1){
    if(pi == p.size()){
        if(d != 1) r = (r + fastpow(2, N / d) * (a * b % MOD)) % MOD;
    }else{
        go(pi + 1, d, a, b);
        ll ma = 1;
        FOR(i, 1, e[p[pi]]) go(pi + 1, d * ma * p[pi], a * ma, b * (p[pi] - 1)), ma *= p[pi];
    }
}

int main() {
    ifstream cin ("gymnasts.in");
    ofstream cout ("gymnasts.out");

    cin >> N;
    ll n = N;
    for(ll i = 2; i * i <= N; i++) 
        if(n % i == 0) {
            e.insert(make_pair(i, 0));
            while(n % i == 0) e[i]++, n /= i;
            p.push_back(i);
        }
    if(n > 1) p.push_back(n), e.insert(make_pair(n, 1));

	go();
    r = (r + MOD + 2 - N % MOD) % MOD;
    cout << r << endl;
}
