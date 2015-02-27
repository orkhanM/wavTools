#ifndef WAVEXCEPTION_H
#define WAVEXCEPTION_H
#include <string>
#include <iostream>

class WAV_Exception{
	friend std::ostream &operator <<(std::ostream &os, const WAV_Exception &e){
		os << "error : " << e.msg;
		return os;
	}
public:
	WAV_Exception(std::string msg) : msg(msg) {}
	
private:
	std::string msg;
};


#endif
