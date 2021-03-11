#include "algorithm.h"

#include <algorithm>
#include <cstdint>
#include <map>
#include <vector>

void HashcodeAlgorithm::compute(Data& data)
{
	//compute_all_1s(data);
	prioritize_cars_with_most_length(data);
}

void HashcodeAlgorithm::compute_all_1s(Data& data)
{
	for (Intersection* intersection : data.intersections)
	{
		for (Street* street : intersection->streets_in)
		{
			street->semaphore.secs_on = 1;
		}
	}
}

void HashcodeAlgorithm::prioritize_cars_with_most_length(Data& data)
{
	struct WeightedStreet
	{
		uint32_t weight;
		Street* street;
		std::vector<uint32_t> seconds_at_car_will_pass;

		inline bool operator<(const WeightedStreet& ws) const
		{
			return street < ws.street;
		}
	};

	std::map<Street*, WeightedStreet> wstreets;

	std::sort(data.cars.begin(), data.cars.end(), [](Car* c1, Car* c2) {
		return c1->time_to_arrive > c2->time_to_arrive;
	});

	for (auto pc : data.cars)
	{
		uint32_t length_accumulated = 0;
		for (auto street : pc->path)
		{
			WeightedStreet ws{};

			ws.street = street;
			ws.seconds_at_car_will_pass.push_back(length_accumulated);
			ws.weight += pc->time_to_arrive;

			if (wstreets.count(ws.street))
			{
				wstreets[ws.street].weight += ws.weight;
			}
			else {
				wstreets.insert(std::pair<Street*, WeightedStreet>(ws.street, ws));
			}
		}
	}

	using my_pair = std::pair<Street*, WeightedStreet>;

	std::vector<my_pair> wstreets_ordered;

	uint32_t total_weight = 0;
	for (auto& entry : wstreets)
	{
		total_weight += entry.second.weight;
		wstreets_ordered.push_back(entry);
	}

	uint32_t median = total_weight / wstreets_ordered.size();
	for (auto& entry : wstreets_ordered)
	{
		float relation = entry.second.weight / median;

		entry.second.street->semaphore.secs_on = retrieve_seconds_by_relation(relation);
	}
}
