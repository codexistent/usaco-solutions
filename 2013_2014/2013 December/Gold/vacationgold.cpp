#include <bits/stdc++.h>
using namespace std;
#define MAXN 20005
#define MAXK 205
#define ll long long
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define f first
#define s second

ll n, m, k, q, dist[2][MAXK][MAXN], h[MAXN];
vector<pair<ll, ll> > e[2][MAXN];

int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

	freopen("vacationgold.in", "r", stdin);
	freopen("vacationgold.out", "w", stdout);

    cin >> n >> m >> k >> q;
    FOR(i, 1, m){
        ll a, b, d;
        cin >> a >> b >> d;
        e[0][b].push_back({a, d});
        e[1][a].push_back({b, d});
    }
    FOR(i, 1, k) cin >> h[i];

    priority_queue<pair<ll, ll> > pq;
    FOR(c, 0, 1){
        FOR(i, 1, k){
            FOR(j, 1, n) dist[c][i][j] = -1;
            dist[c][i][h[i]] = 0;

            pq.push({0, h[i]});
            while(!pq.empty()){
                auto pqi = pq.top(); pq.pop();
                if(-dist[c][i][pqi.s] != pqi.f) continue;

                for(auto ei : e[c][pqi.s]){
                    if(dist[c][i][ei.f] == -1 || dist[c][i][ei.f] > dist[c][i][pqi.s] + ei.s){
                        dist[c][i][ei.f] = dist[c][i][pqi.s] + ei.s;
                        pq.push({-dist[c][i][ei.f], ei.f});
                    }
                }
            }
        }
    }

    pair<ll, ll> r = {0, 0};
    FOR(i, 1, q){
        ll a, b, mn = -1; cin >> a >> b;
        FOR(j, 1, k){
            if(dist[0][j][a] != -1 && dist[1][j][b] != -1){
                if(mn == -1 || dist[0][j][a] + dist[1][j][b] < mn){
                    mn = dist[0][j][a] + dist[1][j][b];
                }
            }
        }

        if(mn != -1){
            r.f++;
            r.s += mn;
        }
    }

    cout << r.f << endl;
    cout << r.s << endl;
}
