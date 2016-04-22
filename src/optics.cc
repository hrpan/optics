#include<vector>
#include<set>
#include<algorithm>
#include<iostream>
#include "Point.h"
#include "optics.h"

float getProgress(int curr, int total){
	return static_cast<float>(100*curr)/total;
}


void optics(std::vector<Point> &pts,float eps,int minPTS){
	int order=0;
	int nevts=pts.size();
	for(int i=0;i<nevts;++i){
		if(i%(nevts/30)==0)
			std::cout << "OPTICS PROGRESS:" << getProgress(i,nevts) << "%" << std::endl;
		if(!pts[i].processed){
			pts[i].processed=true;
			std::set<int> nbhd = getNBHD(pts,i,eps,minPTS);
			pts[i].order=order++;
			if(pts[i].core_dist!=-1){
				std::set<Point*,ptComp> seeds;
				update(pts,nbhd,i,seeds,eps,minPTS);
				while(!seeds.empty()){
					std::set<Point*,ptComp>::iterator it=seeds.begin();
					std::set<int> nbhd_tmp=getNBHD(pts,(**it).index,eps,minPTS);
					(**it).processed=true;
					(**it).order=order++;
					if((**it).core_dist!=-1)
						update(pts,nbhd_tmp,(**it).index,seeds,eps,minPTS);
				}
			}	
		}
	}
}

void update(std::vector<Point> &pts,std::set<int> &nbhd,int p_idx,std::set<Point*,ptComp> seeds, float eps, int minPTS){
	float core_dist=pts[p_idx].core_dist;
	for(std::set<int>::iterator it=nbhd.begin();it!=nbhd.end();++it){
		if(!pts[*it].processed){
			float reach_dist=std::max(core_dist,dist(pts[*it],pts[p_idx]));
			if(pts[*it].reach_dist==-1){
				pts[*it].reach_dist=reach_dist;
				seeds.insert(&pts[*it]);
			}else if(reach_dist<pts[*it].reach_dist){
				pts[*it].reach_dist=reach_dist;
				seeds.erase(&pts[*it]);
				seeds.insert(&pts[*it]);
			}
		}
	}
}

std::set<int> getNBHD(std::vector<Point> &pts, int p_idx, float eps, int minPTS){

	const static int npts = pts.size();

	std::vector<float> distVec;
	std::set<int> nbhd;

	int count=0;

	for(int i=0;i<npts;++i){
		float d = dist(pts[p_idx],pts[i]);
		if(d<eps&&i!=p_idx){
			nbhd.insert(i);
			++count;
		}
		distVec.push_back(d);
	}

	if(count>minPTS){
		sort(distVec.begin(),distVec.end());
		pts[p_idx].core_dist=distVec[minPTS];
	}

	return nbhd;

}










