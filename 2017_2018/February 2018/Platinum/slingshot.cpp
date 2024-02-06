#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(long long i = a; i <= b; i++)
#define RFOR(i, a, b) for(long long i = a; i >= b; i--)
#define ll long long
#define maxn 100005

struct Sling { ll a, b, t, id, bya_id; };
struct Qry { ll x, y, id; };
 
struct MinSegmentTree{ // ONE-BASED INDEXED
public:
    vector<ll> tree;
    ll n;
 
    MinSegmentTree(ll n) {
        this->n = n;
        tree.assign(4 * this->n + 1, INT_MAX);
    }
    MinSegmentTree(const vector<ll> &a) : MinSegmentTree(a.size()){
        build(a, 1, 1, n);
    }
    void setto(ll i, ll x){ // poll update
        if(1 <= i && i <= n) update_go(1, 1, n, make_pair(i, x - query(i, i)));
    }
    ll query(ll i, ll j){
        if(i == 0) return 0;
        if(i > j) return 0;
        return query_range(1, 1, n, make_pair(i, j));
    }
 
private:
    void build(const vector<ll> &a, ll i, ll l, ll r){
        if(l > r) return;
        if(l == r) {
            tree[i] = a[l - 1];
            return;
        }
        
        ll m = (l + r) / 2;
        build(a, 2*i, l, m);
        build(a, 2*i + 1, m + 1, r);
 
        tree[i] = min(tree[2*i], tree[2*i + 1]);
    }
    void update_go(ll i, ll l, ll r, pair<ll, ll> upd){
        if(l > r || upd.first < l || r < upd.first) return;
        if(upd.first == l && l == r) {
            tree[i] += upd.second;
            return;
        }
 
        ll m = (l + r) / 2;
        update_go(i * 2, l, m, upd);
        update_go(i * 2 + 1, m + 1, r, upd);
 
        tree[i] = min(tree[2*i], tree[2*i + 1]);
    }
    ll query_range(ll i, ll l, ll r, pair<ll, ll> qry){
        if(l > r || qry.second < l || r < qry.first) {
            return LLONG_MAX;
        }
 
        if(qry.first <= l && r <= qry.second) return tree[i];
 
        ll m = (l + r) / 2;
        return min(query_range(i * 2, l, m, qry), query_range(i * 2 + 1, m + 1, r, qry));
    }
};

int main() {
    ifstream cin ( "slingshot.in");
    ofstream cout ("slingshot.out");

    int n, m; cin >> n >> m;
    ll r[m];
    vector<Sling> s[2];
    vector<Qry> q[2];
    FOR(i, 1, n) {
        Sling s1; cin >> s1.a >> s1.b >> s1.t;
        if(s1.a < s1.b) s[0].push_back(s1);
        else swap(s1.a, s1.b), s[1].push_back(s1);
    }
    FOR(i, 1, m) {
        Qry q1; cin >> q1.x >> q1.y; 
        q1.id = i - 1;
        if(q1.x < q1.y) q[0].push_back(q1);
        else swap(q1.x, q1.y), q[1].push_back(q1);
        r[i - 1] = q1.y - q1.x;
    }
    int n2[2] = {(int)s[0].size(), (int)s[1].size()}, m2[2] = {(int)q[0].size(), (int)q[1].size()};

    FOR(ii, 0, 1) {
        Sling sbya[n2[ii] + 2], sbyb[n2[ii] + 2];
        FOR(i, 1, n2[ii]) {
            sbya[i] = sbyb[i] = s[ii][i - 1];
            sbya[i].id = sbyb[i].id = i;
        }
        sort(sbya + 1, sbya + n2[ii] + 1, [](Sling& s, Sling& s2){ return s.a < s2.a; }), sort(sbyb + 1, sbyb + n2[ii] + 1, [](Sling s, Sling s2){ return s.b < s2.b; });
        sort(begin(q[ii]), end(q[ii]), [](Qry& qa, Qry& qb){ return qa.y < qb.y; });
        vector<int> b_id(n2[ii] + 1);
        FOR(i, 1, n2[ii]) b_id[sbyb[i].id] = i;
        FOR(i, 1, n2[ii]) {
            sbyb[b_id[sbya[i].id]].bya_id = i;
        }
        
        {
            MinSegmentTree lend(n2[ii] + 2), lend2(n2[ii] + 2); int l = 0;
            FOR(i, 0, (int)q[ii].size() - 1){
                while(l + 1 <= n2[ii] && sbyb[l + 1].b < q[ii][i].y) {
                    l++;
                    lend.setto(sbyb[l].bya_id, - sbyb[l].a - sbyb[l].b + sbyb[l].t);
                    lend2.setto(sbyb[l].bya_id, sbyb[l].a - sbyb[l].b + sbyb[l].t);
                }

                
                int lo = 0, hi = n2[ii];
                while(lo < hi){
                    int md = (lo + hi + 1) / 2;
                    if(md == 0 || sbya[md].a < q[ii][i].x){
                        lo = md;
                    }else{
                        hi = md - 1;
                    }
                }

                if(l == 0) continue;
                if(lo != 0) r[q[ii][i].id] = min(r[q[ii][i].id], q[ii][i].x + q[ii][i].y + lend.query(1, lo));
                if(lo + 1 != n + 1) r[q[ii][i].id] = min(r[q[ii][i].id], - q[ii][i].x + q[ii][i].y + lend2.query(lo + 1, n));
            }
        }
        {
            MinSegmentTree rend(n2[ii] + 2), rend2(n2[ii] + 2); int rpt = n2[ii] + 1;
            RFOR(i, (int)q[ii].size() - 1, 0){
                while(1 <= rpt - 1 && q[ii][i].y <= sbyb[rpt - 1].b) {
                    rpt--;
                    rend.setto(sbyb[rpt].bya_id, - sbyb[rpt].a + sbyb[rpt].b + sbyb[rpt].t);
                    rend2.setto(sbyb[rpt].bya_id, sbyb[rpt].a + sbyb[rpt].b + sbyb[rpt].t);
                }

                int lo = 0, hi = n2[ii];
                while(lo < hi){
                    int md = (lo + hi + 1) / 2;
                    if(md == 0 || sbya[md].a < q[ii][i].x){
                        lo = md;
                    }else{
                        hi = md - 1;
                    }
                }
                if(rpt == n2[ii] + 1) continue;

                if(lo != 0) r[q[ii][i].id] = min(r[q[ii][i].id], q[ii][i].x - q[ii][i].y + rend.query(1, lo));
                if(lo + 1 != n + 1) r[q[ii][i].id] = min(r[q[ii][i].id], - q[ii][i].x - q[ii][i].y + rend2.query(lo + 1, n));
            }
        }
    }

    FOR(i, 0, m - 1) cout << r[i] << endl;
}
