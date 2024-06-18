#include <fstream>
#include <algorithm>
#include <utility>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define MAXN 100005
#define MAXC 1000005
#define x first
#define y second

int n, st[2][MAXC * 4], r;
pair<int, int> c[MAXN];

int qry(int ST, int idx, int a, int b, pair<int, int> rng){
    if(rng.second < a || b < rng.first) return 0;
    if(rng.first <= a && b <= rng.second) return st[ST][idx];

    return qry(ST, idx * 2, a, (a + b) / 2, rng) + qry(ST, idx * 2 + 1, (a + b) / 2 + 1, b, rng);
}

void upd(int ST, int idx, int a, int b, int ch, int chv){
    if(ch < a || b < ch) return;
    if(a == b){
        st[ST][idx] += chv;
    }else{
        upd(ST, idx * 2, a, (a + b) / 2, ch, chv);
        upd(ST, idx * 2 + 1, (a + b) / 2 + 1, b, ch, chv);
        st[ST][idx] += chv;
    }
}

int getR(int yline, int ln, int rn){
    if(yline < 0 || 1000000 < yline) return n;
    return max(max(qry(0, 1, 1,1000000, make_pair(0, yline)), ln - qry(0, 1, 1,1000000, make_pair(0, yline))), 
                max(qry(1, 1, 1,1000000, make_pair(0, yline)), rn - qry(1, 1, 1,1000000, make_pair(0, yline))));
}

int main(){
    ifstream cin("balancing.in");
    ofstream cout("balancing.out");

    FOR(i, 0, MAXC * 4 - 1) st[0][i] = st[1][i] = 0;

    cin >> n; r = n;
    FOR(i, 1, n){
        cin >> c[i].x >> c[i].y;
        upd(1, 1, 1, 1000000, c[i].y, 1);
    }
    sort(c + 1, c + 1 + n);

    int line = 0;
    while(line <= n){
        FOR(i, 1, 10){
            r = min(r, getR(i, line, n - line));
        }

        if(max(line, n - line) >= 2 * min(line, n - line)){
            r = min(r, (max(line, n - line) + 1) / 2);
        }else{
            int lo = 0, hi = 1000000;

            while(lo < hi){
                int m = (hi + lo) / 2;
                if((line + 1) / 2 <= qry(0, 1, 1, 1000000, make_pair(0, m))){
                    hi = m;
                }else{
                    lo = m + 1;
                }
            }

            int a = hi;
            r = min(r, min(getR(a, line, n - line), min(getR(a - 1, line, n - line), getR(a + 1, line, n - line))));

            lo = 0, hi = 1000000;
            while(lo < hi){
                int m = (hi + lo) / 2;
                if(((n - line)) / 2 <= qry(1, 1, 1,1000000, make_pair(0, m))){
                    hi = m;
                }else{
                    lo = m + 1;
                }
            }
            int b = hi;
            r = min(r, min(getR(b, line, n - line), min(getR(b - 1, line, n - line), getR(b + 1, line, n - line))));

            int rline = n - line;
            if(a < b) {
                int m = (a + b + 1) / 2;
                if(max(line - qry(0, 1, 1,1000000, make_pair(0, m)), qry(0, 1, 1,1000000, make_pair(0, m))) <= max(qry(1, 1, 1,1000000, make_pair(0, m)), rline - qry(1, 1, 1,1000000, make_pair(0, m)))){
                    a = m;
                }else{
                    b = m - 1;
                }
            }else{
                swap(a, b);

                while(a < b){
                    int m = (a + b + 1) / 2;
                    if(max(line - qry(0, 1, 1,1000000, make_pair(0, m)), qry(0, 1, 1,1000000, make_pair(0, m))) >= max(qry(1, 1, 1,1000000, make_pair(0, m)), rline - qry(1, 1, 1,1000000, make_pair(0, m)))){
                        a = m;
                    }else{
                        b = m - 1;
                    }
                }
            }
            r = min(r, min(getR(a, line, n - line), min(getR(a - 1, line, n - line), getR(a + 1, line, n - line))));
        }

        if(line == n) break;
        int nx = c[line + 1].x;
        while(c[line + 1].x == nx){
            upd(0, 1, 1,1000000, c[line + 1].y, 1);
            upd(1, 1, 1,1000000, c[line + 1].y, -1);
            line++;
        }
    }

    cout << r << endl;
}
