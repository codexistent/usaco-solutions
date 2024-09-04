#include <bits/stdc++.h>
using namespace std;
#define MAXN 1005
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define f first
#define s second
#define db double
#define int long long

int n, m, k = 0, pc[MAXN];
pair<int, int> c[MAXN];
pair<pair<int, int>, pair<int, int>> ls[MAXN];
vector<int> p[MAXN];
db a[MAXN];

bool ccw(pair<int, int> i, pair<int, int> j, pair<int, int> k){
    return (k.s - i.s) * (j.f - i.f) > (j.s - i.s) * (k.f - i.f);
}

bool intersect(pair<int, int> i1, pair<int, int> i2, pair<int, int> j1, pair<int, int> j2){
    return ccw(i1, j1, j2) != ccw(i2, j1, j2) && ccw(i1, i2, j1) != ccw(i1, i2, j2);
}

main(){
    ifstream cin("crazy.in");
    ofstream cout("crazy.out");

    cin >> n >> m;
    FOR(i, 1, n){
        cin >> ls[i].f.f >> ls[i].f.s;
        cin >> ls[i].s.f >> ls[i].s.s;
    }

    // find polygons
    bool lsv[MAXN];
    FOR(i, 1, n) lsv[i] = false;
    FOR(i, 1, n) if(!lsv[i]) {
        k++;
        pair<int, int> cp = ls[i].s;
        p[k].push_back(i), pc[i] = 0, lsv[i] = true;

        while(cp != ls[i].f){
            FOR(j, 1, n) {
                if(!lsv[j] && (ls[j].f == cp || ls[j].s == cp)){
                    if(ls[j].s == cp) swap(ls[j].f, ls[j].s);
                    lsv[j] = true;
                    cp = ls[j].s;
                    p[k].push_back(j);
                }
            }
        }

        // calculate area using shoelace theorem
        db l = 0, r = 0;
        FOR(i, 1, p[k].size()){
            l += (ls[p[k][i - 1]].f.f * ls[p[k][i - 1]].s.s);
            r += (ls[p[k][i - 1]].s.f * ls[p[k][i - 1]].f.s);
        }
        a[k] = 0.5 * abs(l - r);
    }

    pc[0] = 0;
    FOR(i, 1, m) {
        cin >> c[i].f >> c[i].s;
        int pi = -1; db ai = -1;
        FOR(j, 1, k){
            int lsc = 0;
            for(int lsi : p[j]){
                lsc += intersect(c[i], {c[i].f + 1, 1000005}, ls[lsi].f, ls[lsi].s);
            }

            if(lsc % 2 == 1){
                if(ai == -1 || ai >  a[j]){
                    pi = j;
                    ai = a[j];
                }
            }
        }

        if(ai == -1) pc[0]++;
        else pc[pi]++;
    }

    int mx = 0;
    FOR(i, 0, k) {
        mx = max(mx, pc[i]);
    }

    cout << mx << endl;
}
