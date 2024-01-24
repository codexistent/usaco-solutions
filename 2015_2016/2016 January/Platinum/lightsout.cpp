// inspo: (usaco official analysis) http://www.usaco.org/current/data/sol_lightsout_platinum_jan16.html
#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define RFOR(i, a, b) for(int i = a; i >= b; i--)
#define MAXN 455
#define INF 20000005

int dist[MAXN], pfx[MAXN], orig[MAXN*2][MAXN*2];
vector<int> gol[MAXN][MAXN], gor[MAXN][MAXN];

int cw_c_ccw(pair<int, int> i, pair<int, int> j, pair<int, int> k){
    long long cross = (i.first - j.first)*(k.second - j.second) - (k.first - j.first)*(i.second - j.second);
    return (cross > 0) ? -1 : -2;
}

int main(){
    ifstream cin ("lightsout.in");
    ofstream cout ("lightsout.out");

    int n; cin >> n;
    vector<pair<int, int>> p(n); FOR(i, 0, n - 1) cin >> p[i].first >> p[i].second;
    vector<int> m(1, 0);

    FOR(i, 0, n - 1){
        int j = (i + 1) % n, k = (i + 2) % n;
        m.push_back(abs(p[i].first - p[j].first) + abs(p[i].second - p[j].second));
        m.push_back(cw_c_ccw(p[i], p[j], p[k]));        
    }
    m.back() = 0;

    FOR(i, 0, n - 1) pfx[i + 1] = dist[i + 1] = dist[i] + m[2 * i + 1];
    dist[n] = 0;
    RFOR(i, n - 1, 0) dist[i] = min(dist[i], dist[i + 1] + m[2 * i + 1]);

    FOR(l, 1, m.size()) FOR(i, 0, m.size() - l) {
        for(int& j = orig[i][l]; j < i; j++){
            if(orig[j][l - 1] == orig[i][l - 1] && m[j + l - 1] == m[i + l - 1]) break;
        }
    }

    vector<int> gol[2 * (n + 1) + 1][2 * (n + 1) + 1], gor[2 * (n + 1) + 1][2 * (n + 1) + 1];
    for(int i = 0; i < m.size(); i += 2){
        for(int l = 3; i + l <= m.size(); l += 2) if(i == orig[i][l]) {
            gol[orig[i + 2][l - 2] / 2][l / 2].push_back(i / 2);
            gor[orig[i][l - 2] / 2][l / 2].push_back(i / 2);
        }
    }

    int r = 0, dp[n + 2][n + 2][n + 2][2];
    RFOR(l, n, 1) FOR(i, 0, n - l + 1) if(orig[2 * i][2 * l - 1] == 2 * i) {
        FOR(s, 0, l - 1) FOR(lr, 0, 1) {
            if(i == 0 || i + l == n + 1) {
                dp[i][l][s][lr] = -dist[i + s];
                continue;
            }

            int ldp = INT_MIN, rdp = INT_MIN;
            for(int j : gol[i][l]) ldp = max(ldp, m[2 * j + 1] + dp[j][l + 1][s + 1][0]);
            for(int j : gor[i][l]) rdp = max(rdp, m[2 * (j + l) - 1] + dp[j][l + 1][s][1]);

            (lr ? ldp : rdp) += pfx[i + l - 1] - pfx[i];

            dp[i][l][s][lr] = min(ldp, rdp);
            if(l == 1) r = max(r, dp[i][l][s][lr]);
        }
    }

    cout << r << endl;
}
