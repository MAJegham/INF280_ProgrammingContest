#include <cstdio>
#include <cmath>
#include <cstdint>
#include <algorithm>
#include <bitset>
#include <vector>
#include <random>
#include <iostream>

#define EPS 1e-05

using namespace std;

/****************************************************************************************
Tried to avoid doing the maths for the problem
Instead, run a simulation and estimate expectation by the mean
Fails: not accurate
****************************************************************************************/

int simulate(int N,int D,int C,uint64_t cesar, uint64_t raul){
    int box [N];
    for (int i = 0; i<N; i++) box[i] = i+1;
    int round = 0;
    //printf("-----------");
    while (raul!=0 && cesar!=0){
        round++;
        random_shuffle(box, box + N);
        //printf("\ndrawing : ");
        for(int d=0; d<D; d++){ //draw D balls
            int b = box[d];
            //mark ball on cards
            //printf(" %d ",b);
            cesar &= ~(1<<b);
            raul &= ~(1<<b);
        }
    }
    return round;
}

int main(){
    srand(time(0));
    int N=0;
    int D=0;
    int C=0;

    scanf("%d %d %d",&N,&D,&C);
    while (true){
        if (N==0 && D==0 && C==0) return 0;

        uint64_t init_cesar = 0;
        uint64_t init_raul = 0;
        for (int c = 0; c < C; c++){//cesar's card
            int b = 0;
            scanf("%d",&b);
            init_cesar |= 1<<b;
        }
        for (int c = 0; c < C; c++){//raul's card
            int b = 0;
            scanf("%d",&b);
            init_raul |= 1<<b;
        }

        double average = 1;
        double up_average = 0;
        long iter = 0;
        while( ( (iter < 50) || (fabs(up_average-average) > EPS)) && (iter < 5000) ){ //
            iter++;
            average = up_average;

            int rounds = simulate(N,D,C,init_cesar,init_raul);

            up_average = ( (average * ((double)iter-1)) + (double)rounds ) / ((double)iter);
            //printf("\n%f",up_average);
        }

        //printf("\n%.5f in %ld",up_average,iter);
        printf("%.5f\n",up_average);
        N = D = C = 0;
        scanf("%d %d %d",&N,&D,&C);
    }
}
