#include <cstdio>
#include <cmath>
#include <algorithm>
#define EPS 1e-06
using namespace std;

struct point {
    double x, y;
    point() { x=0.0; y=0.0; }
    point(double in_x, double in_y): x(in_x), y(in_y) {}
    bool operator == (point pt2) const {
        return (fabs(x - pt2.x) < EPS
                && (fabs(y - pt2.y) < EPS));
    }
};

bool verify(double a_, int i){
    return ( (fabs(fmod(a_,180./i)) < EPS) || (fabs(fmod(a_,180./i) - 180./i) < EPS) ); //fabs(fmod(a_,180./i) - 180./i) cause fmod(45.,45) -> 45 -_-
}

int main(){
    double x1 , y1 ;
    while ( scanf("%lf %lf",&x1,&y1) ){
        point pt1 = point(x1,y1);
        double x2,y2;
        scanf("%lf %lf",&x2,&y2);
        point pt2 = point(x2,y2);
        double x3,y3;
        scanf("%lf %lf",&x3,&y3);
        point pt3 = point(x3,y3);

        double a = hypot(pt2.x-pt3.x,pt2.y-pt3.y);
        double b = hypot(pt1.x-pt3.x,pt1.y-pt3.y);
        double c = hypot(pt1.x-pt2.x,pt1.y-pt2.y);

        double a_ = acos((c*c+b*b-a*a)/(2*c*b)) *180./M_PI;
        double b_ = acos((a*a+c*c-b*b)/(2*a*c)) *180./M_PI;
        double c_ = acos((a*a+b*b-c*c)/(2*a*b)) *180./M_PI;

        //bool found = false;
        for (int i=3; i<1001; i++){
            if (  verify(a_,i) && verify(c_,i) && verify(b_,i)){
                printf("%d\n",i);
                //found = true;
                break;
            }
        }
        //if (!found) printf("Not Found\n");
    }

}
