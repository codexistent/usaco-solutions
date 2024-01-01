#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)

int main(){
    ifstream cin("cardgame.in");
    ofstream cout("cardgame.out");

    int N;
    cin >> N;
    set<int> E_R1, B_R1;
    set<int> E_R2, B_R2;
    FOR(i, 1, N / 2){
        int x;
        cin >> x;
        E_R1.insert(-x);
    }
    FOR(i, N / 2 + 1, N){
        int x;
        cin >> x;
        E_R2.insert(x);
    }
    int b = 1;
    while(b <= 2*N && B_R2.size() < N / 2){
        if(E_R1.find(-b) == E_R1.end() && E_R2.find(b) == E_R2.end()) {
            B_R2.insert(b);
        }
        b++;
    }
    while(b <= 2*N){
        if(E_R1.find(-b) == E_R1.end() && E_R2.find(b) == E_R2.end()) {
            B_R1.insert(-b);
        }
        b++;
    }

    int R = 0;
    for(int i : E_R1){
        if(-i < -(*B_R1.begin())){
            R++;
            B_R1.erase(B_R1.begin());
        }
    }
    for(int i : E_R2){
        if(i > *B_R2.begin()){
            R++;
            B_R2.erase(B_R2.begin());
        }
    }
    cout << R << endl;
}
