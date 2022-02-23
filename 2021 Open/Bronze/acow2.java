import java.io.*;
import java.util.*;
// Fri, Apr 2nd, 2021 || 10 / 10 test cases
public class acowtwo {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer in = new StringTokenizer(br.readLine());
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out));

        int answer = 0;
        TreeMap<String, Integer> AlphaVal = new TreeMap<>();

        int papers = Integer.parseInt(in.nextToken());
        int cows = Integer.parseInt(in.nextToken());
        String cowNames[] = new String[cows];
        String origNames[] = new String[cows];

        // 1. Set Alpha Order
        in = new StringTokenizer(br.readLine());
        for(int i = 0; i < cows; i++){
            cowNames[i] = in.nextToken();
            AlphaVal.put(cowNames[i], 0);
            origNames[i] = cowNames[i];
        }

        Arrays.sort(cowNames);

        for(int i = 0; i < AlphaVal.size(); i++){
            AlphaVal.put(cowNames[i], i);
        }

        int citOrders[][] = new int[papers][cows];
        int whereCowAt[][] = new int[cows][papers];


        // 1-5. Go through all paper's author order
        for(int i = 0; i < papers; i++){
            in = new StringTokenizer(br.readLine());
            for (int j = 0; j < cows; j++){
                String input = in.nextToken();
                citOrders[i][j] = AlphaVal.get(input);

                whereCowAt[citOrders[i][j]][i] = j;
            }
        }

        // 2. Go through each relation
        for(int i = 0; i < cows; i++){
            for(int j = 0; j < cows; j++){
                if(i == j){
                    out.write("B");
                    continue;
                }

                int cowOne = AlphaVal.get(origNames[i]);
                int cowTwo = AlphaVal.get(origNames[j]);

                boolean setyet = false;
                boolean superior = false;
                if(cowOne > cowTwo){
                    for(int k = 0; k < papers; k++){
                        if(whereCowAt[cowOne][k] > whereCowAt[cowTwo][k]){
                            int last = citOrders[k][whereCowAt[cowTwo][k]];
                            for(int l = whereCowAt[cowTwo][k]+1; l < whereCowAt[cowOne][k]+1; l++){
                                if(citOrders[k][l] < last){
                                    superior = true;
                                    setyet = true;
                                    break;
                                }
                                last = citOrders[k][l];
                            }
                            if(setyet) break;
                        }else{
                            superior = false;
                            setyet = true;
                            break;
                        }
                    }
                }else if(cowOne < cowTwo){
                    for(int k = 0; k < papers; k++){
                        if(whereCowAt[cowOne][k] < whereCowAt[cowTwo][k]){
                            int last = citOrders[k][whereCowAt[cowOne][k]];
                            for(int l = whereCowAt[cowOne][k]+1; l < whereCowAt[cowTwo][k]+1; l++){
                                if(citOrders[k][l] < last){
                                    superior = false;
                                    setyet = true;
                                    break;
                                }
                                last = citOrders[k][l];
                            }

                            if(setyet) break;
                        }else{
                            superior = true;
                            setyet = true;
                            break;
                        }
                    }

                }
                if(setyet){
                    if(superior) out.write("1"); else out.write("0");
                }else{
                    out.write("?");
                }

            }
            out.write("\n");
        }

        out.close();
    }
}
