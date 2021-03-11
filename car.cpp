#include "car.h"

void Car::add_streets_to_path(Street* street)
{
	path.push_back(street);
	if (path.size() != 1)
	{
		// don't have to sum the length of the first street
		time_to_arrive += street->length;
	}
}