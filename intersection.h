#ifndef MINTERSECTION_H
#define MINTERSECTION_H

#include <cstdint>
#include <vector>

class Street;

class Intersection
{
private:
public:
	uint32_t index;
	std::vector<Street*> streets_in;
	std::vector<Street*> streets_out;

	Intersection(uint32_t index) : index(index)
	{}
};

#endif