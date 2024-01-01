#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)

int N, M;

const int dir[4][2] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}
};

bool inbounds(int x, int y){
    return (1 <= x && x <= N) && (1 <= y && y <= M);
}

bool setmax(int &a, int b){
    a = min(a, b);
    return (a == b);
}

// when we transition, there are at most 4 states?

int main(){
    ifstream cin("dream.in");
    ofstream cout("dream.out");

    cin >> N >> M;
    int T[N + 1][M + 1];
    int R = INT_MAX;
    FOR(i, 1, N) FOR(j, 1, M) cin >> T[i][j];

    int D[N + 1][M + 1][2][2][4];
    bool V[N + 1][M + 1][2][2][4];
    FOR(i, 1, N) FOR(j, 1, M) FOR(k, 0, 1) FOR(l, 0, 1) FOR(m, 0, 3) D[i][j][k][l][m] = INT_MAX, V[i][j][k][l][m] = false;
    D[1][1][0][0][0] = 0;
    
    priority_queue<tuple<int, int, int, bool, bool, int>, vector<tuple<int, int, int, bool, bool, int>>, greater<tuple<int, int, int, bool, bool, int>>> PQ;
    PQ.push(make_tuple(0, 1, 1, 0, 0, 0));
    while(!PQ.empty()){
        auto pq = PQ.top();
        int x = get<1>(pq), y = get<2>(pq), o = get<3>(pq), p = get<4>(pq), pd = get<5>(pq);
        int d2 = D[x][y][o][p][pd] + 1;
        PQ.pop();

        if(x == N && y == M) R = min(R, D[x][y][o][p][pd]);

        if(V[x][y][o][p][pd]) continue;
        V[x][y][o][p][pd] = true;

        if(p){
            int x2 = x + dir[pd][0], y2 = y + dir[pd][1];
            if(inbounds(x2, y2) && (T[x2][y2] == 1 || T[x2][y2] == 2)){
                // discountine slide
                if(setmax(D[x2][y2][T[x2][y2] == 2][0][0], d2)){
                    PQ.push(make_tuple(d2, x2, y2, T[x2][y2] == 2, 0, 0));
                }
                continue;
            }else if(inbounds(x2, y2) && T[x2][y2] == 4){
                if(setmax(D[x2][y2][0][p][pd], d2)){
                    PQ.push(make_tuple(d2, x2, y2, 0, p, pd));
                }
                continue;
            }
        }

        FOR(i, 0, 3) {
            int x2 = x + dir[i][0], y2 = y + dir[i][1];
            if(inbounds(x2, y2)){
                if(T[x2][y2] == 1){
                    if(setmax(D[x2][y2][o][0][0], d2)){
                        PQ.push(make_tuple(d2, x2, y2, o, 0, 0));
                    }
                }else if(T[x2][y2] == 2){
                    if(setmax(D[x2][y2][1][0][0], d2)){
                        PQ.push(make_tuple(d2, x2, y2, 1, 0, 0));
                    }
                }else if(T[x2][y2] == 3 && o){
                    if(setmax(D[x2][y2][o][0][0], d2)){
                        PQ.push(make_tuple(d2, x2, y2, o, 0, 0));
                    }
                }else if(T[x2][y2] == 4){
                    if(setmax(D[x2][y2][0][1][i], d2)){
                        PQ.push(make_tuple(d2, x2, y2, 0, 1, i));
                    }
                }
            }
        }
    }

    cout << (R == INT_MAX ? -1 : R) << endl;
}
