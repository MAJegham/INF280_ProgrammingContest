#include <cstdio>
#include <algorithm>

using namespace std;

int main(){

    //*TODO* try : 2*50*50*9*8*7*5
    int maxLim = 200; //Accepted on uva with just 200
    int N = 0;
    int ent = false;

    while (scanf("%d\n",&N) == 1){
        if ( ent )
            printf("\n");
        else
            ent = true;

        bool oState [N][N];
        int per[N][N];
        bool reach [N][N];
        bool prev[N][N];

        //Read original states
        for (int i=0; i<N;i++){
            char c;
            for (int j = 0; j<N; j++){
                scanf("%c",&c);
                if (c == '.'){
                    oState[i][j] = true;

                }
                else{
                    oState[i][j] = false;

                }
            }
            scanf("%c",&c);
        }
        //Read periods 1-digit at a time
        for (int i=0; i<N;i++){
            int r;
            for (int j = 0; j<N; j++){
                scanf("%1d",&r);
                per[i][j] = r;
            }
        }

        //Start algo
        //t=0
        int res = 0;
        bool reachable = false;
        fill_n((bool*)reach,N*N,false);
        reach[0][0] = true;

        for(int t=1; t<maxLim; t++){
            //check reachibility of home from previous iteration
            if (reach[N-1][N-1]){
                reachable = true;
                res = t-1;
                break;
            }

            //save previously reachable cells
            for (int i=0; i<N;i++){
                for (int j = 0; j<N; j++){
                    prev[i][j] = reach[i][j];
                }
            }

            //propagate reachability i.e. build the new reach[][]
            for (int i=0; i<N;i++){
                for (int j = 0; j<N; j++){
                    bool s;
                    if (per[i][j] == 0)
                        s = oState[i][j];
                    else if ( (t % (2*per[i][j])) < per[i][j] )
                        s = oState[i][j];
                    else
                        s = !(oState[i][j]);

                    if (!s)
                        reach[i][j] = false;
                    else if ( prev[i][j] )
                        reach[i][j] = true;
                    else if ( (i-1 < N ) && (i-1 >= 0 ) && ( prev[i-1][j] ) )
                        reach[i][j] = true;
                    else if ( (i+1 < N ) && (i+1 >= 0 ) && ( prev[i+1][j] ) )
                        reach[i][j] = true;
                    else if ( (j-1 < N ) && (j-1 >= 0 ) && ( prev[i][j-1] ) )
                        reach[i][j] = true;
                    else if ( (j+1 < N ) && (j+1 >= 0 ) && ( prev[i][j+1] ) )
                        reach[i][j] = true;
                    else
                        reach[i][j] = false;
                }
            }

        }

        if (reachable)
            printf("%d\n",res);
        else
            printf("NO\n");

    }

    return 0;
}
