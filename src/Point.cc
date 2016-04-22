#include "Point.h"
#include<cmath>



float dist(Point &p1, Point &p2){
	int nComp = p1.x.size();
	float dist=0;
	for(int i=0;i<nComp;++i)
		dist+=(p1.x[i]-p2.x[i])*(p1.x[i]-p2.x[i]);
	return sqrt(dist);
}


