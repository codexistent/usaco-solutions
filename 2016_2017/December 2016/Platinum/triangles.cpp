#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(long long i = a; i <= b; i++)
#define pii pair<long long, long long>
#define f first
#define s second
#define x first
#define y second
#define mp make_pair

bool lower(pii i, pii j, pii k){
    if(i.f > j.f) swap(i, j);
    long long cross = (i.first - j.first)*(k.second - j.second) - (k.first - j.first)*(i.second - j.second);

    return cross > 0;
}

int main(){
    ifstream cin ("triangles.in");
    ofstream cout ("triangles.out");

    long long N;
    cin >> N;
    pair<long long, long long> P[N];
    FOR(i, 0, N - 1) cin >> P[i].first >> P[i].second;
    sort(P, P + N);

    long long B[N][N];
    FOR(i, 0, N - 1){
        FOR(j, i + 1, N - 1){
            B[i][j] = 0;
            FOR(k, i + 1, j - 1){
                B[i][j] += lower(P[i], P[j], P[k]);
            }
        }
    }

    long long R[N - 2];
    fill(R, R + N - 2, 0);
    FOR(i, 0, N - 1){
        FOR(j, i + 1, N - 1){
            FOR(k, j + 1, N - 1) {
                long long r = B[i][k] - B[i][j] - B[j][k];

                if(r > 0){
                    r--;
                }else if(r < 0) r = -r;

                R[r]++;
            }
        }
    }

    for(long long i : R) cout << i << endl;
}
