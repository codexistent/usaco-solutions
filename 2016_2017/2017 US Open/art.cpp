#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define f first
#define s second
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair

void setmin(int& a, int b) { a = min(a, b); }
void setmax(int& a, int b) { a = max(a, b); }

int main(){
    ifstream cin("art.in");
    ofstream cout("art.out");

    int N;
    cin >> N;
    int A[N + 1][N + 1];
    pair<pii, pii> B[N * N + 1];
    set<int> V;
    FOR(i, 1, N) FOR(j, 1, N) {
        cin >> A[i][j];
        if(A[i][j] == 0) continue;
        if(V.find(A[i][j]) == V.end()) B[A[i][j]] = mp(mp(i, j), mp(i, j));
        V.insert(A[i][j]);
        setmin(B[A[i][j]].f.f, i), setmin(B[A[i][j]].f.s, j);
        setmax(B[A[i][j]].s.f, i), setmax(B[A[i][j]].s.s, j);
    }

    int PFX[N + 2][N + 2];
    FOR(i, 0, N + 1) FOR(j, 0, N + 1) PFX[i][j] = 0;
    for(int v : V) {
        PFX[B[v].f.f][B[v].f.s]++;
        PFX[B[v].f.f][B[v].s.s + 1]--;
        PFX[B[v].s.f + 1][B[v].f.s]--;
        PFX[B[v].s.f + 1][B[v].s.s + 1]++;
    }

    FOR(i, 1, N){
        FOR(j, 1, N){
            PFX[i][j] += PFX[i - 1][j] + PFX[i][j - 1] - PFX[i - 1][j - 1];
        }
    }

    int R = N * N - V.size();
    if(V.size() == 1) V.erase(V.begin());
    FOR(i, 1, N){
        FOR(j, 1, N) if(A[i][j] != 0){
            if(PFX[i][j] > 1) V.erase(A[i][j]);
        }
    }    

    cout << R + V.size() << endl;
}
