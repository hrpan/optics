#include<algorithm>
#include<iostream>
#include "stdio.h"
#include "Point.h"
#include "optics.h"

static int nprocessed = 0;
static int ntotal;

void checkProgress(){
	if(++nprocessed%(ntotal/1000)==0)
		std::cout << "OPTICS Progress:" <<  static_cast<float>(100*nprocessed)/ntotal << "%" << std::endl; 
}


void optics(std::vector<Point> &pts,float eps,int minPTS){
	int nevts=pts.size();
	ntotal=nevts;
	std::cout << "DATA SIZE: " << nevts << std::endl;
	for(int i=0;i<nevts;++i){
		if(!pts[i].processed){
			expandCluster(pts,i,eps,minPTS);
		}
	}
}

void expandCluster(std::vector<Point> &pts, int p_idx, float eps, int minPTS){

	static int ordering=0;

	std::set<int> nbhd=getNBHD(pts,p_idx,eps,minPTS);

	pts[p_idx].processed=true;
	checkProgress();
	pts[p_idx].order=ordering++;

	if(pts[p_idx].core_dist>0){

		std::deque<Point*> seeds;
		update(pts,nbhd,p_idx,seeds);

		while(!seeds.empty()){
			//std::cout << "CURRENT SEED SIZE:" << seeds.size() << std::endl;
			std::deque<Point*>::iterator min_it = std::min_element(seeds.begin(),seeds.end(),ptComp);
			Point *currentPoint = *min_it;
			seeds.erase(min_it);
			std::set<int> nbhd_tmp=getNBHD(pts,(*currentPoint).index,eps,minPTS);
			(*currentPoint).processed=true;
			checkProgress();
			(*currentPoint).order=ordering++;

			if((*currentPoint).core_dist>0)
				update(pts,nbhd_tmp,(*currentPoint).index,seeds);

		}
	}
}



void update(std::vector<Point> &pts,std::set<int> &nbhd,int p_idx,std::deque<Point*> &seeds){

	float core_dist=pts[p_idx].core_dist;

	for(std::set<int>::iterator it=nbhd.begin();it!=nbhd.end();++it){

		if(!pts[*it].processed){

			float reach_dist=std::max(core_dist,dist(pts[*it],pts[p_idx]));
			
			if(pts[*it].reach_dist<0){

				pts[*it].reach_dist=reach_dist;
				seeds.push_back(&pts[*it]);

			}else if(reach_dist<pts[*it].reach_dist){

				pts[*it].reach_dist=reach_dist;

			}
		}

	}
}

std::set<int> getNBHD(std::vector<Point> &pts, int p_idx, float eps, int minPTS){

	const static int npts = pts.size();

	std::vector<float> distVec;
	std::set<int> nbhd;


	for(int i=0;i<npts;++i){
		float d = dist(pts[p_idx],pts[i]);
		if(d<eps&&i!=p_idx){
			nbhd.insert(i);
			distVec.push_back(d);
		}
	}

	if(distVec.size()>minPTS){
		std::nth_element(distVec.begin(),distVec.begin()+minPTS,distVec.end());
		pts[p_idx].core_dist=*(distVec.begin()+minPTS);
	}

	return nbhd;

}










