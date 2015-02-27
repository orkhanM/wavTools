#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <thread>
#include <ctime>
#include "timer_exception.h"

class Timer{
	friend std::ostream &operator <<(std::ostream &os, const Timer &t);
public:
	Timer();
	~Timer();
	void start();	
	void stop();
	int minutesElapsed();
	int hoursElapsed();
	int secondsElapsed();
	int ticksElapsed();
private:
	int ticks();
	int seconds();
	int minutes();
	int hours();
	void update();
	bool stopUpdate;
	int hour, minute, second, tick, startCounter;
	clock_t timerStart, timerEnd, duration;
	std::thread *fe_0;
};


#endif
