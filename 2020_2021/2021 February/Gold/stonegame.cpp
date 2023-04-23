#include <iostream>
#include <vector>
using namespace std;
#define MAXN 100005
#define MAXA 1000005

int N, G[MAXN], PF[MAXA];
long long R;

int main(){
    cin >> N;
    for(int i = 1; i <= N; i++) { // get group sizes & build prefix sums
        cin >> G[i];
        PF[G[i]]++;
    }
    for(int i = 1; i <= 1000000; i++) PF[i] += PF[i - 1];

    for(int i = 1; i <= 1000000; i++){ // for each i stones
        vector<int> O;
        for(int j = 1; j*i <= 1000000; j ++)  { // for each j group size
            if((PF[min(i*(j + 1) - 1, 1000000)] - PF[j*i - 1]) % 2) O.push_back(j); // add to odd if an odd number of groups with size/i = j
        }
        
        if((O.size() == 1 && O[0] == 1) || (O.size() == 2 && O[0] + 1 == O[1])) R += (long long)PF[min(i*(O.back() + 1) - 1, 1000000)] - PF[O.back()*i - 1]; // add to return value if possible
    }

    cout << R;
}
