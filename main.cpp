#include "algorithm.h"
#include "data.h"
#include "files.h"

#include <cassert>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

enum class File
{
	FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F
};

const std::string get_filename(File f);

void do_algorithm(const std::string filename)
{
	Data data;
	HashcodeAlgorithm algorithm;
	Files file_utils;
	file_utils.read(filename, data);
	algorithm.compute(data);
	file_utils.writeOutput(filename, data);
}

int main()
{
	do_algorithm(get_filename(File::FILE_A));
	do_algorithm(get_filename(File::FILE_B));
	do_algorithm(get_filename(File::FILE_C));
	do_algorithm(get_filename(File::FILE_D));
	do_algorithm(get_filename(File::FILE_E));
	do_algorithm(get_filename(File::FILE_F));
	std::cin.get();
}

const std::string get_filename(File f)
{
	switch(f)
	{
	case File::FILE_A:
		return std::string(c_files::RESOURCES_FOLDER) + "a.txt";
	case File::FILE_B:
		return std::string(c_files::RESOURCES_FOLDER) + "b.txt";
	case File::FILE_C:
		return std::string(c_files::RESOURCES_FOLDER) + "c.txt";
	case File::FILE_D:
		return std::string(c_files::RESOURCES_FOLDER) + "d.txt";
	case File::FILE_E:
		return std::string(c_files::RESOURCES_FOLDER) + "e.txt";
	case File::FILE_F:
		return std::string(c_files::RESOURCES_FOLDER) + "f.txt";
	default:
		assert(false);
	}
}