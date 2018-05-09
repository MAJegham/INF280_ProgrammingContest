#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility> 

using namespace std;

int main()
{

    int n_x =0;
    int n_y =0;
    float w =0;
    float p = 0;
    bool rep = true;
    vector<pair<float,float> > V;
    while (true){
        rep = true;

        scanf("%d %d %f", &n_x, &n_y, &w );
        if ( (n_x == 0) && (n_y==0) && (w==0) )
            return 0;

        V.clear();
        for (int i=0; i<n_x; i++){
            scanf("%f ", &p);
            V.push_back(make_pair(p-w/2,p+w/2));
        }

        sort(V.begin(),V.end());
        if ( ( V[0].first > 0) || (V[V.size()-1].second < 75) )
            rep = false;
        if (rep)
            for (int i = 0; i<V.size()-1; i++)
            {
                if ( V[i].second < V[i+1].first )
                    rep = false;
            }
        if (rep)
        {
            V.clear();
            for (int i=0; i<n_y; i++)
            {
                scanf("%f ", &p);
                V.push_back(make_pair(p-w/2,p+w/2));
            }
            sort(V.begin(),V.end());
            if ( ( V[0].first > 0) || (V[V.size()-1].second < 100))
                rep = false;
            if (rep)
                for (int i = 0; i<V.size()-1; i++)
                {
                    if ( V[i].second < V[i+1].first )
                        rep = false;
                }
        }
        else
        {
            for (int i=0; i<n_y; i++)
            {
                scanf("%f ", &p);
            }
        }

        if (rep)
            printf("YES\n");
        else
            printf("NO\n");

    }
    return 0;
}
