#ifndef MTIME_H
#define MTIME_H

#include <cstdint>

struct SimulationTime
{
	inline static uint32_t& get_step()
	{
		static uint32_t step;
		return step;
	}
};

#endif