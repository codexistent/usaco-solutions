#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 100005
#define PRIME 53
#define MOD 1000000009
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

ll n, sh[MAXN], p[MAXN], mi;
string s;
set<ll> hls, cs;
vector<ll> hl;
vector<char> sc;

ll fpow(ll b, ll e){
    if(e == 0) return 1;
    ll r1 = fpow(b, e / 2);
    r1 = (r1 * r1) % MOD;
    if(e % 2 == 1) r1 = (r1 * b) % MOD;

    return r1;
}

int main(){
    ifstream cin("censor.in");
    ofstream cout("censor.out");

    cin >> s >> n;
    mi = fpow(PRIME, MOD - 2), p[0] = 1;
    FOR(i, 1, MAXN - 1) p[i] = (p[i - 1] * PRIME) % MOD;
    FOR(i, 1, n) {
        string si; cin >> si;

        ll h = 0;
        FOR(i, 0, si.length() - 1) h = (h + p[i] * (si[i] - 'a' + 1) % MOD) % MOD;

        cs.insert(h);
        hls.insert(si.length());
    }

    hl.push_back(0); for(ll i : hls) hl.push_back(i);
    ll m = hl.size() - 1;
    FOR(i, 1, m) sh[i] = 0;

    ll nc = 0, rmv = 0;
    for(char c : s){
        sc.push_back(c);
        nc++;
        rmv = 0;
        FOR(i, 1, m){
            if(hl[i] < nc){
                sh[i] = (sh[i] - (sc[sc.size() - 1 - hl[i]] - 'a' + 1) + MOD) % MOD;
                sh[i] = (sh[i] * mi) % MOD;
            }
            sh[i] = (sh[i] + p[min(nc, hl[i]) - 1] * (c - 'a' + 1)) % MOD;

            if(hl[i] <= nc) {
                if(cs.find(sh[i]) != cs.end() && rmv == 0){
                    rmv = hl[i];
                }
            }
        }

        if(rmv == 0) continue;
        FOR(i, 1, rmv) {
            FOR(j, 1, m) 
                if(nc - i >= hl[j]){
                    sh[j] = (sh[j] - p[hl[j] - 1] * (sc.back() - 'a' + 1) % MOD + MOD);
                    sh[j] = (sh[j] * PRIME) % MOD;
                    sh[j] = (sh[j] + (sc[sc.size() - hl[j] - 1] - 'a' + 1) % MOD) % MOD;
                }else{
                    sh[j] = (sh[j] - p[nc - i] * (sc.back() - 'a' + 1) % MOD + MOD) % MOD;
                }
            sc.pop_back();
        }
        nc -= rmv;
    }

    FOR(i, 1, sc.size()) cout << sc[i - 1];
}
