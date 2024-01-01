#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i, a, b) for(int i = a; i <= b; i++)

const map<char, pair<int, int>> dir = {{'N', {0, 1}}, {'E', {1, 0}}, {'S', {0, -1}}, {'W', {-1, 0}}};

ll dist(pair<int, int> a, pair<int, int> b){
    return (ll)(a.first - b.first) * (a.first - b.first) + (ll)(a.second - b.second) * (a.second - b.second);
}

int main(){
    ifstream cin ("radio.in");
    ofstream cout ("radio.out");

    int N, M;
    cin >> N >> M;
    pair<int, int> FJ[N + 1], B[M + 1];
    string fjM, bM;
    cin >> FJ[0].first >> FJ[0].second >> B[0].first >> B[0].second;
    cin >> fjM >> bM;

    FOR(i, 1, N){
        FJ[i].first = FJ[i - 1].first + dir.at(fjM[i - 1]).first;
        FJ[i].second = FJ[i - 1].second + dir.at(fjM[i - 1]).second;
    }
    FOR(i, 1, M){
        B[i].first = B[i - 1].first + dir.at(bM[i - 1]).first;
        B[i].second = B[i - 1].second + dir.at(bM[i - 1]).second;
    }

    ll DP[N + 1][M + 1];
    FOR(i, 0, N) FOR(j, 0, M) DP[i][j] = LONG_LONG_MAX;

    DP[0][0] = 0;
    FOR(fj, 0, N) FOR(b, 0, M) {
        if(fj != 0){
            DP[fj][b] = min(DP[fj][b], DP[fj - 1][b]);
        }
        if(b != 0){
            DP[fj][b] = min(DP[fj][b], DP[fj][b - 1]);
        }
        if(fj != 0 && b != 0){
            DP[fj][b] = min(DP[fj][b], DP[fj - 1][b - 1]);
        }
        DP[fj][b] += dist(FJ[fj], B[b]);
    }

    cout << DP[N][M] - dist(FJ[0], B[0]) << endl;
}
