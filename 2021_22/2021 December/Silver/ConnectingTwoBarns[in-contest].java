import java.io.*;
import java.util.*;
// Mon, Dec 20th, 2021 || 10 / 10 test cases
public class P2V2 {
    public static ArrayList<TreeSet<Integer>> groups = new ArrayList<>();
    public static int groupNum = 0;
    public static HashSet<Integer> visited = new HashSet<>();
    public static ArrayList<ArrayList<Integer>> edges = new ArrayList<>();

    public static void main(String args[]) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer in = new StringTokenizer(br.readLine());
        PrintWriter out = new PrintWriter(System.out);

        int t = Integer.parseInt(in.nextToken());
        for(int i = 0; i < t; i++){
            // get input
            in = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(in.nextToken());
            int m = Integer.parseInt(in.nextToken());
            edges.clear();
            for(int j = 0; j < n; j++) edges.add(new ArrayList<>());

            for(int j = 0; j < m; j++) {
                in = new StringTokenizer(br.readLine());
                int a = Integer.parseInt(in.nextToken()) - 1;
                int b = Integer.parseInt(in.nextToken()) - 1;

                edges.get(a).add(b);
                edges.get(b).add(a);
            }

            // make groups
            groups.clear();
            visited.clear();

            groupNum = 0;
            groups.add(new TreeSet<>());
            dfs(0);
            groupNum = 1;
            if(visited.contains(n - 1)) {
                out.println(0);
                continue;
            }
            groups.add(new TreeSet<>());
            dfs(n - 1);
            for(int j = 1; j < n - 1; j++){
                if(!visited.contains(j)) {
                    groupNum++;
                    groups.add(new TreeSet<>());
                    dfs(j);
                }
            }

            // get answer
            long ans = Long.MAX_VALUE;
            // option 1: build 1 path
            for(Integer node : groups.get(0)){
                long closest = Integer.MAX_VALUE;
                if(groups.get(1).lower(node) != null) closest = Math.min(closest, node - groups.get(1).lower(node));
                if(groups.get(1).higher(node) != null) closest = Math.min(closest, groups.get(1).higher(node) - node);

                closest *= (long)closest;
                ans = Math.min(ans, closest);
            }
            // option 2: build 2 paths
            for(int j = 2, len = groups.size(); j < len; j++) {
                long min1 = Long.MAX_VALUE; long min2 =Long.MAX_VALUE;
                for (Integer node : groups.get(j)) {
                    long closest = Integer.MAX_VALUE;
                    if (groups.get(1).lower(node) != null)
                        closest = Math.min(closest, node - groups.get(1).lower(node));
                    if (groups.get(1).higher(node) != null)
                        closest = Math.min(closest, groups.get(1).higher(node) - node);

                    closest *= (long) closest;
                    min1= Math.min(min1, closest);
                    ///
                    closest = Integer.MAX_VALUE;
                    if (groups.get(0).lower(node) != null)
                        closest = Math.min(closest, node - groups.get(0).lower(node));
                    if (groups.get(0).higher(node) != null)
                        closest = Math.min(closest, groups.get(0).higher(node) - node);
                    closest *= (long) closest;
                    min2= Math.min(min2, closest);
                }
                ans = Math.min(ans, min1 + min2);
            }

            out.println(ans);
        }

        out.close();
    }

    public static void dfs(int node){
        if(visited.contains(node)) return;
        visited.add(node);

        groups.get(groupNum).add(node);
        for(Integer edge : edges.get(node)) dfs(edge);
    }
}
