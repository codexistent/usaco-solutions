#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define RFOR(i, a, b) for(int i = a; i >= b; i--)
#define MAXN 755
#define pb push_back
#define mp make_pair
#define f first
#define s second
static int pd[3] = {0, 1, -1};
static int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};

int n, g[MAXN][MAXN], p[MAXN * MAXN], s[MAXN * MAXN], cn, h[MAXN * MAXN], out[MAXN * MAXN];

bool valid(pair<int, int> x) { return (1 <= x.f && x.f <= n) && (1 <= x.s && x.s <= n); }
int hsh(pair<int, int> x) { return valid(x) ? ((x.f - 1) * n + x.s) : 0; }
int find(int x) { return (p[x] == x) ? x : (p[x] = find(p[x])); }
void join(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) return;

    if(s[a] < s[b]) swap(a, b);

    s[a] += s[b];
    h[a] += h[b];
    p[a] = p[b] = a;
    cn--;
}

int main() {
    ifstream cin("valleys.in");
    ofstream cout("valleys.out");

    cin >> n;
    vector<pair<int, pair<int, int>>> po;
    FOR(i, 1, n) FOR(j, 1, n) { 
        cin >> g[i][j];
        po.pb(mp(g[i][j], mp(i, j)));
    }
    sort(begin(po), end(po));
    
    out[n * n] = cn = 1;
    FOR(i, 0, n * n) p[i] = i, s[i] = 1;
    RFOR(i, n*n - 1, 0){
        cn++;
        for(int xd : pd) for(int yd : pd) if(!hsh(mp(po[i].s.f + xd, po[i].s.s + yd)) || g[po[i].s.f + xd][po[i].s.s + yd] > g[po[i].s.f][po[i].s.s]){
            join(hsh(po[i].s), hsh(mp(po[i].s.f + xd, po[i].s.s + yd)));
        }
        out[i] = cn;
    }

    long long r = 0;
    FOR(i, 0, n * n) p[i] = i, s[i] = 1, h[i] = 0;
    s[0] = 0;
    FOR(i, 0, n * n - 1){
        FOR(j, 0, 3) if(valid(mp(po[i].s.f + dx[j], po[i].s.s + dy[j])) && g[po[i].s.f][po[i].s.s] > g[po[i].s.f + dx[j]][po[i].s.s + dy[j]]) {
            join(hsh(po[i].s), hsh(mp(po[i].s.f + dx[j], po[i].s.s + dy[j])));
        }
        h[find(hsh(po[i].s))] += out[i + 1] - out[i];
        if(h[find(hsh(po[i].s))] == 0) {
            r += s[find(hsh(po[i].s))];
        }
    }

    cout << r << endl;
}
