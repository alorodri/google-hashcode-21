#ifndef MSEMAPHORE_H
#define MSEMAPHORE_H

#include <cstdint>

class Semaphore
{
private:
public:
	bool light = false;

	// by def all semaphores have 0s (lights off)
	uint32_t secs_on = 0;
};

#endif