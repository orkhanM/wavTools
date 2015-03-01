#ifndef WAVPARSE_H
#define WAVPARSE_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "wavexception.h"

class WavParse{
public:
	WavParse(const std::string &filename);
	void loadSampleV(const std::string &filename);
	void exportWAVdat(const std::string &filename); 
	std::vector<double> sampleV;
};

#endif
