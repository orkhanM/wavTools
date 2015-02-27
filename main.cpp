//g++ -o main openal.cpp wavsound/wavsound.o -lopenal -lSDL
#include <iostream>
#include "src/wavsound/wavsound.h"
#include "src/wavexception.h"
#include "src/wavparse/wavparse.h"

using namespace std;

int main()
{
	try{
		WavSound s("./audio/hello.wav");
		s.playWAV();
	}catch(WAV_Exception e){
		cout << e;
	}
	return 0;
}
