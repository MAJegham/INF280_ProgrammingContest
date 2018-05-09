#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <string>

using namespace std;

int main () {
    const int lim = 5000;
    int n=0;

    while (true){
        n++;
        int P = 0;
        int R = 0;
        scanf("%d",&P);
        scanf("%d",&R);

        if (P==0 && R==0)
            return 0;

        //matrix of pairwise distances
        int Dist[P][P];
        fill_n((int*)Dist,P*P,lim);

        unordered_map<string, int> dict; //link each name to an index
        dict.clear();
        dict.reserve(P);
        int ind = 0;
        for(int i=0; i<R; i++){
            string s1;
            cin >> s1;
            if ( dict.find(s1) == dict.end() ) {
                Dist[ind][ind] = 0;
                dict[s1] = ind;
                ind++;
            }
            string s2;
            cin >> s2;
            if ( dict.find(s2) == dict.end() ) {
                Dist[ind][ind] = 0;
                dict[s2] = ind;
                ind++;
            }
            Dist[dict[s1]][dict[s2]] = 1;
            Dist[dict[s2]][dict[s1]] = 1;
        }

        //Floyd-warshall
        for(int i=0; i<P; i++){
            for(int j=0; j<P; j++){
                for(int k=0; k<P; k++){
                    Dist[j][k] = min(Dist[j][k], Dist[j][i] + Dist[i][k]);
                }
            }
        }

        int res = *max_element((int*)Dist,(int*)Dist+P*P);
        if (res == lim){
            printf("Network %d: DISCONNECTED\n\n",n);
        }
        else{
            printf("Network %d: %d\n\n",n,res);
        }
    }

    return 0;
}





