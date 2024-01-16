#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define pii pair<int, int>
#define mp make_pair
#define pb push_back
#define ins insert
#define f first
#define s second

vector<int> P, Pw, C;
vector<map<int, multiset<int>>> W;
vector<set<pii>> Mw;
vector<vector<pii>> MST;
multiset<int> R;

struct DSU {
    vector<int> p, s;
    DSU(int n){
        p.resize(n + 1); FOR(i, 0, n) p[i] = i;
        s.assign(n + 1, 1);
    }

    int find (int x) {
        return p[x] == x ? x : (p[x] = find(p[x]));
    }
    bool onion (int a, int b){
        a = find(a), b = find(b);
        if(a == b) return false;

        if(s[a] < s[b]) swap(a, b);
        s[a] += s[b];
        p[a] = p[b] = a;
        return true;
    }
};

int res(int n){
    if(Mw[n].empty() || (Mw[n].size() == 1 && Mw[n].begin()->s == C[n])) return INT_MAX;
    if(Mw[n].begin()->s == C[n]) return next(Mw[n].begin())->f;
    return Mw[n].begin()->f;
}
void ms_erase(multiset<int>& ms, int x){
    ms.erase(ms.find(x));
}
void dfs(vector<bool>& v, int n, int p){
    v[n] = true, P[n] = p;

    for(auto e : MST[n]) if(e.f != p) {
        int n2 = e.f, w = e.s;
        Pw[n2] = w;
        dfs(v, n2, n);

        if(W[n].find(C[n2]) == W[n].end()){
            multiset<int> s;
            W[n].ins(mp(C[n2], s));
        }else{
            Mw[n].erase(mp(*W[n][C[n2]].begin(), C[n2]));
        }
        W[n][C[n2]].ins(w);
        Mw[n].ins(mp(*W[n][C[n2]].begin(), C[n2]));
    }

    R.ins(res(n));
}

int main(){
    ifstream cin("grass.in");
    ofstream cout("grass.out");

    int N, M, K, Q;
    cin >> N >> M >> K >> Q;
    MST.resize(N);
    priority_queue<pair<int, pii>, vector<pair<int, pii>>, greater<pair<int, pii>>> E;
    FOR(i, 1, M){
        int a, b, w; cin >> a >> b >> w;
        E.push(mp(w, mp(a - 1, b - 1)));
    }

    DSU dsu(N);
    while(!E.empty()){
        auto e = E.top();
        E.pop();
        if(dsu.onion(e.s.f, e.s.s)){
            MST[e.s.f].pb(mp(e.s.s, e.f));
            MST[e.s.s].pb(mp(e.s.f, e.f));
        }
    }

    C.resize(N);
    FOR(i, 0, N - 1) cin >> C[i];

    P.resize(N), Pw.resize(N), W.resize(N), Mw.resize(N);
    vector<bool> v(N);
    FOR(i, 0, N - 1) if(!v[i]) dfs(v, i, -1);

    FOR(i, 1, Q){
        int n, c2;
        cin >> n >> c2; n--;
        int pc = C[n];

        // update n
        ms_erase(R, res(n));

        C[n] = c2; 
        R.ins(res(n));

        // update P[n]
        if(P[n] != -1){
            ms_erase(R, res(P[n])), Mw[P[n]].erase(mp(*W[P[n]][pc].begin(), pc));
            ms_erase(W[P[n]][pc], Pw[n]);
            if(W[P[n]][pc].size() == 0) {
                W[P[n]].erase(pc);
            }else{
                Mw[P[n]].ins(mp(*W[P[n]][pc].begin(), pc));
            }

            if(W[P[n]].find(C[n]) == W[P[n]].end()) {
                multiset<int> ms;
                W[P[n]].ins(mp(C[n], ms));
            }else{
                Mw[P[n]].erase(mp(*W[P[n]][C[n]].begin(), C[n]));
            }
            W[P[n]][C[n]].ins(Pw[n]), Mw[P[n]].ins(mp(*W[P[n]][C[n]].begin(), C[n]));
            R.ins(res(P[n]));
        }

        cout << *R.begin() << endl;
    }
}
