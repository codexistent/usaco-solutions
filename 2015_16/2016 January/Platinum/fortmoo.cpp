#include <fstream>
#include <algorithm>
using namespace std;
#define MAXNM 205

int N, M, MAX = 0;
bool S[MAXNM][MAXNM];
int PFX[MAXNM][MAXNM];

int main(){
    ifstream fin("fortmoo.in");
    ofstream fout("fortmoo.out");
  
    fin >> N >> M;
    for(int i = 1; i <= N; i++){
        string s;
        fin >> s;
        for(int j = 1; j <= M; j++) {
            S[i][j] = (s[j - 1] == 'X');

            PFX[i][j] = S[i][j] + PFX[i - 1][j] + PFX[i][j - 1] - PFX[i - 1][j - 1];
        }
    }

    for(int y1 = 1; y1 <= N; y1++){
        for(int y2 = y1; y2 <= N; y2++){
            int x2 = 1, x3 = 1;
            for(int x1 = 1; x1 <= M; x1++){
                if(PFX[y2][x1] - PFX[y1 - 1][x1] - PFX[y2][x1 - 1] + PFX[y1 - 1][x1 - 1] != 0) continue;
                MAX = max(MAX, y2 - y1 + 1);

                x2 = max(x2, x1);
                x3 = max(x3, x1);
                while(x2 + 1 <= M && !S[y1][x2 + 1] && !S[y2][x2 + 1]){
                    x2++;
                    if(PFX[y2][x2] - PFX[y1 - 1][x2] - PFX[y2][x2 - 1] + PFX[y1 - 1][x2 - 1] == 0) x3 = x2;
                }

                MAX = max(MAX, (x3 - x1 + 1) * (y2 - y1 + 1));
            }
        }
    }

    fout << MAX;
}
