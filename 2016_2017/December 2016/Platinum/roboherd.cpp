#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define pb push_back
#define ll long long
#define MAXN 100005

ll N, M, ct, F[MAXN], R = 0, T, N2 = 0;
vector<ll> D[MAXN];

void go(ll x, ll kmx){
    if(ct >= M) return;
    if(x != -1 && kmx < D[x][0]) x = upper_bound(F, F + x, kmx) - F - 1;

    if(x == -1) {
        T += kmx + 1;
        ct++;
        return;
    }

    go(x - 1, kmx);
    for(ll i = 0; i < D[x].size() && D[x][i] <= kmx; i++) go(x - 1, kmx - D[x][i]);
}

int main(){
    ifstream cin ("roboherd.in");
    ofstream cout ("roboherd.out");

    ll a = 0, b = 0;
    cin >> N >> M;
    FOR(i, 0, N - 1){
        ll O;
        cin >> O;
        vector<ll> v;
        FOR(i, 1, O) {
            ll x;
            cin >> x;
            v.pb(x);
        }
        sort(begin(v), end(v));
        R += v[0];
        if(O == 1) continue;

        FOR(j, 1, O - 1) D[N2].pb(v[j] - v[0]);
        b += D[N2].back(); 

        N2++;
    }

    swap(N, N2);
    sort(D, D + N);
    FOR(i, 0, N - 1) {
        F[i] = D[i][0]; 
    }

    while(a < b){
        ll m = (a + b) / 2;
        ct = 0;
        go(N - 1, m);

        if(ct < M) {
            a = m + 1;
        }else{
            b = m;
        }
    }

    ct = T = 0;
    if(a > 0) go(N - 1, a - 1);
    R = (R + a) * M, R -= T;

    cout << R << endl;
}
