#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 100005

class Edge {
    public:
        int a, b, w;
};
class Query {
    public:
        int k, v, id;
};

int N, M, P[MAXN], S[MAXN], R[MAXN];
Edge E[MAXN];
Query Q[MAXN];

bool cmpE (Edge a, Edge b) {
    return a.w > b.w; // largest first
}
bool cmpQ (Query a, Query b) {
    return a.k > b.k; // largest first
}

int find(int x){
    return (P[x] == x) ? x : (P[x] = find(P[x]));
}
void onion(int a, int b){
    int A = find(a), B = find(b);

    if(S[A] > S[B]){
        S[A] += S[B];
        P[A] = P[B] = P[a] = P[b] = A;
    }else{
        S[B] += S[A];
        P[A] = P[B] = P[a] = P[b] = B;
    }
}

int main(){
    cin >> N >> M;
    for(int i = 1; i <= N - 1; i++) cin >> E[i].a >> E[i].b >> E[i].w;
    for(int i = 1; i <= N; i++){
        P[i] = i;
        S[i] = 1;
    }
    for(int i = 1; i <= M; i++) {
        Q[i].id = i;
        cin >> Q[i].k >> Q[i].v;
    }
    sort(E + 1, E + 1 + N, cmpE);
    sort(Q + 1, Q + 1 + M, cmpQ);

    for(int i = 1, j = 1; i <= M; i++){
        while(j < N && Q[i].k <= E[j].w) {
            onion(E[j].a, E[j].b);
            j++;
        }

        R[Q[i].id] = S[find(Q[i].v)] - 1;
    }

    for(int i = 1; i <= M; i++) cout << R[i] << endl;
}
