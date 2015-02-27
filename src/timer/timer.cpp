#include "timer.h"
#include "timer_exception.h"


std::ostream &operator <<(std::ostream &os, const Timer &t){
	os << t.hour << ":" << t.minute << ":" << t.second << ":" << t.tick ;
	return os;
}


Timer::Timer() : startCounter(0), stopUpdate(false) {fe_0 = new std::thread(&Timer::update,this);}

Timer::~Timer(){
	this->fe_0->join();
	this->stopUpdate = true;	
}

void Timer::start(){
	if(this->startCounter > 0) throw TimerException("Timer already started"); 
	this->timerStart = clock();
	this->startCounter++;
}

void Timer::stop(){
	if(this->startCounter == 0) throw TimerException("Timer not yet started");
	this->timerEnd = clock();
	this->duration = this->timerEnd - this->timerStart;
	this->tick = this->ticks();
	this->second = this->seconds();
	this->minute = this->minutes();
	this->hour = this->hours();
} 

int Timer::ticks() {
	return this->duration % CLOCKS_PER_SEC;
}

int Timer::seconds() {
	return this->duration / CLOCKS_PER_SEC % 60;
}

int Timer::minutes() {
	return this->duration / CLOCKS_PER_SEC / 60 % 60;
}

int Timer::hours() {
	return this->duration / CLOCKS_PER_SEC / 60 / 60;
}

int Timer::secondsElapsed(){
	return (clock() - this->timerStart)/ CLOCKS_PER_SEC % 60;
}

int Timer::ticksElapsed(){
	return (clock() - this->timerStart) & CLOCKS_PER_SEC;
}

int Timer::minutesElapsed() {
	return (clock() - this->timerStart) / CLOCKS_PER_SEC / 60 % 60;
}

int Timer::hoursElapsed() {
	return (clock() - this->timerStart) / CLOCKS_PER_SEC / 60 / 60;
}
void Timer::update(){
	while(!this->stopUpdate){
		hour = hoursElapsed();
		minute = minutesElapsed();
		second = secondsElapsed();
		tick = ticksElapsed();		
	}
}
