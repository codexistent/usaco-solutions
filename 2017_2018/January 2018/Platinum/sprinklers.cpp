#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define RFOR(i, a, b) for(ll i = a; i >= b; i--)
#define MOD 1000000007
#define maxn 100005

int n, x[maxn], y[maxn], xty[maxn];
int xmn[maxn], ymx[maxn];
ll sum1[maxn], sum2[maxn];

int main(){
    ifstream cin("sprinklers.in");
    ofstream cout("sprinklers.out");

    cin >> n;
    FOR(i, 0, n - 1) {
        cin >> x[i] >> y[i];
        xty[x[i]] = y[i];
    }

    int lo = n;
    FOR(i, 0, n - 1) while(xty[i] < lo) xmn[--lo] = i;
    while(lo) xmn[--lo] = n;

    sum1[n - 1] = sum2[n - 1] = xmn[n - 1];
    RFOR(j, n - 2, 0) sum1[j] = (sum1[j + 1] + xmn[j]) % MOD;
    RFOR(j, n - 2, 0) sum2[j] = (sum2[j + 1] + ((ll)xmn[j] * (n - j))) % MOD;
    
    ymx[n - 1] = xty[n - 1];
    RFOR(i, n - 2, 0) ymx[i] = max(ymx[i + 1], xty[i]);

    ll r = 0, ptr = n - 1;
    FOR(i, 1, n - 1){
        while(ptr > 0 && xmn[ptr - 1] <= i) ptr--;

        ll bad1 = sum2[ptr] - sum2[ymx[i]] - (n - ymx[i]) * (sum1[ptr] - sum1[ymx[i]]);
        bad1 = (bad1 % MOD + MOD) % MOD;
        ll bad2 = (ymx[i] * ptr) - (ptr * (ptr - 1) / 2) % MOD;
        bad2 = bad2 * i % MOD;
        bad1 = (bad1 + bad2) % MOD;

        ll r1 = (ymx[i] * (ll)(ymx[i] + 1) / 2) % MOD;
        r1 = (r1 * i) % MOD;
        r = r + r1 - bad1;
        r = (r % MOD + MOD) % MOD;
    }

    cout << r << '\n';
}
