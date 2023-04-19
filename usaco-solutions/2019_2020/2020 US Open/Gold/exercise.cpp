#include <fstream>
using namespace std;
#define MAXN 10005

long long N, M, DP[MAXN];
bool C[MAXN]; // C[i] = stores if i is composite

int main(){
    ifstream cin("exercise.in");
	ofstream cout("exercise.out");
    
    cin >> N >> M;
    fill(DP, DP + MAXN - 1, 1);
    for(long long p = 2; p <= N; p++){
        if(C[p]) continue;
        // p is prime
        for(long long j = N, p2 = p; 1 <= j; j--, p2 = p){
            while(p2 <= j){
                DP[j] += DP[j - p2] * p2 % M, DP[j] %= M;
                p2 *= p;
            }
        }
        
        // update C[] for all multiples of p
        for(long long j = p * p; j <= N; j += p) C[j] = true;
    }

    cout << DP[N];
}
