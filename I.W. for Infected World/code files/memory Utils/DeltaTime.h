#ifndef DELTATIME_H
#define DELTATIME_H


#include "umbrella headers/memory.h"

#include "umbrella headers/sfml.h"



class DeltaTime final
{
public:

	DeltaTime() = default;


	void reset()
	{
		clock.reset();
	}
	
	void restart()
	{
		clock.restart();
	}

	void start()
	{
		clock.start();
	}

	void stop()
	{
		clock.stop();
	}


	const Time& getEllapsedTime() const
	{ 
		return clock.getElapsedTime();
	}


private:

	Clock clock;
	
};
#endif // DELTATIME_H