#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;
#define STDN 100001
#define MAXN 1000000001;

ofstream fout("piepie.out");
ifstream fin("piepie.in");

// ENUMS
enum Owner { BESSIE, ELSIE };

// CLASSES
class Pie{
    public:
        int id;
        int br, er;
        Owner o; 
};

Pie P[STDN * 2];

// STRUCTS
struct bCmp {
	bool operator()(int a, int b) const {
		return P[a].br > P[b].br;
	}
};

struct eCmp {
	bool operator()(int a, int b) const {
		return P[a].er > P[b].er;
	}
};

// VARIABLES
int N, D;
int BFS[STDN * 2];
multiset<int, eCmp> BC;
multiset<int, bCmp> EC;
queue<int> Q;

int main(){
    // get and set data
    fin >> N >> D;

    fill(BFS, BFS + STDN * 2 - 1, -1);
    
    for(int i = 0; i < N; i++){
        P[i].id = i;
        fin >> P[i].br >> P[i].er;
        P[i].o = BESSIE;

        if(P[i].er == 0){
            BFS[i] = 1;
            Q.push(i);
        }else{
            BC.insert(i);
        }
    }
    for(int i = N; i < N*2; i++){
        P[i].id = i;
        fin >> P[i].br >> P[i].er;
        P[i].o = ELSIE;

        if(P[i].br == 0){
            BFS[i] = 1;
            Q.push(i);
        }else{
            EC.insert(i);
        }
    }

    // do bfs
    while(!Q.empty()){
        int q = Q.front();
        Q.pop();

        if(q < N){ // bessie's pie
            auto it = EC.lower_bound(P[q].id);
            while(!EC.empty() && it != EC.end()){
                Pie p = P[*it];
                if(p.br < P[q].br - D) break;
                BFS[p.id] = BFS[P[q].id] + 1;
                Q.push(p.id);
                EC.erase(it);
                it = EC.lower_bound(P[q].id);
            }
        }else{
            auto it = BC.lower_bound(P[q].id);
            while(!BC.empty() && it != BC.end()){
                Pie p = P[*it];
                if(p.er < P[q].er - D) break;
                BFS[p.id] = BFS[P[q].id] + 1;
                Q.push(p.id);
                BC.erase(it);
                it = BC.lower_bound(P[q].id);
            }
        }
    }

    for(int i = 0; i < N; i++){
        fout << BFS[i] << endl;
    }
}
