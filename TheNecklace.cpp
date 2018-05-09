#include <cstdio>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> Adj[51];
vector<int> Circuit;

void Hierholzer(int v) {
    stack <int> Stack;
    Stack.push(v);
    while (!Stack.empty()) {
        if (!Adj[v].empty()) { // follow edges until stuck
            Stack.push(v);
            int tmp = *Adj[v].begin();
            Adj[v].erase(Adj[v].begin()); // remove edge, modifying graph
            //Adj[tmp].erase(v);
            auto it = std::find(Adj[tmp].begin(),Adj[tmp].end(),v);
            Adj[tmp].erase(it);
            v = tmp;
        }
        else{ // got stuck: stack contains a circuit
            Circuit.push_back(v); // append node at the end of circuit
            v = Stack.top(); // backtrack using stack, find larger circuit
            Stack.pop();
        }
    }
}



int main(){

    int T = 0;
    scanf("%d",&T);

    for (int t=0; t<T;t++){
        if (t>0)
            printf("\n");
        printf("Case #%d\n",t+1);

        int occ[51];
        fill_n((int*)occ,51,0);
        for (int j=0; j<51; j++){
            Adj[j].clear();
        }

        int N = 0;
        scanf("%d",&N);

        for (int j = 0; j<N; j++){
            int c1 = 0;
            int c2 = 0;
            scanf("%d %d",&c1,&c2);
            occ[c1] += 1;
            occ[c2] += 1;
            Adj[c1].push_back(c2);
            Adj[c2].push_back(c1);
        }

        int start = 0;
        bool possible = true;
        for(int j=1; j<51; j++){
            if (occ[j] != 0)
                start = j;
            if (occ[j] & 1){ //there's a node with odd degree
                printf("some beads may be lost\n");
                possible = false;
                break;
            }
        }

        if (possible){
            Circuit.clear();
            Hierholzer(start);
            for (int j = 0; j<(int)Circuit.size()-1; j++){
                printf("%d %d\n", Circuit[j], Circuit[j+1]);
            }
        }
    }

    return 0;
}


