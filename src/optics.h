#ifndef OPTICS_H
#define OPTICS
#include<vector>
#include<set>
#include<queue>
#include "Point.h"

void optics(std::vector<Point> &pts, float eps, int minPTS);
void update(std::vector<Point> &pts, std::set<int> nbhd, int p_idx, std::set<Point*,ptComp> seed, float eps, int minPTS);
std::set<int> getNBHD(std::vector<Point> &pts, int p_idx, float eps, int minPTS);

#endif
