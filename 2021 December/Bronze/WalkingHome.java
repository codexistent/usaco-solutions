import java.io.*;
import java.util.*;
// Sat, Dec 18th, 2021 || 10 / 10 test cases
public class P3 {
    public static enum Dir{PLUSA, PLUSB};
    public static int n;

    public static void main(String args[]) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer in = new StringTokenizer(br.readLine());
        PrintWriter out = new PrintWriter(System.out);

        int t = Integer.parseInt(in.nextToken());

        for(int i = 0; i < t; i++){ in = new StringTokenizer(br.readLine());
            n = Integer.parseInt(in.nextToken());
            int k = Integer.parseInt(in.nextToken());
            boolean[][] bale = new boolean[n][n];

            for(int i1 = 0; i1 < n; i1++){ in = new StringTokenizer(br.readLine());
                String s = in.nextToken();
                for(int j1 = 0; j1 < n; j1++){
                    bale[i1][j1] = s.charAt(j1) == 'H';
                }
            }
            int ans = recurse(0, 0, bale, Dir.PLUSA, k) + recurse(0, 0, bale, Dir.PLUSB, k);
            out.println(ans);
        }

        out.close();
    }

    public static int recurse(int x, int y, boolean[][] bale, Dir dir, int depthLeft){
        if(bale[x][y]) return 0;

        int ret = 0;
        if(dir == Dir.PLUSA) { // recurse, in version where Direction is PLUSA(increasing x)
            for(int i = x + 1; i < n; i++){
                if(bale[i][y]) break;

                if(i == n - 1 && y == n - 1) {
                    ret += 1;
                }
                if(depthLeft != 0){
                    ret += recurse(i, y, bale, Dir.PLUSB, depthLeft - 1);
                }
            }
        }else{
            for(int i = y + 1; i < n; i++){ // recurse, in version where Direction is PLUSB(increasing y)
                if(bale[x][i]) break;

                if(x == n - 1 && i == n - 1) {
                    ret += 1;
                }
                if(depthLeft != 0) {
                    ret += recurse(x, i, bale, Dir.PLUSA, depthLeft - 1);
                }
            }
        }
        return ret;
    }
}
