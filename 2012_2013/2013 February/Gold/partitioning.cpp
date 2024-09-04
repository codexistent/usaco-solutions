#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 20
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

ll n, k, g[MAXN][MAXN];

bool valid(vector<ll>& vf, ll mxf, ll v){ 
    ll s[vf.size() + 1]; 
    
    FOR(i, 0, vf.size()) s[i] = 0; 
    FOR(i, 1, n){ 
        ll c = 0; bool rst = false; 
        FOR(j, 1, n){ 
            s[c] += g[i][j]; 
            if(s[c] > v) { 
                if(rst == true) {
                    return false; 
                }
                rst = true;
                
                j = 0, c = 0; 
                FOR(k, 0, vf.size()) s[k] = 0; 
                mxf--;
                continue; 
            }

            if(c < vf.size() && vf[c] == j) c++; 
        } 
    }

    return mxf >= 0;
}

int main(){ 
    ifstream cin("partition.in");
    ofstream cout("partition.out");

    cin >> n >> k;
    FOR(i, 1, n) FOR(j, 1, n) cin >> g[i][j];

    ll npow = pow(2, n - 1); 
    ll r = 225000;
    FOR(m, 0, npow - 1){
        vector<ll> vf; 
        FOR(i, 1, n) if(m & (1 << (i - 1))) vf.push_back(i); 
        
        if(vf.size() > k) continue;
        
        ll a = 0, b = 225000; 
        while(a < b){ 
            ll m = (a + b) / 2;

            if(valid(vf, k - vf.size(), m)){
                b = m;
            }else{
                a = m + 1;
            }
        } 
        r = min(r, a);
    }

    cout << r << endl;
}
