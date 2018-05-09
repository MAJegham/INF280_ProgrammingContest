#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

#define EPS 10-06

struct point {
    double x, y;
    point() { x=0.0; y=0.0; }
    point(double in_x, double in_y): x(in_x), y(in_y) {}
    bool operator == (point pt2) const {
        return (fabs(x - pt2.x) < EPS
                && (fabs(y - pt2.y) < EPS));
    }
    bool operator < (const point & p){
        if (x==p.x)
            return (y<p.y);
        else
            return x <p.x ;
    }
};

double cross( const point &O, const point &A, const point &B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y -O.y) * (B.x-O.x);
}

//source : https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain#C++
vector<point> convexHull(vector<point> P){
    int n = P.size(),k =0;
    vector<point> H(2*n);
    sort(P.begin(), P.end());
    for( int i =0; i< n; i++){
        while( k>=2 && cross(H[k-2], H[k-1] , P[i]) <= 0) //virage a droite
            k--;
        H[k++] = P[i];
    }
    for( int i=n-1, t=k+1; i>=0; --i){
        while( k>=t && cross(H[k-2], H[k-1] , P[i]) <= 0)
            k--;
        H[k++] = P[i];
    }
    H.resize(k); return H;
}

struct vecteur {
    double x,y;
    vecteur() {}
    vecteur(point a, point b): x(b.x-a.x), y(b.y-a.y) {}
    double scalaire(vecteur v){
        return x*v.x + y*v.y;
    }
    double vectoriel(vecteur v){
        return x*v.y - y*v.x;
    }
    double norme(){
        return hypot(x,y);
    }
};

double distance(point P, point A, vecteur u){
    vecteur AP = vecteur(A,P);
    return fabs(AP.vectoriel(u)) / u.norme();
}

vector<point> polygon;
vector<point> convpol;

int main(){
    int t=0;
    while (true){
        t++;
        int n =0;
        scanf("%d",&n);
        if (n==0) return 0;

        //read input
        polygon.clear();
        convpol.clear();
        for (int i=0; i<n; i++){
            int xi , yi;
            scanf("%d %d",&xi,&yi);
            polygon.push_back(point(xi,yi));
        }

        convpol = convexHull(polygon);
        int nn = convpol.size();
        /*for(auto i : convpol){
            printf("- %f,%f -",i.x,i.y);
        }*/

        //Algo
        double res = 100000;
        for(int i=0; i<nn-1; i++){
            //printf("\n%d",i);
            int i1 = i+1;
            //point p0 = polygon[i];
            //point p1 = polygon[i1];
            point A = convpol[i];
            vecteur u = vecteur(A,convpol[i1]);

            double d = 0;
            for (int p=0; p<nn; p++ ){
                if (p==i || p==i1) continue;


                double d_ = distance(convpol[p],A,u);
                //      printf("\ndistance between %d-%d and %d : %f",i,i1,p,d_);
                if (d_ > d) d = d_;
            }
            res = min(res,d);
        }

        printf("Case %d: %.2f\n",t,ceilf(res * 100) / 100);
    }
}
