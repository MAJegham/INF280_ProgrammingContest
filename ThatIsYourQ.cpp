#include <cstdio>
#include <list>
#include <algorithm>
#include <utility>

using namespace std;

int main()
{
    int P = 0;
    int C = 0;
    char c = 0;
    int t = 0;
    int cas = 1;
    list<int> Q;
    list<int>::iterator it;

    while (true){
        Q.clear();
        scanf("%d %d", &P, &C);

        if (P==0 && C==0){
            return 0;
        }


        printf("Case %d:\n",cas);
        cas++;

        if (P <= C)
        {
            for(int i=1; i<=P; i++)
                Q.push_back(i);

            for (int i=0; i<C; i++)
            {
                scanf(" %c",&c);
                if (c == 'N' ){
                    t = Q.front();
                    printf("%d\n",t);
                    Q.push_back(t);
                    Q.pop_front();
                }
                else{
                    scanf(" %d",&t);
                    //Q.remove(t);
                    it = find(Q.begin(),Q.end(),t);
                    if (it != Q.end())
                      Q.erase(it);
                    Q.push_front(t);
                }
            }
        }
        else
        {
            for(int i=1; i<=C; i++)
                Q.push_back(i);

            for (int i=0; i<C; i++)
            {
                scanf(" %c",&c);
                if (c == 'N'){
                    t = Q.front();
                    printf("%d\n",t);
                    Q.push_back(t);
                    Q.pop_front();
                }
                else{
                    scanf(" %d",&t);
                    //Q.remove(t);
                    it = find(Q.begin(),Q.end(),t);
                    if (it != Q.end())
                      Q.erase(it);
                    Q.push_front(t);
                }
            }
        }

        if (cas > 10)
            return 0;
    }

    return 0;
}
