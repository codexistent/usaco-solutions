import java.io.*;
import java.util.*;
// Mon, Dec 20, 2021 || 21 / 21 test cases

public class P1 {
    public static void main(String args[]) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer in = new StringTokenizer(br.readLine());
        PrintWriter  out = new PrintWriter(System.out);

        int k = Integer.parseInt(in.nextToken());
        int m = Integer.parseInt(in.nextToken());
        int n = Integer.parseInt(in.nextToken());
        Patch[] patches = new Patch[k];
        for(int i = 0; i < k; i++){
            in = new StringTokenizer(br.readLine());
            patches[i] = new Patch(Integer.parseInt(in.nextToken()), Integer.parseInt(in.nextToken()));
        }

        boolean[] patchTaken = new boolean[k];
        int[] nohjCows = new int[m];
        Worth[] nohjWorthL = new Worth[m]; for(int i = 0; i < m; i++) nohjWorthL[i] = new Worth();
        Worth[] nohjWorthR = new Worth[m]; for(int i = 0; i < m; i++) nohjWorthR[i] = new Worth();

        TreeSet<Integer> nohjTS = new TreeSet<>();
        HashMap<Integer, Integer> getnohjId = new HashMap<>();
        for(int i = 0; i < m; i++) {
            in = new StringTokenizer(br.readLine());
            nohjCows[i] = Integer.parseInt(in.nextToken());
            nohjTS.add(nohjCows[i]);
            getnohjId.put(nohjCows[i], i);
        }

        for(int i = 0; i < k; i++){
            int lower = Integer.MAX_VALUE;
            int l = 0;
            if(nohjTS.lower(patches[i].loc) != null) {
                lower = patches[i].loc - nohjTS.lower(patches[i].loc);
                l = nohjTS.lower(patches[i].loc);
            }
            int h = 0;
            int higher = Integer.MAX_VALUE;
            if(nohjTS.higher(patches[i].loc) != null) {
                higher = nohjTS.higher(patches[i].loc) - patches[i].loc;
                h = nohjTS.higher(patches[i].loc);
            }

            if(lower < higher) {
                int id = getnohjId.get(l);
                nohjWorthL[id].totWorth += (long)patches[i].tasti;
                nohjWorthL[id].patches.add(i);
            }else if(lower > higher){
                int id = getnohjId.get(h);
                nohjWorthR[id].totWorth += (long)patches[i].tasti;
                nohjWorthR[id].patches.add(i);
            }else {
                int id = getnohjId.get(l);
                nohjWorthL[id].totWorth += (long)patches[i].tasti;
                nohjWorthL[id].patches.add(i);
                id = getnohjId.get(h);
                nohjWorthR[id].totWorth += (long)patches[i].tasti;
                nohjWorthR[id].patches.add(i);
            }
        }

        PriorityQueue<Worth> line = new PriorityQueue<>(new Comparator<Worth>() {
            @Override
            public int compare(Worth o1, Worth o2) {
                if(o1.totWorth > o2.totWorth) return -1;
                else if(o1.totWorth < o2.totWorth) return 1;
                else return 0;
            }
        });
        for(int i = 0; i < m; i++){
            line.add(nohjWorthL[i]);
            line.add(nohjWorthR[i]);
        }

        long ans = 0;
        while(!line.isEmpty() && n != 0){
            Worth w = line.poll();
            if(w.totWorth == 0) break;

            long currWorth = 0;
            for(Integer p : w.patches){
                if(!patchTaken[p]) currWorth += patches[p].tasti;
            }

            if(currWorth < line.peek().totWorth) {
                w.totWorth = currWorth;
                line.add(w);
                continue;
            }

            for(Integer p : w.patches){
                if(!patchTaken[p]) patchTaken[p] = true;
            }
            ans += currWorth;
            n--;
        }

        out.println(ans);
        out.close();
    }

    public static class Patch{
        public int loc, tasti;
        Patch(int loc, int tasti){
            this.loc = loc;
            this.tasti = tasti;
        }
    }

    public static class Worth{
        public long totWorth = 0, id = 0;
        public ArrayList<Integer> patches = new ArrayList<>();
    }
}
