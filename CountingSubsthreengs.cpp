#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
#define MAXN 1000001

vector<vector<int> > line;
unsigned long long subs3(){
    unsigned long long res = 0;
    for(long i=0; i<(long)line.size();i++){ //for each digital word from line
        //long size = line[i].size()+1;

        //int reste [size];
        //fill_n(reste,size,0);
        int reste = 0;
        //unsigned long long dp [size];
        //fill_n(dp,size,0);
        //long long occ [3][size];
        //fill_n((long long*)occ,3*size,0);
        //long long cache [3];
        //fill_n((long long*)occ,3,0);
        unsigned long long occ [3];
        fill_n((unsigned long long*)occ,3,0);

        for(long j=0; j<(long)line[i].size();j++){ //proccess the word
            reste =  ( reste + line[i][j] )%3;
            //for (int k=0; k<3; k++)  cache[k] = occ[k];
            res = res + occ[reste];
            occ[reste]++;
            if ( reste == 0 ) res++;
        }
    }

    return res;
}

int main(){


    vector<int> digits;
    char c;
    while(scanf("%c",&c) == 1){

        if (c <= '9'  && c >= '0'){ //digit
            digits.push_back(c - '0');
        }
        else if (c == '\n'){ //end of line
            if ( digits.size() > 0 )
                line.push_back(digits);
            //Process all line ie text
            if (line.size() > 0){
                printf("%llu\n",subs3());
                line.clear();
                digits.clear();
                continue;
            }
            else{
                printf("0\n");
                continue;
            }
            return 0;
        }
        else{ //letter
            if ( digits.size() > 0 )
                line.push_back(digits);
            digits.clear();
            continue;
        }
    }


}
