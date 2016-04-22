#ifndef READER_H
#define READER_H
#include "TFile.h"
#include "TTree.h"
#include "Point.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>

class Reader{
	private:
		float eps;
		int minPTS;
		int nVar;
		int order;
		float r_dist;
		std::string inputFileName;
		std::string inputTreeName;
		std::string outputFileName;
		std::string outputTreeName;
		TFile *f_in;
		TFile *f_out;
		TTree *tr_in;
		TTree *tr_out;
		std::ifstream input;

		std::vector<std::string> varName;	
		std::vector<float> var;
		std::vector<float> sum;
		std::vector<float> sumsq;
		std::vector<float> sigma;
	public :
		Reader(std::string);
		void Initialize();
		void setTrees();
		void ptsInit(std::vector<Point> &pts);
		void ptsNorm(std::vector<Point> &pts);
		void treeFill(std::vector<Point> &pts);
		void closeFiles();
		float getEPS();
		int getMINPTS();
};


#endif 
