// just another implementation, but on a different date, of USACO February Gold - Cow Camp

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(ict, ist, ied) for(int ict = ist; ict <= ied; ict++)

long double ch[1005];

long double fpow(long double b, ll e){
    if(e == 0) return 1.0;
    long double e2 = fpow(b, e / 2);
    return e2 * e2 * ((e % 2) ? b : 1.0);
}

int main(){
    ll t, k; cin >> t >> k;
    ch[0] = 1; FOR(i, 1, t - 1) ch[i] = ch[i - 1] * (t - 1 - (i - 1)) / i;

    ll ki = 0;
    long double dp = 0;
    while(ki < k){

        long double a = 0;
        FOR(i, floor(dp) + 1, t - 1) a += i * ch[i];

        long double b = 0;
        FOR(i, 0, floor(dp)) b += ch[i];

        FOR(i, 1, t - 1) a /= 2.0, b /= 2.0;

        ll lo = ki + 1, hi = k;
        while(lo < hi){
            ll md = (lo + hi) / 2;

            long double bp = fpow(b, md - ki);
            if(bp == 1.0){
                return 0;
            }
            if(md == k || floor(a * (1 - bp) / (1 - b) + dp * bp) > floor(dp)){
                hi = md;
            }else{
                lo = md + 1;
            }
        }
        
        long double bp = fpow(b, lo - ki);
        if(bp == 1.0){
            return 0;
        }
        dp = a * (1 - bp) / (1 - b) + dp * bp;
        ki = lo;
    }

    cout << fixed << setprecision(20) << (1.0 + dp) << endl;
}
