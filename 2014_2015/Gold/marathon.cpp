#include <fstream>
#include <math.h>
using namespace std;
#define MAXN 100005
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define pii pair<int, int>
#define f first 
#define s second

int n, q, stp[MAXN * 4], str[MAXN * 4];
pii p[MAXN];

int dist(int i, int j){
    return abs(p[i].f - p[j].f) + abs(p[i].s - p[j].s);
}

// stp helpers
void buildp(int index, int a, int b){
    if(a == b || a + 1 == b){
        stp[index] = dist(a, b);
        return;
    }
    buildp(index * 2, a, (a + b) / 2);
    buildp(index * 2 + 1, (a + b) / 2, b);
    stp[index] = stp[index * 2] + stp[index * 2 + 1];
}

void updp(int index, int a, int b, int ch){
    if(a + 1 == b && (a == ch || b == ch)){
        stp[index] = dist(a, b);
        return;
    }
    if(ch < a || b < ch || a >= b) return;
    updp(index * 2, a, (a + b) / 2, ch);
    updp(index * 2 + 1, (a + b) / 2, b, ch);
    stp[index] = stp[index * 2] + stp[index * 2 + 1];
}

int qryp(int index, int a, int b, int qa, int qb){
    if(qa <= a && b <= qb) return stp[index];
    if(qb <= a || b <= qa || a == b) return 0;
    return qryp(index * 2, a, (a + b) / 2, qa, qb) + qryp(index * 2 + 1, (a + b) / 2, b, qa, qb);
}

// str helpers
void buildr(int index, int a, int b){
    if(a > b) return;
    if(a == b){
        str[index] = dist(a - 1, b + 1) - dist(a - 1, a) - dist(a, b + 1);
        return;
    }
    buildr(index * 2, a, (a + b) / 2);
    buildr(index * 2 + 1, (a + b) / 2 + 1, b);

    str[index] = min(str[index * 2], str[index * 2 + 1]);
}

void updr(int index, int a, int b, int ch){
    if(ch < a - 1 || b + 1 < ch || a > b) return;
    if(a == b && (a - 1 == ch || ch == a || ch == b + 1)){
        str[index] = dist(a - 1, b + 1) - dist(a - 1, a) - dist(a, b + 1);
        return;
    }
    updr(index * 2, a, (a + b) / 2, ch);
    updr(index * 2 + 1, (a + b) / 2 + 1, b, ch);

    str[index] = min(str[index * 2], str[index * 2 + 1]);
}

int qryr(int index, int a, int b, int qa, int qb){
    if(qb < a || b < qa || (a > b || qa > qb)) return 0;
    if(qa <= a && b <= qb) {
        return str[index];
    }
    return min(qryr(index * 2, a, (a + b) / 2, qa, qb), qryr(index * 2 + 1, (a + b) / 2 + 1, b, qa, qb)); 
}

int main(){
    ifstream cin("marathon.in");
    ofstream cout("marathon.out");

    cin >> n >> q;
    FOR(i, 1, n) cin >> p[i].f >> p[i].s;

    buildp(1, 1, n);
    buildr(1, 2, n - 1);

    FOR(i, 1, q){
        char c;
        cin >> c;
        if(c == 'U'){
            int pi;
            cin >> pi >> p[pi].f >> p[pi].s;

            updp(1, 1, n, pi);
            updr(1, 2, n - 1, pi);
        }else{
            int x, y; cin >> x >> y;

            if(x == y) cout << 0 << endl;
            else cout << (qryp(1, 1, n, x, y) + qryr(1, 2, n - 1, x + 1, y - 1)) << endl;
        }
    }
}
