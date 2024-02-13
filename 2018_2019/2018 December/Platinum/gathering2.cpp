#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define maxn 100005

int n, m;
vector<int> adj[maxn], adjn(maxn), befn(maxn);
vector<int> bef[maxn], aft[maxn];
vector<bool> r(maxn), v(maxn);

void dfs(int i){
    if(r[i]) return;
    r[i] = true;

    for(int i2 : adj[i]) if(!aft[i2].size()) dfs(i2);
}

int main(){
    ifstream cin ("gathering.in");
    ofstream cout ("gathering.out");

    cin >> n >> m;
    FOR(i, 1, n - 1) {
        int a, b; cin >> a >> b; a--, b--;
        adj[a].push_back(b), adj[b].push_back(a);
        adjn[a]++, adjn[b]++;
    }
    FOR(i, 1, m){
        int a, b; cin >> a >> b; a--, b--;
        bef[b].push_back(a), aft[a].push_back(b);
        befn[b]++;
    }

    int ri = -1;
    queue<int> q;
    FOR(i, 0, n - 1) if(adj[i].size() == 1 && befn[i] == 0) q.push(i);
    while(q.size()){
        int i = q.front(); q.pop();
        if(v[i]) continue;
        v[i] = true, ri = i;
        for(int iaft : aft[i]) {
            befn[iaft]--; if(befn[iaft] == 0 && adjn[iaft] <= 1) q.push(iaft);
        }

        for(int i2 : adj[i]) if(!v[i2]) {
            adjn[i2]--; if(befn[i2] == 0 && adjn[i2] <= 1) q.push(i2);
        }
    }
  
    FOR(i, 0, n - 1) if(!v[i]) goto give_answer;

    dfs(ri);

    give_answer:;
    FOR(i, 0, n - 1) cout << r[i] << endl;
}
