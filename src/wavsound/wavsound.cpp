#include "wavsound.h"

WavSound::WavSound(const std::string &filename) {
	try{
		this->loadWAV(filename);
	}catch(WAV_Exception e){
		std::cerr << e << std::endl;
	}
}

WavSound::~WavSound(){
	alDeleteSources(1,&sourceid);
	alDeleteSources(1,&this->bufferid);
	alcDestroyContext(context);
	alcCloseDevice(device);
	delete sampleBuffer;	
}	

void WavSound::printWAVinfo(){
	std::cout << "sample rate\t:\t" << sampleRate
		<< "\nsample size\t:\t" << sampleSize
		<< "\nnum samples\t:\t" << numSamples
		<< "\nbyte rate\t:\t" << byteRate
		<< "\nnum channels\t:\t" << numChannels
		<< "\nbits per sample\t:\t" << bitsPerSample
	;
}
void WavSound::loadWAV(const std::string &filename){
	char buffer[4];
	std::ifstream in(filename.c_str(), std::ios::binary);
	if(!in){
		throw WAV_Exception("WAV file cannot be found");
	}
	in.read(buffer, 4);				
	if(strncmp(buffer, "RIFF", 4) != 0){
		in.close();
		throw WAV_Exception("File is not \"RIFF\"");
	}
	in.read(buffer,4); 			 
	in.read(buffer,4); 			
	if(strncmp(buffer, "WAVE", 4) != 0){
		in.close();
		throw WAV_Exception("Wrong file format");
	}
	in.read(buffer,4);
	in.read(buffer,4); 
	if(convertToInt(buffer,4) != 16){
		in.close();
		throw WAV_Exception("Invalid PCM format");
	}
	in.read(buffer,2); 	
	if(convertToInt(buffer,2) != 1){
		in.close();
		throw WAV_Exception("PCM is not formatted for linear quantization.");
	}
	in.read(buffer,2); 					
	this->numChannels = this->convertToInt(buffer,2);
	in.read(buffer,4);					
	this->sampleRate = this->convertToInt(buffer,4);
	in.read(buffer,4);					
	this->byteRate = this->convertToInt(buffer,4);
	in.read(buffer,2);				
	this->blockAlign = this->convertToInt(buffer,2);
	in.read(buffer,2);	
	this->bitsPerSample = this->convertToInt(buffer,2);
	in.read(buffer,4);		
	in.read(buffer,4);
	int size = convertToInt(buffer,4);
	this->sampleBuffer = new char[size];
	in.read(this->sampleBuffer,size);
	this->sampleSize = this->bitsPerSample/8;
	this->numSamples = size/this->sampleSize;
	in.close();
/*---------------------------------------------------------------
		INITIALIZE SOUND CARD
---------------------------------------------------------------*/
	this->device = alcOpenDevice(NULL);	
	if(this->device == NULL){
		throw WAV_Exception("cannot open sound card");
	}
	context = alcCreateContext(this->device,NULL);
	if(this->context == NULL){
		throw WAV_Exception("cannot open context");
	}
	alcMakeContextCurrent(this->context);
/*-------------------------------------------------------------
		SET BUFFER ID	
-------------------------------------------------------------*/
	alGenBuffers(1,&(this->bufferid));
/*-------------------------------------------------------------
		DECIDE AUDIO FORMAT
-------------------------------------------------------------*/
	if(this->numChannels == 1){
		if(this->bitsPerSample == 8){
			this->format = AL_FORMAT_MONO8;
		}else{
			this->format = AL_FORMAT_MONO16;
		}
	}else{
		if(this->bitsPerSample == 8){
			this->format = AL_FORMAT_STEREO8;
		}else{
			this->format = AL_FORMAT_STEREO16;
		}	
	}
}

void WavSound::playWAV(){
	alBufferData(this->bufferid,
			this->format,
			this->sampleBuffer,
			this->numSamples*this->sampleSize,
			this->sampleRate
	);
	std::cerr << "\n\n" << (((double)this->numSamples/(double)this->sampleRate)/this->numChannels)*1000;
	alGenSources(1,&this->sourceid);
	alSourcei(this->sourceid,AL_BUFFER,this->bufferid);
	alSourcePlay(sourceid);
	SDL_Delay( (((double)this->numSamples/(double)this->sampleRate)/this->numChannels)*1000);

	alDeleteSources(1,&sourceid);
	alDeleteSources(1,&this->bufferid);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

int WavSound::convertToInt(char *buffer, int len){
	int a = 0;
	if(!this->isBigEndian())
		for(int i = 0; i < len; i++)
			((char*)&a)[i] = buffer[i];
	else
		for(int i = 0; i < len; i++)
			((char*)&a)[3-i] = buffer[i];
	return a;
}


bool WavSound::isBigEndian(){
	int a = 1;
	return !((char*)&a)[0];
}
