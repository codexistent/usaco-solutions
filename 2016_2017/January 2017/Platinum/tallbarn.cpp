#include <bits/stdc++.h>
using namespace std;
#define db double
#define ll long long
#define FOR(i, a, b) for(int i = a; i <= b; i++)

ll count(const vector<ll>& A, db mred){
    ll t = 0;
    for(ll i : A) t += (ll)(sqrt(1 + 4 * i / mred) - 1) / 2 + 1;

    return t;
}

int main(){
    ifstream cin("tallbarn.in");
    ofstream cout("tallbarn.out");

    ll N, K;
    cin >> N >> K;
    vector<ll> A;
    FOR(i, 0, N - 1) {
        ll x; cin >> x;
        A.push_back(x);
    }

    db a = 0, b = 1000000000000;
    FOR(i, 1, 200){
        db min = (a + b) / 2;
        if(count(A, min) >= K){
            a = min;
        }else{
            b = min;
        }
    }

    ll T = 0;
    double R = 0;
    for(ll i : A){
        ll x = (ll)(sqrt(1 + 4 * i / a) - 1) / 2;
        T += x + 1;
        R += (db)i / (x + 1); 
    }

    cout << (ll)round(R + (T - K)*a) << endl;
}
