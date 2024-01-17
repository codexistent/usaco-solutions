// inspo : https://github.com/fishy15/competitive_programming/blob/d199d6b7295e18f7850b90d4b1c32a3ee22ac0ad/oi/usaco/contest/2017/open/plat/cowbasic.cpp#L4
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007
#define FOR(i, a, b) for(int i = a; i <= b; i++)

int n;

struct Matrix {
    const static int maxn = 101;
    ll m[maxn][maxn];
    Matrix() { memset(m, 0, sizeof m); }
    Matrix(char c) { // identity matrix
        memset(m, 0, sizeof m);
        FOR(i, 0, maxn - 1) m[i][i] = 1; 
    }
    Matrix operator* (const Matrix& m2){
        Matrix r;
        FOR(i, 0, n - 1) FOR(j, 0, n - 1) {
            FOR(k, 0, n - 1) {
                r.m[i][j] = (r.m[i][j] + (m[i][k] * m2.m[k][j]) % MOD) % MOD;
            }
        }
        return r;
    }
    static Matrix pow(Matrix &m, int e){
        Matrix r('i');
        while(e){
            if(e & 1) r = r * m;
            m = m * m;
            e >>= 1;
        }
        return r;
    }
};

struct level {
    int sz;
    Matrix m;
    level(int x) : sz(x), m('i') {}
};

map<string, int> var;
stack<level> st;

int main(){
    ifstream cin ("cowbasic.in");
    ofstream cout ("cowbasic.out");

    string line;
    st.push(1);
    int vc = 0;
    while(getline(cin, line)) {
        vector<string> v;
        stringstream ss(line);
        string s;
        while(getline(ss, s, ' ')) if(s != "") {
            if('a' <= s[0] && s[0] <= 'z') if(!var.count(s)) var[s] = ++vc;
            if(s != "(" && s != ")" && s != "+" && s != "{") v.push_back(s);
        }

        n = var.size() + 1;
        if(v[0][0] == 'R') {
            int q = var[v[1]];
            cout << st.top().m.m[0][q] << endl;
        } else if('0' <= v[0][0] && v[0][0] <= '9') {
            st.push(stoi(v[0]));
        } else if (v[0][0] != '}') {
            Matrix id('i');
            int val = var[v[0]];
            id.m[val][val] = 0;
            FOR(i, 1, v.size() - 1){
                if('a' <= v[i][0] && v[i][0] <= 'z') {
                    id.m[var[v[i]]][val]++;
                } else if('0' <= v[i][0] && v[i][0] <= '9') {
                    int q = stoi(v[i]);
                    id.m[0][val] = (id.m[0][val] + q) % MOD;
                }
            }
            st.top().m = st.top().m * id;
        } else {
            auto t = st.top();
            st.pop();
            t.m = Matrix::pow(t.m, t.sz);
            st.top().m = st.top().m * t.m;
        }
    }
}
