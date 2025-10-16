#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define FOR(ict, ist, ied) for(ll ict = ist; ict <= ied; ict++)
const ll MOD = 1e9 + 7;
const ll MAXA = 1e7 + 1;

vector<ll> fac(MAXA);

ll fpow(ll b, ll e){ 
  if(e == 0) return 1; 
  ll e2 = fpow(b, e/2); 
  return e2 * e2 % MOD * ((e % 2) ? b : 1) % MOD;
}

ll inv(ll x){ return fpow(x, MOD - 2); }

ll choose(ll n, ll k){ 
  // n!/((n - k)!k!) 
  return fac[n] * inv(fac[n - k] * fac[k] % MOD) % MOD;
}

ll group(ll x, ll y){ 
  // x elements, y groups 
  // x elements + y - 1 dividers = (x + y - 1) choose (y - 1) 
  return choose(x + y - 1, y - 1);
}

int main(){ 
  ll n; cin >> n; 
  fac[0] = 1; 
  FOR(i, 1, MAXA - 1) fac[i] = fac[i - 1] * i % MOD; 

  ll r = 1ll, prv = 1; 
  FOR(i, 1, n){ 
    ll x; cin >> x; x /= 2; 
    // to minimize direction changes, spread as evenly as possible 

    // if(x <= prv), do one for each 
    if(x <= prv) { 
      r = (r * choose(prv, x)) % MOD; 
    }else if(prv < x){ 
      ll x2 = x - prv; 
      r = (r * group(x2, prv)) % MOD; 
    } 
    prv = x; 
  } 
  cout << r << endl;
}
