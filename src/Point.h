#ifndef POINT_H
#define POINT_H
#include<vector>

struct Point{
	std::vector<float> x;
	float core_dist;
	float reach_dist;
	bool processed;
	int index;
	int order;
};

struct ptComp{
	bool operator()(const Point *p1, const Point *p2){
		return (*p1).reach_dist<(*p2).reach_dist;
	}
};



float dist(Point &p1, Point &p2);
#endif
