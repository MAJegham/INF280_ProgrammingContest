#include <cstdio>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <vector>

#define EPS 1e-12

using namespace std;

unsigned long long int ones [64]; // ones[i] := number of ones from  0  to   (2^n -1)

unsigned long long int onesFrom0(unsigned long long int A){
    if (A == 0) return 0;
    if ( (A & (A - 1)) == 0 ){ //if A==2^n
                                // this fails( log2(A) - floor(log2(A))  < EPS  ) for 9007199254740991
                                // https://stackoverflow.com/questions/600293/how-to-check-if-a-number-is-a-power-of-2?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
        return 1 + ones[(int)log2(A)];
    }
    if ( (A & (A + 1)) == 0 ) {//if A==2^n-1
                                //( log2(A+1) - floor(log2(A+1))  < EPS)
        return ones[(int)log2(A+1)];
    }
    else{
        unsigned long long int ret = 0;
        for(int i = 0; i <= log2(A) ; i++ ){
            unsigned long long int period = (unsigned long long int)pow(2,i+1);
            ret += A/period*(period/2);
            if (A%period+1 > period/2)
                ret += A%period-period/2+1;
        }
        return ret;
        return 0;
    }

}

int main(){

    ones [0] = 0;
    ones [1] = 1;
    for (int i = 2; i<64; i++){
        ones[i] = 2*ones[i-1] + (unsigned long long int)pow(2,i-1);
    }


    unsigned long long int A = 0;
    unsigned long long int B = 0;
    unsigned long long int res = 0;

    scanf("%llu %llu",&A,&B);
    while (true){
        if (A==0 && B==0) return 0;

        res = onesFrom0(B) - onesFrom0(A-1);
        printf("%llu\n",res);

        A = B = 0;
        scanf("%llu %llu",&A,&B);
    }


}
