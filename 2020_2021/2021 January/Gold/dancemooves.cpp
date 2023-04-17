#include <iostream>
#include <vector>
using namespace std;
#define MAXN 100005

int N, K, r, P[MAXN]/* P[i] = next node after i */, g[MAXN]/* g[i] = group of node i */, ANS[MAXN]/* ANS[i] = return value for node i*/, C[MAXN]/* C[i] = cow i count */;
long long M;
bool v[MAXN];
vector<int> G[MAXN];
vector<pair<int, int> > S[MAXN * 2];

void groupNodes(int& gc, int i){
    int s = i, n = i;
    gc++;
    do{
        G[gc].push_back(n);
        g[n] = gc;
        n = P[n];
    }while(n != s);
}

void add(int gid, int x){
    for(auto p : S[gid]) if(p.second <= x) {
        if(C[p.first] == 0) r++;
        C[p.first]++;
    }
}

void remove(int gid, int x){
    for(auto p : S[gid]) if(p.second <= x) {
        if(C[p.first] == 1) r--;
        C[p.first]--;
    }
}

int main(){
    cin >> N >> K >> M;
    for(int i = 1; i <= N; i++){
        ANS[i] = i;
        S[i].push_back(make_pair(i, 0));
    }
    // 1. STIMULATE FIRST K SWAPS  
    for(int i = 1, a, b; i <= K; i++){
        cin >> a >> b;
        S[ANS[a]].push_back(make_pair(b, i));
        S[ANS[b]].push_back(make_pair(a, i));
        swap(ANS[a], ANS[b]);
    }

    for(int i = 1; i <= N; i++) P[ANS[i]] = i;

    for(int i = 1, gc = 0; i <= N; i++){ if(!g[i]){
        // 2. GROUP NODES
        groupNodes(gc, i);

        // 3. CALCULATE ANSWERS
        long long D = min(M / K, (long long)G[gc].size());
        int R = (D == G[gc].size()) ? 0 : M % K;
        for(int j = 0; j < D; j++) {
            add(G[gc][j], K);
        }

        for(int j = 0; j < G[gc].size(); j++){
            // add extra R swaps
            add(G[gc][((D - 1) + j + 1) % G[gc].size()], R);
            ANS[G[gc][j]] = r;

            remove(G[gc][j], K);

            remove(G[gc][((D - 1) + j + 1) % G[gc].size()], R);

            add(G[gc][((D - 1) + j + 1) % G[gc].size()], K);
        }
        
        for(int j = 0; j < D; j++) {
            remove(G[gc][j], K);
        }
    } }

    for(int i = 1; i <= N; i++) cout << ANS[i] << endl;
}
