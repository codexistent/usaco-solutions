#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define MAXNM 1505

static int dx[4] = {-1, 1, 0, 0};
static int dy[4] = {0, 0, -1, 1};
int N, M, Q, G[MAXNM][MAXNM];

int valid(int i, int j){
    return (0 <= i && i <= N - 1) && (0 <= j && j <= M - 1) && (G[i][j] != -1);
}
int valid2(int i, int j){
    return (0 <= i && i <= N - 1) && (0 <= j && j <= M - 1) && (G[i][j] == 0);
}

struct BCC { // gets all bi-connected components of an undirected graph
    int n, count = 0;
    vector<vector<pair<int, int>>> c;
    vector<set<int>> m;
    BCC (int n, const vector<vector<int>>& e) : n(n){
        m.resize(n);
        compute_bccs(e);

        for(int i = 0; i < c.size(); i++) {
            for(auto j : c[i]) {
                m[j.f].insert(i), m[j.s].insert(i);
            }
        }
    }
private:
    int timer = 0;
    void compute_bccs(const vector<vector<int>>& e){
        int m = 0; for(auto v : e) m += v.size();

        int* tin = new int[n];
        int* low = new int[n];
        int* p = new int[n];
        list<pair<int, int>>* s = new list<pair<int, int>>[m];
        FOR(i, 0, n - 1) tin[i] = low[i] = p[i] = -1;

        FOR(i, 0, n - 1) {
            if(tin[i] == -1) {
                timer = 0;
                dfs1(i, tin, low, s, p, e);
            }

            if(s->size()){
                vector<pair<int, int>> v;
                while(s->size() > 0){
                    v.pb(s->back());
                    s->pop_back();
                }
                c.push_back(v);
            }
        }
    }

    void dfs1(int v, int tin[], int low[], list<pair<int, int>>* s, int p[], const vector<vector<int>>& e){
        tin[v] = low[v] = ++timer;
        int ch = 0;

        for(int to : e[v]){
            if(tin[to] == -1){
                ch++;
                p[to] = v, s->pb(mp(v, to));

                dfs1(to, tin, low, s, p, e);

                low[v] = min(low[v], low[to]);

                if((tin[v] == 1 && ch > 1) || (tin[v] > 1 && low[to] >= tin[v])){
                    vector<pair<int, int>> cc;
                    while(s->back().f != v || s->back().s != to) {
                        cc.pb(s->back());
                        s->pop_back();
                    }
                    cc.pb(s->back());
                    s->pop_back();
                    c.pb(cc);
                }
            }else if(to != p[v]){
                low[v] = min(low[v], tin[to]);
                if(tin[v] > tin[to]) s->pb(mp(v, to));
            }
        }
    }
};

int id[MAXNM][MAXNM], idn = 1;
bool v[MAXNM][MAXNM];

void dfs_e(int x, int y, vector<vector<int>>& e){
    if(v[x][y]) return;
    v[x][y] = true;

    FOR(i, 0, 3){
        if(valid(x + dx[i], y + dy[i])) {
            if(id[x + dx[i]][y + dy[i]] == -1) id[x + dx[i]][y + dy[i]] = idn++;
            vector<int> v;
            e.pb(v);

            e[id[x][y]].pb(id[x + dx[i]][y + dy[i]]);
            dfs_e(x + dx[i], y + dy[i], e);
        }
    }
}

bool share_bcc(int a, int b, const BCC& bcc){
    for(int i : bcc.m[a]) if(bcc.m[b].count(i)) return true;
    return false;
}

bool flood1[MAXNM][MAXNM];
void dfs_ff(int i, int j){
    if(flood1[i][j]) return;
    flood1[i][j] = true;

    FOR(d, 0, 3) if(valid2(i + dx[d], j + dy[d])) dfs_ff(i + dx[d], j + dy[d]);
}
void fillflood(int i, int j){
    FOR(i, 0, N - 1) FOR(j, 0, M - 1) flood1[i][j] = false;
    dfs_ff(i, j);
}

int main() {
    ifstream cin ("pushabox.in");
    ofstream cout ("pushabox.out");

    cin >> N >> M >> Q;
    pair<int, int> a, b;
    FOR(i, 0, N - 1){
        string s; cin >> s;
        FOR(j, 0, M - 1) {
            if(s[j] == '#') G[i][j] = -1;
            if(s[j] == 'A') G[i][j] = 1, a = mp(i, j);
            if(s[j] == 'B') G[i][j] = 2, b = mp(i, j);
            if(s[j] == '.') G[i][j] = 0;
        }
    }

    vector<vector<int>> e;
    FOR(i, 0, N - 1) FOR(j, 0, M - 1) v[i][j] = false, id[i][j] = -1;
    id[b.f][b.s] = 0;
    dfs_e(b.f, b.s, e);

    BCC bcc(idn, e);

    bool res[N][M][4];
    FOR(i, 0, N - 1) FOR(j, 0, M - 1) FOR(k, 0, 3) res[i][j][k] = false;
    priority_queue<pair<pair<int, int>, int>> pq;
    fillflood(a.f, a.s);
    FOR(d, 0, 3) if(valid(b.f + dx[d], b.s + dy[d]) && valid(b.f - dx[d], b.s - dy[d]) && flood1[b.f - dx[d]][b.s - dy[d]]) {
        pq.push(mp(mp(b.f, b.s), d));
    }
    while(!pq.empty()){
        auto state = pq.top();
        pq.pop();
        if(res[state.f.f][state.f.s][state.s]) continue;
        int x = state.f.f, y = state.f.s, d = state.s;
        res[x][y][d] = true;

        // continue in current direction
        if(valid(x + dx[d], y + dy[d])){
            pq.push(mp(mp(x + dx[d], y + dy[d]), d));
        }

        // change directions
        FOR(d2, 0, 3) if(d2 != d){
            if(valid(x - dx[d2], y - dy[d2]) && share_bcc(id[x - dx[d]][y - dy[d]], id[x - dx[d2]][y - dy[d2]], bcc)){
                pq.push(mp(mp(x, y), d2));
            }
        }
    }

    FOR(i, 1, Q){
        int x, y;
        cin >> x >> y;
        x--, y--;
        bool valid = (x == b.f && y == b.s);
        FOR(d, 0, 3) valid |= res[x][y][d];
        
        if(valid) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
