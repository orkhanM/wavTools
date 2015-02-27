#include "wavparse.h"

WavParse::WavParse(const std::string &f){
	this->loadSampleV(f);
}

void WavParse::exportWAVdat(const std::string &filename){
	std::ofstream wavout(filename.c_str());
	if(!wavout){
		throw WAV_Exception("error writing WAV data");	
	}
	wavout << std::setprecision(15) << std::showpoint;
	for(std::vector<double>::iterator it=sampleV.begin(); it != sampleV.end(); ++it){
		wavout << *it << "\n";
	}
	wavout.close();
	return;
}



void WavParse::loadSampleV(const std::string &filename){

	int i = system(("octave src/wavparse/audio.m "+filename).c_str()); 

	while(i != 0){}

	std::ifstream in("src/wavparse/wav.dat");
	if(!in){
		throw WAV_Exception("SampleV Error");
	}
	std::string line;
	while(getline(in,line)){
		this->sampleV.push_back(atof(line.c_str()));
	}
	in.close();
}


