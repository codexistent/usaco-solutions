#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define f first
#define s second
#define mp make_pair
#define ll long long

int D[2], P[4006005], S[4006005];
ll R = 0;

int hsh(int i, int j) {
    return i * (D[1] + 1) + j;
}

int find(int x){
    return (P[x] == x) ? x : (P[x] = find(P[x]));
}

bool dsu(int a, int b){
    a = find(a), b = find(b);
    if(a == b) return false;

    if(S[a] < S[b]) swap(a, b);

    S[a] += S[b];
    P[a] = P[b] = a;
    return true;
}

int main(){
    ifstream cin ("fencedin.in");
    ofstream cout ("fencedin.out");

    int A, B, F[2][2005];
    cin >> A >> B >> D[0] >> D[1];
    F[0][0] = F[1][0] = 0, F[0][D[0] + 1] = A, F[1][D[1] + 1] = B;
    FOR(d, 0, 1) {
        FOR(i, 1, D[d]) cin >> F[d][i];
        sort(F[d], F[d] + D[d] + 1);
    }

    FOR(i, 1, D[0] + 1) FOR(j, 1, D[1] + 1) P[hsh(i, j)] = hsh(i, j), S[hsh(i, j)] = 1;

    pair<int, int> pq[2][2005];
    FOR(d, 0, 1){
        FOR(i, 1, D[d] + 1){
            pq[d][i - 1] = mp(F[d][i] - F[d][i - 1], i);
        }
        sort(pq[d], pq[d] + D[d] + 1);
    }

    FOR(d, 0, 1){
        FOR(i, 1, D[d] + 1){
            pq[d][i - 1] = mp(F[d][i] - F[d][i - 1], i);
        }
        sort(pq[d], pq[d] + D[d] + 1);
    }

    ll R = 0;
    int ptr[2] = {0, 0};
    while(ptr[0] != D[0] + 1 || ptr[1] != D[1] + 1){
        int d = (ptr[0] == D[0] + 1) ? 1 : (ptr[1] == D[1] + 1) ? 0 : (pq[0][ptr[0]].f > pq[1][ptr[1]].f) ? 1 : 0;
        int w = pq[d][ptr[d]].f, m = pq[d][ptr[d]].s;
        ptr[d]++;

        FOR(i, 1, D[!d]){
            if(d == 0){
                R += w*dsu(hsh(m, i), hsh(m, i + 1));
            }else{
                R += w*dsu(hsh(i, m), hsh(i + 1, m));
            }
        }
    }
    
    cout << R << endl;
}
