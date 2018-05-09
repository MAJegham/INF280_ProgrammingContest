#include <cstdio>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <vector>

using namespace std;


bitset<10000001> P;
vector<long long> premiers;

void initPrimes(long long pmax){ //to pmax excluded
    P.set(); // initialisation
    P[0] = P[1] = 0;
    for (long long i = 2; i< pmax; i++){
        if (P[i]) {
            for (long long j=i*i; j<pmax; j+=i)
                P[j] = 0;
            premiers.push_back(i);
        }
    }
}

int main(){
    initPrimes(50001);

    long m = 0;
    int a =0;
    int b = 0;

    while (true){
        scanf("%ld %d %d",&m,&a,&b);
        if (a==0 && b==0 && m==0)
            return 0;

        long res = 0;
        long w = 0;
        long h = 0;
        for (long q = floor(sqrt((float)b*(float)m/(float)a)) ; q > 1 ;q--){ //h
            //printf("\n a=%d, b=%d, q=%ld => w will start at : %ld",a,b,q,(long)ceil(((float)a/(float)b)*(float)q));
            for (long p = ceil(((float)a/(float)b)*(float)q); p<=q && p*q<=m; p++){ //w
                if (res < p*q && P[p] && P[q]){
                    w = p;
                    h = q;
                    res = p*q;
                    //if(q==211) printf("\n w=%ld , w/h = %f", p,(float)p/(float)q);
                }
            }
        }

        printf("%ld %ld\n",w,h);

    }
}
