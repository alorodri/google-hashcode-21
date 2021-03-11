#ifndef MCAR_H
#define MCAR_H

#include "street.h"

#include <cstdint>
#include <string>
#include <vector>

class Car
{
private:
public:
	std::vector<Street*> path;
	uint32_t time_to_arrive = 0;
	void add_streets_to_path(Street* streets);
};

#endif