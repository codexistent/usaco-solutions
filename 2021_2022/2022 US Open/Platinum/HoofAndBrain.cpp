#include <iostream>
#include <set>
#include <stack>
using namespace std;
#define MAXMN 200005

struct Edge {
    int a, b;
};

int N, M, Q, G[MAXMN];
bool DE[MAXMN], V[MAXMN], DEC[MAXMN];
Edge E[MAXMN];
set<int> C[MAXMN], P[MAXMN];
stack<int> S;

int find(int x){ // dsu find
    return (G[x] == x) ? x : (G[x] = find(G[x]));
}

void onion(int a, int b) { // dsu union
    int A = find(a), B = find(b);
    if(A == B) return;

    if(P[A].size() > P[B].size()) swap(A, B);

    for(int p : P[A]){

        C[p].erase(A);
        C[p].insert(B);
        if(C[p].size() == 1) {
            P[B].erase(p);
            S.push(p);
        }else{
            P[B].insert(p);
        }
    }

    G[a] = G[b] = G[A] = G[B] = B;
}

int main(){
    // STEP 1) GET/SET DATA
    cin >> N >> M;
    for(int i = 1; i <= M; i++) {
        cin >> E[i].a >> E[i].b;
        C[E[i].a].insert(E[i].b);
        P[E[i].b].insert(E[i].a);
        G[i] = i;
    }

    // STEP 2) MARK DEAD-END NODES
    fill(V, V + MAXMN - 1, false);
    for(int i = 1; i <= N; i++) if(C[i].size() == 0) S.push(i);

    while(!S.empty()){
        int n = S.top(); S.pop();
        if(V[n]) continue;

        DE[n] = true;

        for(int p : P[n]) {
            C[p].erase(n);
            if(C[p].size() == 0) S.push(p);
        }
    }

    // STEP 3) MERGE CYCLES
    for(int i = 1; i <= N; i++) if(C[i].size() == 1) S.push(i);

    while(!S.empty()){
        int n = S.top(); S.pop();
        onion(n, *C[n].begin());
    }


    // STEP 4) GET ANSWERS
    cin >> Q;

    for(int i = 1, a, b; i <= Q; i++) {
        cin >> a >> b;
        if(DE[a] || DE[b] || find(a) == find(b)) {
            cout << "B";
        } else {
            cout << "H";
        }
    }
    cout << endl;
}
