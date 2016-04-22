#include<iostream>
#include "Reader.h"
#include "Point.h"
#include "optics.h"
using namespace std;

int main(){

	vector<Point> pts;

	Reader reader("./input/input");

	reader.Initialize();

	reader.ptsInit(pts);

	optics(pts,reader.getEPS(),reader.getMINPTS());	
	
	reader.treeFill(pts);

	reader.closeFiles();

	
}
