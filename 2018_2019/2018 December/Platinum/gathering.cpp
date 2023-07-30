#include <fstream>
#include <vector>
#include <set>
#include <tuple>
using namespace std;
#define MAXN 100005

int N, M, S;
bool R[MAXN] = {0}, V[MAXN] = {0};
vector<int> E[MAXN], A[MAXN], B[MAXN];
set<int> e[MAXN], a[MAXN];

void reset(){
    // edges
    for(int i = 1; i <= N; i++) for(int j : E[i]) e[i].erase(j);
    for(int i = 1; i <= N; i++) for(int j : E[i]) e[i].insert(j);

    // a's
    for(int i = 1; i <= N; i++) for(int j : A[i]) a[i].erase(j);
    for(int i = 1; i <= N; i++) for(int j : A[i]) a[i].insert(j);
}

struct tupleComp {
    bool operator()(const tuple<int, int, int>& x, const tuple<int, int, int>& y) const {
        if (get<1>(x) != get<1>(y)) {
            return get<1>(x) < get<1>(y); // sort by leafs
        } else {
            return get<2>(x) < get<2>(y); // sort by conditions next
        }
    }
};

multiset<tuple<int, int, int>, tupleComp> C;

void dfs(int n){
    if(V[n]) return;
    V[n] = true;

    R[n] = true;
    for(int i : E[n]) {
        if(B[i].size() == 0) {
            dfs(i);
        }
    }
}

int main(){
    ifstream cin("gathering.in");
    ofstream cout("gathering.out");

    cin >> N >> M;
    for(int i = 2, a, b; i <= N; i++) {
        cin >> a >> b;
        E[a].push_back(b);
        E[b].push_back(a);
    }
    for(int i = 1, a, b; i <= M; i++){
        cin >> a >> b;
        A[b].push_back(a);
        B[a].push_back(b);
    }

    reset();

    for(int i = 1; i <= N; i++) C.insert(make_tuple(i, e[i].size(), a[i].size()));

    for(int i = 1; i <= N; i++){
        S = get<0>(*C.begin());
        if(!(get<1>(*C.begin()) <= 1 && get<2>(*C.begin()) <= 0)){
            for(int i = 1; i <= N; i++) cout << 0 << endl;
            return 1;
        }
        C.erase(C.begin());
        for(int j : e[S]) {
            e[j].erase(S);
            C.insert(make_tuple(j, e[j].size(), a[j].size()));
        }

        for(int j : B[S]){
            a[j].erase(S);
            C.insert(make_tuple(j, e[j].size(), a[j].size()));
        }
    }

    for(int i = 1; i <= N; i++) R[i] = false;
    dfs(S);
    for(int i = 1; i <= N; i++) cout << R[i] << endl;
}
