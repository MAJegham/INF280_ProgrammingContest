#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>

using namespace std;

#define N 21
#define MAXN  (1<<21)

queue<pair<int,string> > Q; //pair(Configuration, Strategy to reach it)
vector<int> Adj[N]; //adjacency list of each tree
string result;

void BFS(int root, int n) {
    bool Visited[MAXN] = {};
    for(int i=0; i<MAXN; i++) Visited[i]=false;
    Q = queue<pair<int,string> >();
    Q.push(make_pair(root,""));
    while (!Q.empty()) {
        int config = Q.front().first;
        string strat = Q.front().second;
        Q.pop();
        if (Visited[config])
            continue;
        Visited[config] = true;
        for( int i=0; i<n; i++){ //try shooting on all positions from the given configuration
            if (config & (1<<i)){ //if there might be a monkey behind the target
                string newStrat = strat+" "+to_string(i);
                int lastConfig = config;
                int newConfig = 0;
                for(int j=0; j<n;j++){ //construct the new configuration bit by bit
                    for(int adj : Adj[j]){
                        if (adj!=i && (lastConfig&(1<<adj))){ //if monkey could have been on neighbouring tree (adj) and that tree wasn't shot
                            newConfig = newConfig | (1<<j); //then, he could have jumped from adj to j
                            break;
                        }
                    }
                }
                Q.push(make_pair(newConfig, newStrat ));
                if (newConfig == 0){
                    result = newStrat;
                    return;
                }
            }
            //Q.push(SOMETHING);        // usually do something with v
        }
    }
}


int main(){
    while(true){
        int n=0; //number of trees in the fores
        int m = 0; //number of adjacency relations
        scanf("%d %d",&n,&m);
        if ( (n==0) && (m==0))
            return 0;

        if ( n != m+1 ){ //not an acyclic graphe, supposing connectivity
            for(int i=0;i<m;i++){
                int a = 0;
                int b = 0;
                scanf("%d %d",&a,&b);
            }
            printf("Impossible\n");
            continue;
        }

        for(int i=0; i<n; i++) Adj[i].clear();
        for(int i=0;i<m;i++){
            int a = 0;
            int b = 0;
            scanf("%d %d",&a,&b);
            Adj[a].push_back(b);
            Adj[b].push_back(a);
        }

        result = "";
        BFS( (1<<n)-1 ,n); //start from : all trees are possible
                         //coding possible configurations as Bn,Bn-1,...,B1,B0 : Bi=1 <==> mokey maybe behind tree i
        int l = 0;
        for(int i=0; i< (int)result.length(); i++)
            if (result.at(i) == ' ' ) l++;
        if (l!=0)
            cout << l << ":" << result << endl;
        else printf("Impossible\n");
    }

    return 0;
}


