#ifndef MDATA_H
#define MDATA_H

#include "car.h"
#include "intersection.h"
#include "street.h"

#include <cstdint>
#include <iostream>
#include <set>
#include <vector>

struct Data
{
	// seconds, intersections, streets, cars, points per car
	uint32_t header[5]{ 0 };
	std::set<Intersection*> intersections;
	std::vector<Street*> streets;
	std::vector<Car*> cars;

	Data() = default;
	Data& operator=(Data& data) = delete;
	Data(const Data& data) = delete;

	~Data()
	{
		// free memory
		for (auto intersection : intersections)
		{
			delete intersection;
		}
		intersections.clear();

		for (auto street : streets)
		{
			delete street;
		}
		streets.clear();

		for (auto car : cars)
		{
			delete car;
		}
		cars.clear();
	};
};

#endif