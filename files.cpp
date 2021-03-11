#include "files.h"

template<>
int Files::from_string(const std::string& str)
{
	return std::stoi(str);
}

template<>
std::string Files::from_string(const std::string& str)
{
	return str;
}

void Files::parse(const uint32_t line_number, const std::string& str, Data& data)
{
	uint32_t& simulation_seconds = data.header[0];
	uint32_t& intersections = data.header[1];
	uint32_t& streets = data.header[2];
	uint32_t& cars = data.header[3];
	uint32_t& points_per_car = data.header[4];

	if (line_number == 0)
	{
		std::vector<int> splitted_header = split<int>(str, ' ');
		simulation_seconds = splitted_header[0];
		intersections = splitted_header[1];
		streets = splitted_header[2];
		cars = splitted_header[3];
		points_per_car = splitted_header[4];
	}
	else if (line_number <= streets)
	{
		std::vector<std::string> splitted_streets = split<std::string>(str, ' ');
		uint32_t index_of_intersection_on_street_starts = std::stoi(splitted_streets[0]);
		uint32_t index_of_intersection_on_street_ends = std::stoi(splitted_streets[1]);
		std::string street_name = splitted_streets[2];
		uint32_t street_length = std::stoi(splitted_streets[3]);

		Intersection* intersection_on_start;
		Intersection* intersection_on_end;
		// must check if intersection exists to pass by ref to street, not need to duplicate them
		if (intersection_cache.count(index_of_intersection_on_street_starts))
		{
			intersection_on_start = intersection_cache.at(index_of_intersection_on_street_starts);
		}
		else {
			intersection_on_start = new Intersection{index_of_intersection_on_street_starts};
			intersection_cache.insert(std::pair<uint32_t, Intersection*>(intersection_on_start->index, intersection_on_start));
		}

		if (intersection_cache.count(index_of_intersection_on_street_ends))
		{
			intersection_on_end = intersection_cache.at(index_of_intersection_on_street_ends);
		}
		else {
			intersection_on_end = new Intersection{index_of_intersection_on_street_ends};
			intersection_cache.insert(std::pair<uint32_t, Intersection*>(intersection_on_end->index, intersection_on_end));
		}

		Street* street = new Street(
		intersection_on_start,
		intersection_on_end,
		street_name,
		street_length );

		intersection_on_start->streets_out.push_back(street);
		intersection_on_end->streets_in.push_back(street);

		data.streets.push_back(street);
		data.intersections.insert(intersection_on_start);
		data.intersections.insert(intersection_on_end);

		street_cache.insert(std::pair<std::string, Street*>(street->name, street));
	}
	else if (line_number <= cars + streets)
	{
		std::vector<std::string> splitted_cars = split<std::string>(str, ' ');

		Car* car = new Car();
		uint32_t number_of_streets_on_car = std::stoi(splitted_cars[0]);
		for (uint32_t i = 1; i <= number_of_streets_on_car; ++i)
		{
			car->add_streets_to_path(street_cache.at(splitted_cars[i]));
		}

		data.cars.push_back(car);

	}
	else
	{
		std::cerr << "Parsing more lines than the file should have" << "\n";
		std::cin.get();
		std::abort();
	}
}

Data& Files::read(const std::string filename, Data& data)
{
	std::fstream sfile;
	sfile.open(filename, std::ios::in);
	std::ostringstream ss{};

	if (sfile)
	{
		std::string str;
		uint32_t line_number = 0;
		while (std::getline(sfile, str))
		{

			parse(line_number, str, data);

			std::cout << str << "\n";
			++line_number;
		}

	}
	else {
		// debug file not found
		std::cout << "file not found" << "\n";
	}

	sfile.close();
	return data;
}

uint32_t count_intersections_with_active_semaphores(const std::set<Intersection*>& intersections)
{
	uint32_t count = 0;
	for (auto intersection : intersections)
	{
		bool has_active = false;
		for (auto street : intersection->streets_in)
		{
			if (street->semaphore.secs_on > 0)
			{
				has_active = true;
			}
		}

		if (has_active)
		{
			++count;
		}
	}

	return count;
}

uint32_t count_streets_with_active_semaphores(const std::vector<Street*>& streets_in)
{
	uint32_t count = 0;
	for (auto street : streets_in)
	{
		if (street->semaphore.secs_on > 0)
		{
			++count;
		}
	}
	return count;
}

void Files::writeOutput(const std::string filename, const Data& data)
{
	std::fstream file;
	file.open(filename + ".out", std::ios::out);

	if (file)
	{
		file << count_intersections_with_active_semaphores(data.intersections) << "\n";
	
		for (const Intersection* intersection : data.intersections)
		{
			uint32_t streets_count_semaphores_active = count_streets_with_active_semaphores(intersection->streets_in);

			if (streets_count_semaphores_active > 0)
			{
				file << intersection->index << "\n";

				file
				<< streets_count_semaphores_active
				<< "\n";
			}

			for (const Street* street : intersection->streets_in)
			{
				if (street->semaphore.secs_on > 0)
				{
					file << street->name << " " << street->semaphore.secs_on << "\n";
				}
			}
		}
	}

	file.close();
}