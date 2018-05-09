
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

//DP solution

int main(){
    int K = 0;
    scanf("%d",&K);


    for (int i=0; i<K; i++){

        int C = 0;
        scanf("%d",&C);

        long N = 0;
        scanf("%ld",&N);


        vector<pair<long,int> > optimal; //better use heap for minimum
        optimal.clear();
        optimal.reserve((N+2));
        vector<pair<int,int> > dests;
        dests.clear();
        dests.reserve(N+2);
        vector<int > cumweights;
        cumweights.clear();
        cumweights.reserve(N+2);
        vector<long > cumdistc;
        cumdistc.clear();
        cumdistc.reserve(N+2);

        dests.push_back(make_pair(0,0));
        cumweights.push_back(0);
        cumdistc.push_back(0);
        for (long j = 0; j<N; j++){

            int x = 0;
            scanf("%d",&x);
            int y = 0;
            scanf("%d",&y);
            int c = 0;
            scanf("%d",&c);

            dests.push_back(make_pair(x,y));
            cumweights.push_back(c+cumweights[j]);
            cumdistc.push_back(cumdistc[j]+abs(x-dests[j].first)+abs(y-dests[j].second));
        }

        optimal.push_back(make_pair(0,0));

        for (long j= 1; j<=N; j++){

            int w = cumweights[j]-cumweights[j-1];
            vector<pair<long,int> > options;
            options.clear();

            //go back then deliver
            long f = optimal[j-1].first + (dests[j-1].first+dests[j-1].second) + (dests[j].first+dests[j].second);
            options.push_back(make_pair(f, w));

            //try to deliver without going back
            if (optimal[j-1].second + w <= C){
                f = optimal[j-1].first + cumdistc[j] - cumdistc[j-1];
                options.push_back(make_pair(f, optimal[j-1].second + w));
                optimal[j] = *min_element(options.begin(), options.end()); // not sure we should conclude and continue here
                continue;
            }

            //check other possible combinations
            for(long k=1;k<j;k++){
                if ( (cumweights[j]-cumweights[j-k-1])<=C ){
                    f = optimal[j-k-1].first +
                            (dests[j-k-1].first+dests[j-k-1].second) +
                            (dests[j-k].first+dests[j-k].second) +
                            (cumdistc[j] - cumdistc[j-k]);
                    options.push_back(make_pair(f, cumweights[j]-cumweights[j-k-1] ));
                }
                else
                    break;
            }
            optimal[j] = *min_element(options.begin(), options.end());

        }

        printf("%ld",(optimal[N].first + dests[N].first + dests[N].second ));
        if (i == K-1)
            printf("\n");
        else
            printf("\n\n");
    }

    return 0;
}























