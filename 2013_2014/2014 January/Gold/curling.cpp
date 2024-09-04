#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define f first
#define s second

ll n;
db mns[2] = {INFINITY, INFINITY};
pair<db, db> st[2];
vector<pair<db, db>> c[2], ch[2];
vector<pair<pair<db, db>, pair<db, db>>> chs[2];

int orientation(pair<db, db> a, pair<db, db> b, pair<db, db> c){
    db cx = (a.f - b.f)*(c.s - b.s) - (c.f - b.f)*(a.s - b.s);
    if(cx < 0) return -1; // ccw
    if(cx > 0) return 1; // cw
    return 0;
}
db distSq(pair<db, db> a, pair<db, db> b){
    return (a.f - b.f) * (a.f - b.f) + (a.s - b.s) * (a.s - b.s);
}
bool comp_c0(const pair<db, db>& a, const pair<db, db>& b){
    int o = orientation(st[0], a, b);
    if(o == 0){
        return distSq(st[0], a) < distSq(st[0], b);
    }
    return o == 1;
}
bool comp_c1(const pair<db, db>& a, const pair<db, db>& b){
    int o = orientation(st[1], a, b);
    if(o == 0){
        return distSq(st[1], a) < distSq(st[1], b);
    }
    return o == 1;
}
bool comp_chs(const pair<pair<db, db>, pair<db, db>>& a, pair<pair<db, db>, pair<db, db>>& b){
    if(a.f.f == b.f.f) return a.s.f < b.s.f;
    return a.f.f < b.f.f;
}

void getHull(int hi){
    FOR(i, 0, n - 1){
        ch[hi].push_back(c[hi][i]);
        while(ch[hi].size() >= 4){
            pair<db, db> l3 = ch[hi].back(); ch[hi].pop_back();
            pair<db, db> l2 = ch[hi].back(); ch[hi].pop_back();
            pair<db, db> l1 = ch[hi].back(); ch[hi].pop_back();

            ch[hi].push_back(l1);
            if(orientation(l1, l2, l3) != 1) {
                ch[hi].push_back(l3);
            }else{
                ch[hi].push_back(l2);
                ch[hi].push_back(l3);
                break;
            }
        }
    }
}

void getSegments(int hi){
    FOR(i, 0, (ll)ch[hi].size() - 1){
        pair<pair<db, db>, pair<db, db>> sg = {ch[hi][i], ch[hi][(i + 1) % ((ll)ch[hi].size())]};
        if(sg.f.f > sg.s.f) swap(sg.f, sg.s);
        chs[hi].push_back(sg);
    }
}

int coverage(pair<pair<db, db>, pair<db, db>> sg, pair<db, db> pt){ // takes in a line segment and point; returns -2 if not in x range, -1 if below, 0 if on, and 1 if above segment
    if(sg.f.f <= pt.f && pt.f <= sg.s.f){
        db sgv = sg.f.s;
        if(sg.s.f != sg.f.f){
            sgv += ((pt.f - sg.f.f) / (sg.s.f - sg.f.f)) * (sg.s.s - sg.f.s);
        }else{
            if(min(sg.f.s, sg.s.s) <= pt.s && pt.s <= max(sg.f.s, sg.s.s)) return 0;
            return -2;
        }

        if(pt.s < sgv) return -1; // below segment
        if(sgv < pt.s) return 1; // above segment
        return 0; // on segment
    }
    return -2; // not in x range
}

int main(){
    ifstream cin ("curling.in");
    ofstream cout ("curling.out");

    cin >> n;
    FOR(t, 0, 1){
        FOR(i, 1, n){
            pair<db, db> p;
            cin >> p.f >> p.s;
            if(p.s <= mns[t]){
                mns[t] = p.s;
                st[t] = p;
            }
            c[t].push_back(p);
        }
    }
    FOR(hi, 0, 1){
        if(hi == 0) sort(begin(c[hi]), end(c[hi]), comp_c0);
        if(hi == 1) sort(begin(c[hi]), end(c[hi]), comp_c1);
        getHull(hi), getSegments(hi), sort(begin(chs[hi]), end(chs[hi]), comp_chs);

        ll r = 0, ptr = 0, p1 = -1, p2 = -1;
        sort(begin(c[!hi]), end(c[!hi]));
        for(auto ci : c[!hi]){
            // update top/bottom pointers
            while(ptr <= chs[hi].size() - 1 && chs[hi][ptr].f.f <= ci.f){
                if(p1 == -1 || chs[hi][p1].s.f <= chs[hi][ptr].s.f){
                    p2 = p1;
                    p1 = ptr;
                }else if(p2 == -1 || chs[hi][p2].s.f <= chs[hi][ptr].s.f){
                    p2 = ptr;
                }
                ptr++;
            }

            int c1 = (p1 == -1) ? -2 : coverage(chs[hi][p1], ci);
            int c2 = (p2 == -1) ? -2 : coverage(chs[hi][p2], ci);
            if(c1 == 0 || c2 == 0){ // on segment
                r++;
            }else if((c1 == 1 && c2 == -1) || (c1 == -1 && c2 == 1)) { // in between two segments
                r++;
            }
        }

        if(hi == 0) cout << r << " ";
        else cout << r << endl;
    }
}
