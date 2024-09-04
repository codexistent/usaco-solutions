#include <bits/stdc++.h>
using namespace std;
#define MAXN 20
#define MAXD 55
#define BITSZ 32768
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define f first
#define s second
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int n, g[MAXD][MAXD], s[MAXN][MAXN], dp[BITSZ][MAXN];
pair<int, int> d, p[MAXN];
int bfs[MAXD][MAXD];
bool v[MAXD][MAXD];

bool inbounds(int i, int j){
    return (1 <= i && i <= d.f) && (1 <= j && j <= d.s);
}

void flood(int i, int j){
    g[i][j] = n;
    FOR(k, 0, 3){
        if(inbounds(i + dir[k][0], j + dir[k][1]) && g[i + dir[k][0]][j + dir[k][1]] == -1){
            flood(i + dir[k][0], j + dir[k][1]);
        }
    }
}

int main(){
    ifstream cin("island.in");
    ofstream cout("island.out");

    cin >> d.f >> d.s;
    FOR(i, 1, d.f) {
        FOR(j, 1, d.s) {
            char c; cin >> c;
            if(c == '.'){
                g[i][j] = -2; // not crossable
            }else if(c == 'X'){
                g[i][j] = -1; // island square
            }else{
                g[i][j] = 0; // swim
            }
        }
    }

    n = 0;
    FOR(i, 1, d.f) FOR(j, 1, d.s) {
        if(g[i][j] == -1) n++, flood(i, j), p[n] = {i, j};
    }

    FOR(i, 1, n){
        FOR(j, 1, n) s[i][j] = 1000000;
        s[i][i] = 0;

        priority_queue<pair<int, pair<int, int> > > pq;
        pq.push({0, p[i]});

        FOR(i, 1, d.f) FOR(j, 1, d.s) v[i][j] = false, bfs[i][j] = 1000000; 
        while(pq.size()){
            auto pqi = pq.top(); pq.pop();
            if(v[pqi.s.f][pqi.s.s]) continue;
            v[pqi.s.f][pqi.s.s] = true;

            if(g[pqi.s.f][pqi.s.s] != 0) s[i][g[pqi.s.f][pqi.s.s]] = min(s[i][g[pqi.s.f][pqi.s.s]], -pqi.f);

            FOR(j, 0, 3) if(inbounds(pqi.s.f + dir[j][0], pqi.s.s + dir[j][1]) && g[pqi.s.f + dir[j][0]][pqi.s.s + dir[j][1]] != -2) {
                pair<int, pair<int, int>> nx = {-pqi.f + (g[pqi.s.f + dir[j][0]][pqi.s.s + dir[j][1]] == 0), {pqi.s.f + dir[j][0], pqi.s.s + dir[j][1]}};
                if(bfs[nx.s.f][nx.s.s] > nx.f){
                    bfs[nx.s.f][nx.s.s] = nx.f;
                    nx.f *= -1;
                    pq.push(nx);
                }
            }
        }
    }

    int BITSZn = pow(2, n);
    FOR(i, 0, BITSZ - 1) FOR(j, 0, MAXN - 1) dp[i][j] = 1000000;
    FOR(i, 1, n) dp[1 << (i - 1)][i] = 0;
    FOR(m, 1, BITSZn - 2){
        FOR(i, 1, n) if(m & (1 << (i - 1))){
            if(dp[m][i] == 1000000) continue;
            FOR(j, 1, n) if(!(m & (1 << (j - 1)))){
                dp[m | (1 << (j - 1))][j] = min(dp[m | (1 << (j - 1))][j], dp[m][i] + s[i][j]);
            }
        }
    }

    int r = 1000000;
    FOR(i, 1, n) r = min(r, dp[BITSZn - 1][i]);

    cout << r << endl;
}
