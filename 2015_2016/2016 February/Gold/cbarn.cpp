#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define ll long long

int main(){
    ifstream cin("cbarn.in");
    ofstream cout("cbarn.out");

    int n;
    cin >> n;
    vector<int> c(n);
    FOR(i, 0, n - 1) cin >> c[i];

    int cc = 0, m = INT_MAX, s = 0;
    FOR(i, 0, n - 1){
        cc += c[i] - 1;
        if(m > cc) m = cc, s = (i + 1) % n;
    }

    rotate(c.begin(), c.begin() + s, c.begin() + n);

    ll R = 0;
    queue<int> q;
    FOR(i, 0, n - 1){
        if(c[i]) FOR(j, 1, c[i]) q.push(i);
        R += (i - q.front()) * (i - q.front());
        q.pop();
    }

    cout << R << endl;
}
