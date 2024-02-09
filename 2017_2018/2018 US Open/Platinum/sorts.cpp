#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define ll long long

int main() {
    ifstream cin ("sort.in");
    ofstream cout ("sort.out");

    int n; cin >> n;
    pair<int, int> a[n + 2];
    FOR(i, 1, n){
        int x; cin >> x;
        a[i] = make_pair(x, i);
    }
    sort(a + 1, a + n + 1);

    int p[n + 2];
    p[0] = 0, p[n] = 0;
    FOR(i, 1, n - 1) p[i] = max(p[i - 1] + (i - 1), a[i].second) - i;

    ll r = 0;
    if(n == 1) goto retrez;

    FOR(i, 1, n) r += max(1, max(p[i - 1], p[i]));

    retrez:;
    cout << r << endl;
}
