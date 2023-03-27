#include <iostream>
using namespace std;

#define MAXN 200005
#define pair pair<int, int>
#define a first
#define b second
#define mp make_pair

int N, C[MAXN];
pair DP[2][7];
string S, B = " bessie";

int next(int x) {
    return (x == 6) ? 1 : x + 1; 
}
int prev(int x) {
    return (x == 1) ? 6 : x - 1; 
}
void set_max(pair &p, int new_a, int new_b){
    if(new_a == -1) return;
    if(p.a < new_a || (p.a == new_a && p.b > new_b)){
        p.a = new_a;
        p.b = new_b;
    }
}

int main(){
    cin >> S;
    N = S.length();
    S = " " + S;
    for(int i = 1; i <= N; i++) cin >> C[i];
    for(int i = 0; i <= 6; i++) DP[0][i].a = DP[1][i].a = -1;

    DP[0][6] = mp(0, 0);
    for(int i = 1; i <= N; i++){
        for(int j = 0; j <= 6; j++) DP[i % 2][j].a = -1;
        for(int j = 1; j <= 5; j++){
            // add a character
            if(S[i] == B[j]) {
                set_max(DP[i % 2][j], DP[(i - 1) % 2][prev(j)].a, DP[(i - 1) % 2][prev(j)].b);
            } 
            // don't add a character
            set_max(DP[i % 2][j], DP[(i - 1) % 2][j].a, DP[(i - 1) % 2][j].b + C[i]);
        }
        // -> current character = 6
        // add a character
        if(S[i] == 'e') {
            if(DP[(i - 1) % 2][5].a != -1) set_max(DP[i % 2][6], DP[(i - 1) % 2][5].a + 1, DP[(i - 1) % 2][5].b);
        }
        // don't add a character
        set_max(DP[i % 2][6], DP[(i - 1) % 2][6].a, DP[(i - 1) % 2][6].b);
    }

    cout << max(DP[N % 2][6].a, 0) << endl;
    cout << DP[N % 2][6].b;
}
