#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <SDL/SDL.h>

#include "timer.h"
#include "timer_exception.h"

using namespace std;

int main() {
	try{
		Timer* timer = new Timer();
		timer->start();
		while(timer->secondsElapsed() != 10){
			SDL_Delay(1000);
			cout << *timer << endl;
		}
		timer->stop();
		delete timer;
	}catch(TimerException e){
		cerr << e;
		exit(1);
	}	

	return 0;
}
