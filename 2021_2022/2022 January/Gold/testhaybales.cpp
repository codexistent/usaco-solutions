#include <iostream>
#include <vector>
#include <set>
using namespace std;
#define MAXN 100005

long long N, X;
bool V[MAXN];
set<long long> C[MAXN], R; 

void dfs(long long i, long long h){
    if(V[i]) return;
    V[i] = true;

    if(i != N + 1) R.insert((N + 1)*h + (X--));
    for(int c : C[i]) dfs(N + 1 - c, h - 1);
}

int main(){
    // [1 : GET DATA/BUILD GRAPH]
    cin >> N;
    X = N - 1;
    for(long long i = 1, j; i <= N; i++) {
        cin >> j;
        C[j+1].insert(N + 1 - i);
    }

    // [2 : DFS]
    dfs(N + 1, N + 1);

    // [3 : PRINT ANSWER]
    cout << N + 1 << endl;
    for(long long i : R) cout << i << endl;
}
