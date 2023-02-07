#include <fstream>
#include <algorithm>
#include <set>
using namespace std;
#define MAXN 100005

class Boot {
    public:
        int id, d, s;
};
class Tile {
    public:
        int d, l, r;
};

int N, M, S = 1;
bool V[MAXN];
Boot B[MAXN];
Tile T[MAXN];
int b[MAXN], t[MAXN];
bool cmpT(int a, int b){
    return T[a].d > T[b].d;
}
bool cmpB(int a, int b) {
    return B[a].d > B[b].d;
};

int main(){
    ifstream fin("snowboots.in");
    ofstream fout("snowboots.out");
    fin >> N >> M;
    for(int i = 1; i <= N; i++) { // get tiles
        t[i] = i;
        fin >> T[i].d;
        T[i].l = i - 1;
        T[i].r = i + 1;
    }
    for(int i = 1; i <= M; i++) { // get boots
        B[i].id = b[i] = i;
        fin >> B[i].d >> B[i].s;
    }
    T[1].l = 1; T[N].r = N;
    sort(t + 1, t + 1 + N, cmpT);
    sort(b + 1, b + 1 + M, cmpB);

    int c = 1;
    for(int i = 1; i <= M; i++){
        while(c <= N && T[t[c]].d > B[b[i]].d){
            int l = T[t[c]].l;
            int r = T[t[c]].r;

            T[l].r = r;
            T[r].l = l;

            S = max(S, r - l);
            c++;
        }

        V[b[i]] = (S <= B[b[i]].s);
    }

    for(int i = 1; i <= M; i++) fout << V[i] << endl;
}
