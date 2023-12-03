#include <bits\stdc++.h> 
using namespace std;
#define MAXN 200005
#define FOR(i, a, b) for(int i = a; i <= b; i++)

int N, P[MAXN] /* P[n] = representative node of n */, S[MAXN] /*size of group*/;

int find(int x){
    return P[x] == x ? x : P[x] = find(P[x]);
}

bool onion(int a, int b){
    a = find(a), b = find(b);
    if(a == b) return false;

    if(S[a] < S[b]) swap(a, b);
    S[a] += S[b];
    P[a] = P[b] = a;
    return true;
}

int main(){
  cin >> N;
  for(int i = 0; i < N; i++) P[i] = i, S[i] = 1;
}
