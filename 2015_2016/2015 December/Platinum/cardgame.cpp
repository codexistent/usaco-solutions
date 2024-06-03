#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define MAXN 50005

int n, ec[MAXN], pfxl[MAXN], pfxr[MAXN];
set<int> bh, bl;

int main(){
    ifstream cin("cardgame.in");
    ofstream cout("cardgame.out");

    int n;
    cin >> n;
    FOR(i, 1, 2 * n) bh.insert(i), bl.insert(i);
    FOR(i, 1, n) {
        cin >> ec[i];
        bh.erase(ec[i]), bl.erase(ec[i]);
    }

    pfxl[0] = 0, pfxr[n + 1] = 0;
    FOR(i, 1, n){
        pfxl[i] = pfxl[i - 1];

        auto i2 = bh.lower_bound(ec[i]);
        if(i2 != bh.end()){
            bh.erase(i2);
            pfxl[i]++;
        }
    }

    for(int i = n; i >= 1; i--){
        pfxr[i] = pfxr[i + 1];
        auto i2 = bl.lower_bound(ec[i]);
        if(i2 != bl.begin()){
            i2--;
            bl.erase(i2);
            pfxr[i]++;
        }
    }

    int res = 0;
    FOR(i, 0, n) res = max(res, pfxl[i] + pfxr[i + 1]);

    cout << res << endl;
}
