#ifndef MSTREET_H
#define MSTREET_H

#include "intersection.h"
#include "semaphore.h"

#include <cstdint>
#include <string>

class Street
{
private:
public:
	std::string name;
	uint32_t length;
	Semaphore semaphore;
	Intersection* intersection_on_start;
	Intersection* intersection_on_end;

	Street(
		Intersection* intersection_on_start,
		Intersection* intersection_on_end,
		std::string name,
		uint32_t length)
		:
		intersection_on_start(intersection_on_start),
		intersection_on_end(intersection_on_end),
		name(name),
		length(length),
		semaphore(Semaphore{})
	{}
};

#endif