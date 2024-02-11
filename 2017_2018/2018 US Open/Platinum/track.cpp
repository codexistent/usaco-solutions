#include "grader.h"
#define BLOK 1000 // this is the sqrt of (max IDal. of n) = sqrt(10^6)
#define DIV 4050

void helpBessie(int ID){
    int n = getTrainLength(), k = getWindowLength();
    int p = getCurrentPassIndex(), i = getCurrentCarIndex();
    
    if(p==0)
	{
        if(i == 0) set(0, 0), set(1, -1);
        int back = get(0), top = get(1);
        
        if(i % BLOK == 0 || (i >= k && (i - k) % BLOK == 0)){
            while(top >= back && get(1 + 2 * top + 2) >= ID) top--;
            top++, set(1 + 2 * top + 1, i), set(1 + 2 * top + 2, ID);
        }else if((int)get(1 + 2 * top + 2) >= ID){
            top--;
            while(top >= back && get(1 + 2 * top + 2) >= ID) top--;
            top++, set(1 + 2 * top + 1, i), set(1 + 2 * top + 2, ID);
        }

        if(i + 1 >= k && (i + 1 - k) % BLOK == 0){
            while(back <= top && get(2 * back + 2) <= i - k) back++;
            set(DIV + (i + 1 - k) / BLOK, get(2 * back + 2));
        }

        set(0, back), set(1, top);
	}
    else
	{
		if(i < get(DIV)) return;
        if(i == get(DIV)){
            set(0, 0), set(1, -1);
            set(DIV - 1, 0); // current block end idx
            set(DIV - 2, 1000000000); // shared low throughout all windows in block
            set(DIV - 3, 0); // # outputs
        }
		int bc = get(DIV - 1);
        int back = get(0), top = get(1);
        int outputs = get(DIV - 3);
        if(i - get(DIV + bc) <= BLOK){
            while(back <= top && get(2 * top + 3) >= ID) top--;
            top++;
            set(2 * top + 2, i), set(2 * top + 3, ID);
        }else{
            int g_low = get(DIV - 2);
            if(ID < g_low) set(DIV - 2, ID);
        }

		if(outputs + k - 1 == i) {
            while(back <= top && get(2 * back + 2) < outputs) back++;
            shoutMinimum((get(DIV - 2) < get(2 * back + 3)) ? get(DIV - 2) : get(2 * back + 3));
            outputs++;
        }
		while(BLOK * (bc + 1) + k - 1 < n && get(DIV + bc + 1) == i){
            while(outputs <= BLOK * (bc + 1)){
                while(back <= top && get(2 * back + 2) < outputs) back++;
                shoutMinimum((get(DIV - 2) < get(2 * back + 3)) ? get(DIV - 2) : get(2 * back + 3));
                outputs++;
            }
            bc++;
            set(DIV - 2, 1000000000);
            top = back = 0;
            set(2 * top + 2, i), set(2 * top + 3, ID);
        }

		set(DIV - 3, outputs);
        set(DIV - 1, bc);
        set(1, top);
        set(0, back);
	}
}
