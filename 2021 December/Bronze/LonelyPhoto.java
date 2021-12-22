import java.io.*;
import java.util.*;

public class P1V2 {
    public static void main(String args[]) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer in = new StringTokenizer(br.readLine());
        PrintWriter out = new PrintWriter(System.out);

        // create groups
        int n = Integer.parseInt(in.nextToken());
        in = new StringTokenizer(br.readLine());
        ArrayList<Integer> groups = new ArrayList<>();

        String s = in.nextToken();
        int tot = 0;
        char type = 'L';
        for(int i = 0; i < n; i++){
            if(type == s.charAt(i)) {
                tot++;
            } else{
                groups.add(tot);
                tot = 1;
                type = s.charAt(i);
            }
        }
        groups.add(tot); groups.add(0);

        long ans = 0;
        for(int i = 1, len = groups.size() - 1; i < len; i++){
            int left = groups.get(i - 1);
            int right = groups.get(i + 1);
            ans += Math.max(left - 1, 0) + Math.max(right - 1, 0);
            if(groups.get(i) == 1){
                ans += (long)left * right;
            }
        }

        out.println(ans);
        out.close();
    }
}
