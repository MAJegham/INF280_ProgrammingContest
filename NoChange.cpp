#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main (){
    int N=0;
    int x = 0;
    int k = 0;
    int v =0;
    bool a1 = false;
    int a21 = 0;
    int a22 = 0;
    vector<int> V;
    vector<vector<pair<bool,pair<int,int> > > > a;
    vector<pair<bool,pair<int,int> > > l;
    scanf("%d",&N);

    for (int count=0; count<N; count++){
        scanf("%d",&x);
        scanf("%d",&k);

        V.clear();
        for (int j=0; j<k;j++){
            scanf("%d",&v);
            V.push_back(v);
        }

        a.clear();
        l.clear();

        for (int j=0;j<=x;j++){
            a22 = 10000;
            if (j < V[0]){
                a1 = false;
                a21 = 0;
            }
            else{
                a1 = (j%V[0] == 0);
                if (a1)
                    a21 = j / V[0];
                else
                    a21 = 0;
            }
            l.push_back(make_pair(a1,make_pair(a21,a22)));
        }
        a.push_back(l);

        for (int i=1;i<k;i++){
            l.clear();
            for (int j=0;j<=x;j++){
                if(j < V[i]){
                    a22 = a[i-1][j].second.first;
                    a1 = a[i-1][j].first;
                    a21 = 0;
                }
                else{
                    a22 = max(a[i-1][j].second.first, l[j-V[i]].second.second);
                    a21 = 0;
                    if (a[i-1][j].first){
                        a1 = true;
                    }
                    else if ( (l[j-V[i]].first) &&
                              (l[j-V[i]].second.first < l[j-V[i]].second.second) ){
                        a1 = true;
                        a21 = l[j-V[i]].second.first + 1;
                    }
                    else
                        a1 = false;
                }

                l.push_back(make_pair(a1,make_pair(a21,a22)));

            }
            a.push_back(l);
        }

        if (a[k-1][x].first)
            printf("YES\n");
        else
            printf("NO\n");
        if (count < N-1)
            printf("\n");
    }

    return 0;
}
