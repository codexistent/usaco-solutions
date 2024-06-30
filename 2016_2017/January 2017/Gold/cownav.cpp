#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 25
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define f first
#define s second
const int DIR[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int n, dp[MAXN][MAXN][4][MAXN][MAXN][4], r = LONG_LONG_MAX;
bool e[MAXN][MAXN];

pair<pair<int, int>, int> fwd(pair<pair<int, int>, int> p){
    if(p.f.f == n && p.f.s == n) return p;

    if(1 <= p.f.f + DIR[p.s][0] && p.f.f + DIR[p.s][0] <= n){
        if(e[p.f.f + DIR[p.s][0]][p.f.s]) p.f.f += DIR[p.s][0];
    }
    if(1 <= p.f.s + DIR[p.s][1] && p.f.s + DIR[p.s][1] <= n){
        if(e[p.f.f][p.f.s + DIR[p.s][1]]) p.f.s += DIR[p.s][1];
    }
    return p;
}

main(){
    ifstream cin("cownav.in");
    ofstream cout("cownav.out");

    cin >> n;
    for(int i = n; i >= 1; i--) {
        string s; cin >> s;
        FOR(j, 1, n) e[i][j] = (s[j - 1] == 'E');
    }

    FOR(i, 1, n) FOR(j, 1, n) FOR(d, 0, 3) FOR(i2, 1, n) FOR(j2, 1, n) FOR(d2, 0, 3) dp[i][j][d][i2][j2][d2] = LONG_LONG_MAX;
    dp[1][1][0][1][1][1] = dp[1][1][1][1][1][0] = 0;
    priority_queue<pair<int, pair<pair<pair<int, int>, int>, pair<pair<int, int>, int> > > > pq;
    pq.push({0, {{{1, 1}, 0}, {{1, 1}, 1}}});
    pq.push({0, {{{1, 1}, 1}, {{1, 1}, 0}}});
    while(pq.size()){
        auto pqi = pq.top(); pq.pop();
        pair<pair<int, int>, int> p1 = pqi.s.f, p2 = pqi.s.s;
        if(dp[p1.f.f][p1.f.s][p1.s][p2.f.f][p2.f.s][p2.s] != -pqi.f) continue;
        if(p1.f.f == n && p1.f.s == n && p2.f.f == n && p2.f.s == n) r = min(r, -pqi.f);

        // turn right
        if(dp[p1.f.f][p1.f.s][(p1.s + 1) % 4][p2.f.f][p2.f.s][(p2.s + 1) % 4] > dp[p1.f.f][p1.f.s][p1.s][p2.f.f][p2.f.s][p2.s] + 1){
            dp[p1.f.f][p1.f.s][(p1.s + 1) % 4][p2.f.f][p2.f.s][(p2.s + 1) % 4] = dp[p1.f.f][p1.f.s][p1.s][p2.f.f][p2.f.s][p2.s] + 1;
            pq.push({-dp[p1.f.f][p1.f.s][(p1.s + 1) % 4][p2.f.f][p2.f.s][(p2.s + 1) % 4], {{p1.f, (p1.s + 1) % 4}, {p2.f, (p2.s + 1) % 4}}});
        }
        // turn left
        if(dp[p1.f.f][p1.f.s][(p1.s + 3) % 4][p2.f.f][p2.f.s][(p2.s + 3) % 4] > dp[p1.f.f][p1.f.s][p1.s][p2.f.f][p2.f.s][p2.s] + 1){
            dp[p1.f.f][p1.f.s][(p1.s + 3) % 4][p2.f.f][p2.f.s][(p2.s + 3) % 4] = dp[p1.f.f][p1.f.s][p1.s][p2.f.f][p2.f.s][p2.s] + 1;
            pq.push({-dp[p1.f.f][p1.f.s][(p1.s + 3) % 4][p2.f.f][p2.f.s][(p2.s + 3) % 4], {{p1.f, (p1.s + 3) % 4}, {p2.f, (p2.s + 3) % 4}}});
        }
        // move forward
        auto p1_2 = fwd(p1), p2_2 = fwd(p2);
        if(dp[p1_2.f.f][p1_2.f.s][p1_2.s][p2_2.f.f][p2_2.f.s][p2_2.s] > dp[p1.f.f][p1.f.s][p1.s][p2.f.f][p2.f.s][p2.s] + 1){
            dp[p1_2.f.f][p1_2.f.s][p1_2.s][p2_2.f.f][p2_2.f.s][p2_2.s] = dp[p1.f.f][p1.f.s][p1.s][p2.f.f][p2.f.s][p2.s] + 1;
            pq.push({-dp[p1_2.f.f][p1_2.f.s][p1_2.s][p2_2.f.f][p2_2.f.s][p2_2.s], {p1_2, p2_2}});
        }
    }

    cout << r << endl;
}
