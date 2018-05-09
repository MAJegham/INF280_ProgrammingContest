#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

#define PI 3.14159265358979323846

using namespace std;

struct point{
    double x,y,z; //they are int but we'll use them as floats
    double r;
} pos[8];

double getRadius(point cp, vector<point> bal){
    //bal := already used positions
    //other ballons constraints
    double m = numeric_limits<double>::max();
    for (int i=0; i<bal.size();i++){
        double temp = pow( pow((cp.x-bal[i].x), 2) + pow((cp.y-bal[i].y), 2) + pow((cp.z-bal[i].z), 2), 0.5) - bal[i].r;
        if (temp <= 0){
            return 0;
        }
        if (temp < m ){
            m = temp;
        }
    }
    return m;
}


int main(){
    int n = 0;
    point c1;
    point c2;
    int B = 0;

    while ( true ){
        //number of points
        scanf("%d",&n);
        if ( n == 0 )
            return 0;

        //Box counter
        B++;

        //corners
        scanf("%lf %lf %lf", &c1.x,&c1.y,&c1.z);
        scanf("%lf %lf %lf", &c2.x,&c2.y,&c2.z);

        //number of possible positions
        int sz = 0;

        for (int i=0; i<n; i++){
            point p;
            scanf("%lf %lf %lf", &p.x,&p.y,&p.z);
            //check if point is in box then add it
            if ( (p.x < max(c1.x,c2.x)) && (p.x > min(c1.x,c2.x))
                 &&(p.y < max(c1.y,c2.y)) && (p.y > min(c1.y,c2.y))
                 &&(p.z < max(c1.z,c2.z)) && (p.z > min(c1.z,c2.z)) ){
                sz++;
                // set default radius to the borders constraint
                p.r = min({fabs(p.x-c1.x) , fabs(p.y-c1.y) , fabs(p.z-c1.z) ,
                           fabs(p.x-c2.x) , fabs(p.y-c2.y) , fabs(p.z-c2.z)});
                pos[sz-1] = p;
            }
        }

        double max_cov = 0;
        int per [sz];
        for(int i=0;i<sz;i++)
            per[i]=i;

        do{ //for each possible order
            vector<point> bal; //balloons used
            bal.clear();
            bal.reserve(sz);
            double covered = 0;

            for (int i=0; i<sz; i++){ //for each position
                point cp = pos[per[i]];
                cp.r = min( pos[per[i]].r, getRadius(cp,bal));
                if (cp.r > 0){
                    covered += 4.0/3.0*PI*pow(cp.r , 3);
                    bal.push_back(cp);
                }
                else
                    break;
            }
            if (covered > max_cov )
                max_cov = covered;
        }while(next_permutation(per,per+sz));

        double noc = (fabs(c1.x-c2.x) * fabs(c1.y-c2.y) * fabs(c1.z-c2.z) ) - max_cov;
        printf("Box %d: %.0f\n\n",B,round(noc));

    }


    return 0;
}











