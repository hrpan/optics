#include "Point.h"
#include<cmath>

bool ptComp(Point *p1, Point *p2){
	return (*p1).reach_dist<(*p2).reach_dist;
}

float dist(Point &p1, Point &p2){
	int nComp = p1.x.size();
	float dist=0;
	for(int i=0;i<nComp;++i)
		dist+=(p1.x[i]-p2.x[i])*(p1.x[i]-p2.x[i]);
	return sqrt(dist);
}


