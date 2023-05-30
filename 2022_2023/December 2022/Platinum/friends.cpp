#include <iostream>
#include <set>
using namespace std;
#define MAXN 200005

int N, M;
long long T;
set<int> F[MAXN]; // F[i] = friends of cow i sorted by smallest->largest id

int main(){
    cin >> N >> M;
    for(int i = 1, a, b; i <= M; i++){ // get edges(aka friendships) & group friends
        cin >> a >> b;
        if(a > b) swap(a, b); // make only one edge from smaller to larger node to prevent overcounting
        F[a].insert(b);
    }

    T = -M; // set total = -M so we account for initial friendships
    for(int i = 1; i <= N; i++){ // for each cow i
        T += F[i].size(); // add total # friends cow i has at time of departure(this includes all initial and newly made friendships)
        // note we don't need to add all new friendships from cow i's departure because friendships will 'carry' as cows leave
        if(F[i].size()){ // if cow i has friends, account for new friendships
            int j = *F[i].begin(); // j = ith cow’s smallest-indexed friend
            F[i].erase(j);

            if(F[i].size() > F[j].size()) swap(F[i], F[j]);  // always merge smaller with larger to ensure no TLE
            for(int k : F[i]){ // merge
                F[j].insert(k);
            }
        }
    }

    cout << T; // print answer
}
