//g++ -o main openal.cpp wavsound/wavsound.o -lopenal -lSDL
#include <iostream>
#include "wavsound.h"
#include "wavexception.h"
#include "wavparse.h"

using namespace std;

int main()
{
	try{
		WavSound s("./audio/hello.wav");
		s.printWAVinfo();
		s.playWAV();
	}catch(WAV_Exception e){
		cout << e;
	}
	return 0;
}
