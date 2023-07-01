#include <iostream>
#include <vector>
using namespace std;
#define MAXK 50005
#define INF 1000000007
#define MOD INF

int K, N[MAXK];

long long compute(vector<pair<int, int> > v){
    long long R = 0, M = 0;
    vector<long long> PFX, SFX, D[K];
    for(auto p : v) D[p.first].push_back(p.second);  // D[i] = distances of other nodes from node 1 in graph i

    for(int i = 0; i < K; i++){
        M = max(M, 2ll * N[i]); // M = max 2*N[i] over along long D
        while(PFX.size() <= M) PFX.push_back(1), SFX.push_back(1);  // expand size according to M
        vector<long long> C(2*N[i]);  // C[i] = # distances to node 1 of value i
        for(int d : D[i]) C[d]++;

        for(int j = 0; j < 2*N[i]; j++, C[j] += C[j - 1]) PFX[j] *= C[j], PFX[j] %= MOD; // PFX[j] = product of along long C[j]s for every i
        SFX[2*N[i]] *= C[2*N[i] - 1], SFX[2*N[i]] %= MOD;
    }
    for(int i = 1; i <= M; i++) SFX[i] *= SFX[i - 1], SFX[i] %= MOD;

    for(int i = 1; i < M; i++) R += ((PFX[i] * SFX[i] - PFX[i - 1] * SFX[i - 1] + MOD) % MOD) * i, R = (R + MOD) % MOD;
    return R;
}

int main(){
    cin >> K;
    vector<pair<int, int> > ED/*even distances*/, OD/*odd distances*/, CD/*combined max of even & odd if both parity distances exist*/;

    for(int i = 0, M; i < K; i++){
        cin >> N[i] >> M;
        vector<int> E[2*N[i]]; // edges
        for(int j = 0, a, b; j < M; j++) { // get/make edges
            cin >> a >> b; a--, b--;
            E[a].push_back(N[i] + b), E[N[i] + b].push_back(a); // nodes 0...N[i] - 1 are along long even distances 
            E[b].push_back(N[i] + a), E[N[i] + a].push_back(b); //  N[i]...2*N[i] - 1 are along long odd distances
        }

        // bfs for shortest even/odd dist to node 1
        vector<long long> D(2*N[i], INF), Q; // D stores bfs'd distances
        Q.push_back(0);
        D[0] = 0;
        for(int j = 0; j < Q.size(); j++){ // 
            for(int k : E[Q[j]]) if(D[k] == INF) { // try Q[j] -> k
                Q.push_back(k);
                D[k] = D[Q[j]] + 1;
            }
        }
        
        for(int j = 0; j < N[i]; j++){
            if(D[j] < INF) ED.push_back(make_pair(i, D[j]));  // nodes 0...N[i] - 1 are along long even distances 
            if(D[j + N[i]] < INF) OD.push_back(make_pair(i, D[j + N[i]]));  //  N[i]...2*N[i] - 1 are along long odd distances
            if(D[j] < INF && D[j + N[i]] < INF) CD.push_back(make_pair(i, max(D[j], D[j + N[i]])));
        }
    }

    cout << (compute(ED) + compute(OD) - compute(CD) + MOD) % MOD;
}
