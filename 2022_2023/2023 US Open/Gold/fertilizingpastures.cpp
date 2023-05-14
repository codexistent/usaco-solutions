#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
using namespace std;
#define MAXN 200005

long long N, T, DP[MAXN], DP2[MAXN], a[MAXN], A[MAXN], S[MAXN], R[MAXN], MAXR; // A[i] = sum of a's for nodes in subtree i, S[i] = # nodes in subtree i, R[i] = max. depth of any node in subtree i to root, MAXR = max depth
bool V[MAXN];
vector<long long> C[MAXN]/*C[i] = children of node i*/;

void dfs(int n, int r){
    if(V[n]) return;
    long long dp[C[n].size() + 1], sfxA[C[n].size() + 2], ss = 0;
    vector<pair<double, long long> > c; 
    V[n] = true, MAXR = max(MAXR, R[n] = r), S[n] = 1, sfxA[C[n].size() + 1] = dp[0] = 0, DP2[n] = (C[n].size() == 0) ? 0 : LONG_MAX;;

    for(long long i : C[n]){
        dfs(i, r + 1);
        A[n] += A[i], S[n] += S[i], R[n] = max(R[n], R[i]);
        c.push_back(make_pair((double)S[i]/A[i], i));
    }
    sort(c.begin(), c.end()); // sort children by (subtree size / subtree a sum)

    // when T = 0, use DP[]
    for(int i = 1; i <= C[n].size(); i++){
        dp[i] = dp[i - 1] + DP[c[i - 1].second] + A[c[i - 1].second] * (1 + 2 * ss);
        ss += S[c[i - 1].second];
    }
    DP[n] = dp[C[n].size()];

    // when T = 1, use DP2[]
    for(int i = C[n].size(); 1 <= i; i--) sfxA[i] = sfxA[i + 1] + A[c[i - 1].second]; // suffix of a sums for node n's children
    for(int i = 1; i <= C[n].size(); i++) if(R[c[i - 1].second] == MAXR) DP2[n] = min(DP2[n], dp[i - 1] + (DP2[c[i - 1].second] + A[c[i - 1].second] * (1 + 2 * (ss - S[c[i - 1].second]))) + ((dp[C[n].size()] - dp[i]) - 2 * sfxA[i + 1] * S[c[i - 1].second]));
}

int main(){
    cin >> N >> T; // get and set data
    for(int i = 2, p; i <= N; i++) {
        cin >> p >> a[i];
        C[p].push_back(i), A[i] = a[i];
    }

    dfs(1, 0);

    if(T == 0) cout << 2*(N - 1) << " " << DP[1] << endl;
    else cout << 2*(N - 1) - MAXR << " " << DP2[1] << endl;
}
