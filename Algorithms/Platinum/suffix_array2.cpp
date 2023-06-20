#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
 
struct suffix_array {
public:
    int N;
    string S;
    vector<int> SA, R, LCP, EC;
 
    suffix_array(string s){
        S = s + '$';
        N = S.length();
        compute_sa();
        N--;
    }
 
    void compute_sa(){
        helper h;
        string s = S;
        int L, k = 0;
        vector<int> ec(N + 1);
        // 1 - concatenate characters until a power of 2
        for(L = 1; L < s.length(); L *= 2, k += 1);
        for(int i = s.length() + 1; i <= L; i++) s += S[i - S.length() - 2];
 
        // 2 - i = 0 - make initial equivalence classes
        h.initial_ec(ec, s); 
 
        // 3 - i = 1...k - duplicate suffix lengths until final suffix array
        EC.resize(N);
        SA.resize(N);
        for(int i = 1, l = 2; i <= k; i++, l *= 2) h.expand_sa(ec, EC, SA, l, N);
        // finishing touches
        swap(EC, ec);
    }
    void compute_lcp(){
        // TODO
    }
private:
    class helper {
        struct sa_comp { // suffix array comparator
            const vector<int>& ec;
            int L, N;
 
            sa_comp(const vector<int>& v, int l, int n) : ec(v), L(l), N(n) {}
 
            bool operator()(int s1, int s2) const {
                if(ec[s1] != ec[s2]){
                    return ec[s1] < ec[s2];
                }else if(ec[(s1 + L / 2) % N] != ec[(s2 + L / 2) % N]){
                    return ec[(s1 + L / 2) % N] < ec[(s2 + L / 2) % N];
                }else{
                    return s1 < s2;
                }
            }
        };
    public:
        void initial_ec(vector<int>& ec, string s) { // build initial equivalence classes - counting sort O(n + k)
            int N = s.length(), c[256] = {0}, r[N];
            for(int i = 0; i < N; i++) c[s[i]]++; // compute # of character i
            for(int i = 1; i < 256; i++) c[i] += c[i - 1]; // c[i] = # of characters 1...i in S
            
            for(int i = 0; i < N; i++) r[--c[s[i]]] = i; // r sorts all strings lexiographically & then by index
 
            ec[r[0]] = 0; // build equicalence classes
            for(int i = 1; i < N; i++) ec[r[i]] = ec[r[i - 1]] + (s[r[i]] != s[r[i - 1]]);
        }
        void expand_sa(vector<int>& ec, vector<int>& EC, vector<int>& SA, int L, int N2){ // expand suffix lengths by two
            // update suffix array
            for(int i = 0; i < N2; i++) SA[i] = i;            
            sort(SA.begin(), SA.end(), sa_comp(ec, L, N2));
            /*
            You can also use lambda instead of comparator:
            ---------
            sort(SA.begin(), SA.end(), [&](int s1, int s2) {
                if(ec[s1] != ec[s2]){
                    return ec[s1] < ec[s2];
                }else if(ec[(s1 + l / 2) % N] != ec[(s2 + l / 2) % N]){
                    return ec[(s1 + l / 2) % N] < ec[(s2 + l / 2) % N];
                }else{
                    return s1 < s2;
                }
            });
            ---------
            */
 
            // update equivalence classes
            EC[SA[0]] = 0;
            for(int i = 1; i < N2; i++) EC[SA[i]] = EC[SA[i - 1]] + !((ec[SA[i]] == ec[SA[i - 1]]) && (ec[(SA[i] + L / 2) % N2] == ec[(SA[i - 1] + L / 2) % N2]));
            swap(EC, ec);
        }
    };
};
 
int main(){
    // 
    string str;
    cin >> str;
    suffix_array s(str);
    for(int i = 0; i <= s.N; i++) cout << s.SA[i] << " ";
}
