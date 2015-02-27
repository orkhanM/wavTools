#ifndef TIMER_EXCEPTION_H
#define TIMER_EXCEPTION_H

#include <iostream>
#include <string>

class TimerException{
	friend std::ostream &operator <<(std::ostream &os, const TimerException e){
		std::cerr << " *** TIMER EXCEPTION *** " << e.message;
		return os;
	}
public:
	TimerException(std::string message) : message(message) {}
private:
	std::string message;
};


#endif
