// [SUFFIX ARRAY // N LOG^2 N // 10-6-2023]

#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const ll MAXN = 1e7 + 5; // MAXN determines max string length( without segfault-ing)

int N, N2, K, ec[MAXN], EC[MAXN], SA[MAXN];
int L;
char S[MAXN];

int mod(int x){
    return (x % N2 == 0) ? N2 : x % N2;
}

bool sa_cmp(int s1, int s2) { // suffix array comparator
    if(ec[s1] != ec[s2]){
        return ec[s1] < ec[s2];
    }else if(ec[mod(s1 + L / 2)] != ec[mod(s2 + L / 2)]){
        return ec[mod(s1 + L / 2)] < ec[mod(s2 + L / 2)];
    }else{
        return s1 < s2;
    }
}

// returns if two strings are in same equivalence class
bool equivalent_class(int s1, int s2){ return (ec[s1] == ec[s2]) && (ec[mod(s1 + L / 2)] == ec[mod(s2 + L / 2)]); }

void initial(){
    vector<pair<int, int> > c;
    for(int i = 1; i <= N2; i++) c.push_back(make_pair(S[i], i));
    sort(c.begin(), c.end());

    ec[c[0].second] = 1;
    for(int i = 2; i <= N2; i++) ec[c[i - 1].second] = ec[c[i - 2].second] + (c[i - 1].first != c[i - 2].first);
}

void expand(int l){
    L = l;
    for(int i = ec[0] = 0; i <= N2; i++) SA[i] = i;
    sort(SA + 1, SA + 1 + N2, sa_cmp);

    for(int i = 1; i <= N2; i++) EC[SA[i]] = EC[SA[i - 1]] + !equivalent_class(SA[i], SA[i - 1]);
    swap(ec, EC);

}

void suffix_array(string s){
    // build original string
    N = s.length();
    for(int i = 1; i <= N; i++) S[i] = s[i - 1];

    // find K = equal or next higher power of two to N + 1
    N2 = 1, K = 0;
    while(N2 < N + 1) N2 *= 2, K++;

    // add extra digits based on K
    for(int i = N + 1; i <= N2; i++) S[i] = '$';

    // make initial ec = equivalence class
    initial();

    // expand suffixes by x2 K times
    for(int i = 1, p = 2; i <= K; i++, p *= 2) expand(p);
}

int main(){
    string s;
    cin >> s;
    suffix_array(s);

    for(int i = N2 - N + 1; i <= N2; i++) cout << SA[i]; // indexing starts at 1
}
