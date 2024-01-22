#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)

int main() {
    ifstream cin("greedy.in");
    ofstream cout("greedy.out");

    int n;
    cin >> n;
    int s[n];
    FOR(i, 0, n - 1) {
        cin >> s[i]; 
        s[i] = n - s[i];
    }

    int a = 1, b = n + 1;
    while(a + 1 < b){
        int k = (a + b) / 2;

        bool v = true;
        vector<int> c(n + 1, 0);
        FOR(i, 0, k - 2) c[s[i]]++;
        int sum = 0;
        FOR(i, 1, n) sum += c[i], v &= (sum < i);
        
        if(v) a = k;
        else b = k;
    }

    cout << n - a << endl;
}
