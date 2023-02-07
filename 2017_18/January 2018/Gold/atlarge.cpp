#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define MAXN 100005

int N, K;
int B[MAXN], L[MAXN];
vector<int> E[MAXN];
bool R[MAXN];

bool v1[MAXN], v2[MAXN];

struct cmpBFS {
   bool operator()(int a, int b){
      return L[a] > L[b];
   }
};

void dfsB(int i){
    if(v1[i]) return;
    v1[i] = true;

    for(int e : E[i]){
        if(v1[e]) continue;
        B[e] = B[i] + 1;
        dfsB(e);
    }
}

int main(){
    ifstream fin("atlarge.in");
    ofstream fout("atlarge.out");

    // get data
    fin >> N >> K;
    for(int i = 1; i < N; i++){
        int a, b;
        fin >> a >> b;
        E[a].push_back(b);
        E[b].push_back(a);
    }
    
    // find distance from each node to bessie; dfs
    fill(B, B + MAXN - 1, MAXN);
    B[K] = 0;
    dfsB(K);

    // find distance from each node to nearest leaf; bfs
    fill(L, L + MAXN - 1, MAXN);
    priority_queue<int, vector<int>, cmpBFS> pq;
    for(int i = 1; i <= N; i++) {
        if(E[i].size() == 1) {
            L[i] = 0;
            pq.push(i);
        }
    }
    while(!pq.empty()){
        int n = pq.top();
        pq.pop();
        if(v2[n]) continue;
        v2[n] = true;

        for(int e : E[n]){
            if(v2[e]) continue;
            L[e] = min(L[e], L[n] + 1);
            pq.push(e);
        }
    }

    // check if bessie can reach each node before farmer
    for(int i = 1; i <= N; i++) R[i] = (B[i] < L[i]);

    // get number of edges connecting reachable nodes from unreachable nodes
    int C = 0;
    for(int i = 1; i <= N; i++) if(R[i]) for(int e : E[i]) C += (!R[e]);

    fout << C << endl;
}
