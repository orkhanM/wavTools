#ifndef WAVSOUND_H
#define WAVSOUND_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <AL/al.h>
#include <AL/alc.h>
#include <SDL/SDL.h>
#include "wavexception.h"


class WavSound{
public:
	WavSound();
	WavSound(const std::string &filename);
	void printWAVinfo();
	void loadWAV(const std::string &filename);
	void playWAV();
	~WavSound();
private:
	ALCdevice *device;
	ALCcontext *context;
	char* sampleBuffer;
	std::string format_type;
	unsigned int bufferid, format, sourceid;
	int sampleRate, sampleSize, numSamples, byteRate, bitsPerSample, numChannels, blockAlign;
	bool PCM_LINEAR;
	bool isBigEndian();
	int convertToInt(char *buffer, int len);
};
#endif
