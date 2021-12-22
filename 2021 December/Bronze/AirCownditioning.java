import java.io.*;
import java.util.*;
// Sat, Dec 18, 2021 || 11/11 test cases
public class P2 {
    public static void main(String args[]) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer in = new StringTokenizer(br.readLine());
        PrintWriter out = new PrintWriter(System.out);

        int n = Integer.parseInt(in.nextToken());
        int ans = 0;
        int[] original = new int[n];
        int[] targetChng = new int[n];
        in = new StringTokenizer(br.readLine());
        for(int i = 0; i < n; i++) original[i] = Integer.parseInt(in.nextToken());
        in = new StringTokenizer(br.readLine());
        for(int i = 0; i < n; i++) targetChng[i] = original[i] - Integer.parseInt(in.nextToken());

        ans += Math.abs(targetChng[0]);
        int last = targetChng[0];
        for(int i = 1; i < n; i++){
            int curr = targetChng[i];
            if(Math.abs(curr) == curr && Math.abs(last) == last){ // same side(both positive change needed)
                if(curr > last) ans += curr - last;
            }else if(Math.abs(curr) != curr && Math.abs(last) != last){ // same side(both negitive change needed)
                if(curr < last) ans += Math.min(Math.abs(curr), Math.abs(last - curr));
            }else{
                ans += Math.abs(curr);
            }

            last = curr;
        }

        out.println(ans);
        out.close();
    }
}
