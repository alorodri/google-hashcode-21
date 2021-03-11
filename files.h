#ifndef MFILES_H
#define MFILES_H

#include "data.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct Output;

namespace c_files
{
	const std::string RESOURCES_FOLDER = "resources/";
}

class Files
{
private:
	void parse(const uint32_t line_number, const std::string& str, Data& data);
	std::map<uint32_t, Intersection*> intersection_cache;
	std::map<std::string, Street*> street_cache;

public:

	template<typename T>
	static T from_string(const std::string& str);

	template<typename T>
	static auto split(const std::string& str, const char separator)
	{
		std::vector<T> vs;
		std::ostringstream ss{};
		for (char c : str)
		{
			if (c == separator)
			{
				vs.push_back(from_string<T>(ss.str()));
				ss.clear();
				ss.str("");
			}
			else {
				ss << c;
			}
		}
		vs.push_back(from_string<T>(ss.str()));

		return vs;
	}

	Data& read(const std::string filename, Data& data);
	void writeOutput(const std::string filename, const Data& data);
};

#endif