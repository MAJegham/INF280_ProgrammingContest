#include <cstdio>
#include <queue>
#include <algorithm>

#define MAXLEN 10000

using namespace std;

typedef pair<unsigned int, int> WeightNode;


int main(){
    while (true){
        int N = 0;
        int M = 0;
        scanf("%d %d",&N,&M);

        if (N==0 && M==0)
            return 0;

        int S = 0;
        int D = 0;
        scanf("%d %d",&S,&D);

        //Creating graph
        vector<int> Inc [N];
        vector<int> Adj [N];
        int W [N][N];
        fill_n((int *)W, N*N, MAXLEN);

        for (int i=0; i<M; i++){
            int U = 0;
            int V = 0;
            int P = 0;
            scanf("%d %d %d",&U,&V,&P);
            Inc[V].push_back(U);
            Adj[U].push_back(V);
            W[U][V] = P;
        }

        //Dijkstra to initialise Dist[]
        priority_queue <WeightNode, vector<WeightNode>,greater<WeightNode> > Q;
        long Dist [N];
        fill_n((long *)Dist, N, MAXLEN);
        Dist[S] = 0;
        Q.push(make_pair(0, S));
        while (!Q.empty()) {
            int u = Q.top().second; // get node with least priority
            Q.pop();
            for(auto v : Adj[u]) {
                unsigned int weight = W[u][v];
                if (Dist[v] > Dist[u] + weight){ // shorter path found?
                    Dist[v] = Dist[u] + weight;
                    Q.push(make_pair(Dist[v], v)); // simply push, no update here
                }
            }
        }

        //Eliminate shortest paths
        priority_queue <WeightNode> pQ; //maximum queue
        pQ.push(make_pair(Dist[D],D));
        while(!pQ.empty()){
            int v = pQ.top().second;
            pQ.pop();
            for (auto u : Inc[v]){
                if(Dist[u]+W[u][v] == Dist[v]){
                    Adj[u].erase(remove(Adj[u].begin(), Adj[u].end(), v), Adj[u].end());
                    if (u != S)
                        pQ.push(make_pair(Dist[u],u));
                }
            }
        }

        //Now we calculate Almost Shortest Path
        Q = priority_queue <WeightNode, vector<WeightNode>,greater<WeightNode> > (Q); //Q.clear();
        fill_n((long *)Dist, N, MAXLEN);
        Dist[S] = 0;
        Q.push(make_pair(0, S));
        while (!Q.empty()) {
            int u = Q.top().second; // get node with least priority
            Q.pop();
            for(auto v : Adj[u]) {
                unsigned int weight = W[u][v];
                if (Dist[v] > Dist[u] + weight){ // shorter path found?
                    Dist[v] = Dist[u] + weight;
                    Q.push(make_pair(Dist[v], v)); // simply push, no update here
                }
            }
        }

        if ( Dist[D] == MAXLEN )
            printf("-1\n");
        else
            printf("%ld\n",Dist[D]);

    }



    return 0;
}























