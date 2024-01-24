#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair
#define f first
#define s second

int main (){
    ifstream cin ("fencedin.in");
    ofstream cout ("fencedin.out");

    int mx[2], dim[2];
    cin >> mx[0] >> mx[1] >> dim[0] >> dim[1];
    int f[2][max(dim[0], dim[1]) + 2];
    FOR(d, 0, 1) {
        FOR(i, 1, dim[d]) cin >> f[d][i];
        f[d][0] = 0, f[d][dim[d] + 1] = mx[d];
        sort(f[d], f[d] + dim[d] + 2);
    }

    priority_queue<pair<int, bool>, vector<pair<int, bool>>, greater<pair<int, bool>>> pq;
    FOR(d, 0, 1) FOR(i, 1, dim[d] + 1) {
        pq.push(mp(f[d][i] - f[d][i - 1], d));
    }

    long long s = 0;
    int r = (dim[0] + 1) * (dim[1]  + 1) - 1, rem[2] = {0, 0};
    int ct = 0;
    while(r > 0){
        int d = pq.top().s;
        long long rs = min((rem[d] && rem[!d]) ? (dim[!d] + 1 - rem[!d]) : dim[!d], r);
        r -= rs, s += rs * pq.top().f, rem[d]++;
        pq.pop();
    }

    cout << s << endl;
}
