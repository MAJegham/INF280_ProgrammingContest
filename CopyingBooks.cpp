#include <cstdio>
#include <list>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

int main(){
    int N =0;
    scanf("%d",&N);

    for (int count = 0; count < N; count++){

        int m = 0;
        scanf("%d",&m);
        int k = 0;
        scanf("%d",&k);

        int tot = 0;
        vector<int> books;
        books.clear();
        books.reserve(m+3);
        priority_queue<int,vector<int>,greater<int> > q;
        int p = 0;
        for(int i=0;i<m;i++){
            scanf("%d",&p);
            tot += p;
            books.push_back(p);
            q.push(p);
        }

        int b = tot / k;
        int B = tot-(k-1)*q.top(); //tot
        int charge = b;
        vector<vector<int> > rep;
        do{
            rep.clear();
            rep.reserve(k);

            bool works = false;
            int ind = m-1;
            for(int i=0; i<k; i++){
                vector<int> l;
                l.clear();
                int load = 0;

                while(ind>=k-i-1 && load+books[ind] <= charge){
                    load+=books[ind];
                    l.push_back(books[ind]);
                    ind--;
                }

                rep.push_back(l);

                if (ind<0 && i==k-1){
                    works = true;
                    break;
                }
            }

            if(works){ //ind<0 && works
                B = charge;
                charge = (B+b)/2;
                //current charge can partition the books
                //break;
                if (B==b)
                    break;
            }
            else{
                //charge = meanch + q.top();
                //q.pop();
                b = charge+1;
                charge = (b+B)/2;
            }

        }while(true);

        for(int i=0; i<rep.size(); i++){
            for(int j=0; j< rep[rep.size()-1-i].size();j++){
                if (i==rep.size()-1 && j==rep[rep.size()-1-i].size()-1)
                    printf("%d",rep[rep.size()-1-i][rep[rep.size()-1-i].size()-1-j]);
                else
                    printf("%d ",rep[rep.size()-1-i][rep[rep.size()-1-i].size()-1-j]);
            }
            if (i+1<rep.size())
                printf("/ ");
        }
        printf("\n");

    }
    return 0;
}







