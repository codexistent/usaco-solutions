#include <bits/stdc++.h>
using namespace std;
#define MAXN 505
#define ll long long
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define f first
#define s second

ll n;
pair<pair<ll, ll>, bool> c[MAXN];
pair<ll, ll> r = {0, 0};

int main(){
    ifstream cin("cowrect.in");
    ofstream cout("cowrect.out");

    cin >> n;
    FOR(i, 1, n) {
        cin >> c[i].f.f >> c[i].f.s;
        char ch; cin >> ch;
        c[i].s = ch == 'H';
    }
    sort(c + 1, c + 1 + n);

    FOR(xl, 1, n){
        if(xl != 1 && c[xl - 1].f.f == c[xl].f.f) continue;
        multiset<pair<ll, bool>> cx;
        FOR(xh, xl, n){
            cx.insert({c[xh].f.s, c[xh].s});
            if(xh != n && c[xh].f.f == c[xh + 1].f.f) continue;

            ll yl = (*cx.begin()).f, yh = (*cx.begin()).f, nc = 0, prev = -1;
            auto it = cx.begin();
            while(it != end(cx)){
                while(it != end(cx) && (prev == (*it).f || !(*it).s)){
                    prev = (*it).f;
                    it = next(it);
                }

                yl = yh = (*it).f, nc = 0;
                while(it != end(cx) && (*it).s){
                    yh = (*it).f;
                    nc++;
                    it = next(it), prev = (*it).f;
                }

                if(r.f < nc || (r.f == nc && r.s > (yh - yl) * (c[xh].f.f - c[xl].f.f))){
                    r = {nc, (yh - yl) * (c[xh].f.f - c[xl].f.f)};
                }
            }
        }
    }

    cout << r.f << endl << r.s << endl;
}
