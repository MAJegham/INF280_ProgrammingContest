#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cmath>

#define MAXL 2147483000
using namespace std;

vector<pair<long, pair<int,int> > > Edges;
set<pair<int,int> > A;  // Final minimum spanning tree

// ----------------------------- UNION FIND ---------------------------
map<int, pair<int,unsigned int> > Sets;  // map to parent & rank

void MakeSet(int x) {
    Sets.insert(make_pair(x, make_pair(x, 0)));
}

int Find( int x) {
    if (Sets[x].first == x)
        return x;              // Parent == x ?
    else
        return Sets[x].first = Find(Sets[x].first);  // Get Parent
}

void Union( int x, int y) {
    int parentX = Find(x), parentY = Find(y);
    int rankX = Sets[parentX].second, rankY = Sets[parentY].second;
    if (parentX == parentY)
        return ;
    else if (rankX < rankY)
        Sets[parentX].first = parentY;
    else
        Sets[parentY].first = parentX;
    if (rankX == rankY)
        Sets[parentX].second++;
}

// ----------------------------- MST ---------------------------
long Kruskal(int n_nodes) {
    long min_w = 0;
    //if ((int)covered.size() == n_nodes)
    //  return min_w; //ie 0
    for(auto tmp : Edges) {
        auto edge = tmp.second;
        if (Find(edge.first) != Find(edge.second)) {
            Union(edge.first, edge.second);       // update Union-Find
            A.insert(edge);                     // include edge in MST

            min_w +=  tmp.first;
        }
        if ((int)A.size() == n_nodes-1)
          break;
    }
    return min_w;
}




int main(){
    int T = 0;
    scanf("%d",&T);

    for(int t = 0; t<T; t++){

        if (t>0)
            printf("\n");
        Edges.clear();
        int n =0; //number of cities
        int q =0; //available subnets
        scanf("%d %d",&n,&q);

        long cost_ [q];
        vector<pair<int,int> > subnets [q];
        for(int i = 0; i<q; i++){
            subnets[i].clear();
        }
        //Subnets infos
        for(int i = 0; i<q; i++){
            int n_ = 0;
            scanf("%d",&n_);
            int cities [n_];
            long c_ = 0;
            scanf("%ld",&c_);
            cost_[i] = c_;
            for(int j = 0; j<n_; j++){
                int id = 0;
                scanf("%d",&id);
                cities[j] = id;
            }
            for(int j=0;j<n_-1;j++){
                subnets[i].push_back(make_pair(cities[j],cities[j+1]));
            }
        }

        //Cities coords
        pair<int,int> coords [n+1];
        for(int i = 1; i<n+1; i++){
            int x =0;
            int y =0;
            scanf("%d %d",&x,&y);
            coords[i] = make_pair(x,y);
        }

        //Edges list
        for(int i=1; i<n+1; i++){
            for(int j=i; j<n+1; j++){
                long d = (long)(pow((coords[i].first - coords[j].first),2)) +
                        (long)(pow(coords[i].second - coords[j].second,2));
                if (i!=j)
                    Edges.push_back(make_pair(d,make_pair(i,j)));
            }
        }
        sort(Edges.begin(), Edges.end());      // Sort edges by weight

        long min_w = MAXL;
        for(int i=pow(2,q)-1; i>=0;i--){ //different combinations for choosing the subnets
            long sub_c = 0;
            Sets.clear();
            A.clear();

            for( int u=1; u < n+1; u++) // Initialize Union-Find
                MakeSet(u);

            int decision [q]; //which subnets are chosen
            for(int j=0; j<q;j++){
                decision[j] = (i>>j)&1;
            }

            for(int j=0; j<q;j++){
                if ( decision[j] == 1 ){  //for chosen nets
                    sub_c += cost_[j];

                    for(int k=0; k<(int)subnets[j].size();k++){ //add the subnets edges to A and nodes to covered
                        if (Find(subnets[j][k].first) != Find(subnets[j][k].second)){
                            Union(subnets[j][k].first, subnets[j][k].second);
                            A.insert(subnets[j][k]);
                        }

                    }
                }
            }

            long w = Kruskal(n);

            min_w = min(min_w,w+sub_c);

        }

        printf("%ld\n",min_w);


    }
    return 0;
}
