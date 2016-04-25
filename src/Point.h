#ifndef POINT_H
#define POINT_H
#include<vector>

static std::vector<float> weight;

struct Point{
	std::vector<float> x;
	float core_dist;
	float reach_dist;
	bool processed;
	int index;
	int order;
};

bool ptComp(Point *p1, Point *p2);

void setWeight(std::vector<float> &w);

float dist(Point &p1, Point &p2);
#endif
