#ifndef MALGORITHM_H
#define MALGORITHM_H

#include "data.h"
#include "files.h"

class HashcodeAlgorithm
{
private:
	inline uint32_t retrieve_seconds_by_relation(const float relation)
	{
		return std::ceil(relation);
	}
public:
	void compute(Data& data);
	void compute_all_1s(Data& data);
	void prioritize_cars_with_most_length(Data& data);
};

#endif