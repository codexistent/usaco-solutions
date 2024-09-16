#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 100005
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

ll n, r = 1;
pair<ll, ll> arr[MAXN], sarr[MAXN];

int main(){
    ifstream cin("sort.in");
    ofstream cout("sort.out");

    cin >> n;
    FOR(i, 1, n) {
        cin >> arr[i].first;
        arr[i].second = i;
        sarr[i] = arr[i];
    }
    sort(sarr + 1, sarr + 1 + n);

    priority_queue<pair<ll, ll>> pq;
    ll v = 0;
    FOR(i, 1, n){
        pq.push({-arr[i].first, -arr[i].second});
        while(pq.size() && make_pair(-pq.top().first, -pq.top().second) <= sarr[i]){
            pq.pop();
            v++;
        }

        r = max(r, i - v);
    }

    cout << r << endl;
}
