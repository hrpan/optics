#include "Reader.h"
#include<iomanip>
#include<cmath>

Reader::Reader(std::string ifname){
	input.open(ifname.c_str());
	std::cout << "Reading arguments from: " << ifname << std::endl;
}


void Reader::Initialize(){
	std::string tmp;
	input >> tmp;
	inputFileName=tmp;
	std::cout << "Input TFile: " << inputFileName << std::endl;
	input >> tmp;
	inputTreeName=tmp;
	std::cout << "Input TTree: " << inputTreeName << std::endl;
	input >> tmp;
	outputFileName=tmp;
	std::cout << "Output TFile: " << outputFileName << std::endl;
	input >> tmp;
	outputTreeName=tmp;
	std::cout << "Output TTree: " << outputTreeName << std::endl;
	input >> eps >> minPTS;
	std::cout << "EPS: " << eps << " minPTS: " << minPTS << std::endl;
	input >> nVar;
	std::cout << "NUMBER OF VARIABLES: " << nVar << std::endl;
	
	std::vector<float> w(nVar,0);
	for(int i=0;i<nVar;++i){
		input >> tmp >> w[i];
		std::cout << "SETTING VARIABLE" << i+1 << ": " << std::setw(5) << tmp << " WEIGHT: " << w[i] << std::endl;
		varName.push_back(tmp);
	}		

	setWeight(w);
	var.resize(nVar,0);
	sum.resize(nVar,0);
	sumsq.resize(nVar,0);
	sigma.resize(nVar,0);

	std::cout << "READER INITIALIZATION COMPLETE" << std::endl;
	setTrees();
}

void Reader::setFiles(){
	f_in = new TFile(inputFileName,"READ");
	f_out = new TFile(outputFileName,"CREATE");

	outputFileName.ReplaceAll(".root","");

	while(!f_out->IsOpen()){

		static int counts=0;
		TString newOFName=TString::Format("%s_%d.root",outputFileName.Data(),++counts);
		std::cout << "Switching output file to: " << newOFName <<std::endl;
		f_out = new TFile(newOFName);

	}

	std::cout << "FILE SETTING COMPLETE" << std::endl;
}

void Reader::setTrees(){
	tr_in = (TTree*) f_in->Get(inputTreeName);
	tr_out = new TTree(outputTreeName,"Output from optics");

	for(int i=0;i<nVar;++i)
		tr_in->SetBranchAddress(varName[i].c_str(),&var[i]);	

	tr_out->Branch("order",&order);
	tr_out->Branch("r_dist",&r_dist);
	tr_out->Branch("c_dist",&c_dist);
	std::cout << "BRANCH SETTING COMPLETE" << std::endl;
}

void Reader::ptsInit(std::vector<Point> &pts){
	int n = tr_in->GetEntries();
	for(int i=0;i<n;++i){
		Point p_tmp;
		tr_in->GetEntry(i);
		for(int j=0;j<nVar;++j){
			p_tmp.x.push_back(var[j]);		
			sum[j]+=var[j];
			sumsq[j]+=var[j]*var[j];
		}
		p_tmp.processed=false;
		p_tmp.core_dist=-1;
		p_tmp.reach_dist=-1;
		p_tmp.index=i;
		pts.push_back(p_tmp);
	}
	std::cout << "POINTS INITIALIZATION COMPLETE" << std::endl;
	ptsNorm(pts);
}

void Reader::ptsNorm(std::vector<Point> &pts){
	int n = pts.size();
	for(int i=0;i<nVar;++i)
		sigma[i]=sqrt((sumsq[i]-sum[i]*sum[i]/n)/(n-1));
	
	for(int i=0;i<n;++i)
		for(int j=0;j<nVar;++j)
			pts[i].x[j]/=sigma[j];
	std::cout << "POINTS NORMALIZATION COMPLETE" << std::endl;
}

void Reader::treeFill(std::vector<Point> &pts){
	int n = pts.size();
	for(int i=0;i<n;++i){
		order=pts[i].order;
		r_dist=pts[i].reach_dist;
		c_dist=pts[i].core_dist;
		tr_out->Fill();
	}
	std::cout << "TREE FILLING COMPLETE" << std::endl;
}

void Reader::closeFiles(){
	f_in->Close();
	f_out->Write();
	f_out->Close();	
}

float Reader::getEPS(){
	return eps;
}

int Reader::getMINPTS(){
	return minPTS;
}
