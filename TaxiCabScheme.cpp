#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

#define MAXX 505
#define MAXY 505

/********** Hopcroft-Karp (data structures) **************/
// Artificial node (unused otherwise) -- end of augmenting path
#define NIL 0
// "Infinity", i.e., value larger than min(|X|, |Y|)
#define INF 505
// Partitions X and Y
vector<int> X, Y;
// Neighbors in Y of nodes in X
vector<int> Adj[MAXX];
// Matching X-Y and Y-X
int PairX[MAXX];
int PairY[MAXY];
// Augmenting path lengths
unsigned int Dist[MAXX];

/********** Hopcroft-Karp (BFS)  *************************/
bool BFS() {
    queue<int> Q;
    Dist[NIL] = INF;
    for(auto x : X) { // start from nodes that are not yet matched
        Dist[x] = (PairX[x] == NIL) ? 0 : INF;
        if (PairX[x] == NIL)
            Q.push(x);
    }
    while(!Q.empty()) {         // find all shortest paths to NIL
        int x = Q.front();    Q.pop();
        if (Dist[x] < Dist[NIL])  // can this become a shorter path?
            for ( auto y : Adj[x])
                if(Dist[PairY[y]] == INF) {
                    Dist[PairY[y]] = Dist[x] + 1;    // update path length
                    Q.push(PairY[y]);
                }
    }
    return Dist[NIL] != INF;    // any shortest path to NIL found?
}

/********** Hopcroft-Karp (DFS)  *************************/
bool DFS(int x) {
    if (x == NIL)
        return true;                                  // reached NIL
    for (auto y : Adj[x])
        if (Dist[PairY[y]] == Dist[x] + 1 &&
                DFS(PairY[y])) {                  // follow trace of BFS
            PairX[x] = y;          // add edge from x to y to matching
            PairY[y] = x;
            return true;
        }
    Dist[x] = INF;
    return false;                      // no augmenting path found
}

/********** Hopcroft-Karp (main) *************************/
int HopcroftKarp() {
    int Matching = 0;         // count number of edges in matching
    while
            (BFS()) {          // find all shortest augmenting paths
        for(auto x : X)               // update matching cardinality
            if (PairX[x] == NIL &&        // node not yet in matching?
                    DFS(x))         // does an augmenting path start at x?
                Matching++;
    }
    return Matching;
}



int dur(pair<int , int> s, pair<int , int> d){
    return abs(s.first-d.first) + abs(s.second-d.second);
}

int main(){
    int C =0;
    scanf("%d",&C);
    for (int c =0; c <C; c++){
        int T =0;
        scanf("%d",&T);

        X.clear();
        Y.clear();
        for (int i=0; i<MAXX; i++) Adj[i].clear();
        int tim [T+1];
        pair<int , int> dep [T+1];
        pair<int , int> arr [T+1];
        tim[0] = 0;
        dep[0] = make_pair(0,0);
        arr[0] = make_pair(0,0);
        for (int t =1; t <=T; t++){
            int h=0; int m=0;
            int xd=0; int yd=0;
            int xa=0; int ya=0;
            scanf("%2d:%2d %d %d %d %d",&h,&m,&xd,&yd,&xa,&ya);
            tim[t] = 60*h+m;
            dep[t] = make_pair(xd,yd);
            arr[t] = make_pair(xa,ya);
        }

        bool pushed_j [T+1]; for (int t =1; t <=T; t++) pushed_j[t] = false;

        for (int i=1; i<=T;i++) {
            bool pushed = false;
            for (int j=i+1; j<=T;j++) {
                if ((tim[i] + dur(dep[i],arr[i]) + dur(arr[i],dep[j])) < tim[j] ){
                    Adj[i].push_back(j);
                    if (!pushed_j[j]){
                        Y.push_back(j);
                    }
                    if (!pushed){
                        X.push_back(i);
                    }
                }
            }
        }

        fill_n(PairX, MAXX, NIL);    // initialize: empty matching
        fill_n(PairY, MAXY, NIL);
        int m = 0;
        m = HopcroftKarp();
        printf("%d\n",T-m);

    }


    return 0;
}
