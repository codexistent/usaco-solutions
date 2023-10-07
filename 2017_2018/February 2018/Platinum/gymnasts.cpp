#include <fstream>
#include <vector>
using namespace std;
#define MOD 1000000007

long long N, R = 0;
vector<long long> P, E;

long long pow(long long b, long long e){
    if(e == 0) return 1;
    if(e == 1) return b;

    long long r = pow(b, e / 2);

    if(e % 2) return (((r * r) % MOD) * b) % MOD;
    else return (r * r) % MOD;
}

void go(long long p, long long g, long long d, long long m){
    if(p == P.size()){
        if(g < N){
            R = (R + (pow(2, g)) * ((N / d) / g * m)) % MOD; 
        }
        return;
    }
    for(int i = 0; i < E[p]; i++){
        go(p + 1, g, d*P[p], m*(P[p] - 1));
        g *= P[p];
    }
    go(p + 1, g, d, m);
}

int main(){
    ifstream fin("gymnasts.in");
    ofstream fout("gymnasts.out");

    fin >> N;
    long long n = N;
    long long i = 2;
    for(i = 2; i*i <= N; i++){
        if(n % i == 0){
            long long e = 0;
            P.push_back(i);
            while(n % i == 0){
                n /= i;
                e++;
            }
            E.push_back(e);
        }
    }
    if(n > 1){
        P.push_back(n);
        E.push_back(1);
    }

    go(0, 1, 1, 1);
    R = (R + MOD - (N - 1) % MOD) % MOD + 1;
    fout << R << endl;
}
