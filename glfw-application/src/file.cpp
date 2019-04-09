#include "file.h"

#include <fstream>

std::string file_get_contents(const char* file)
{
	std::ifstream in(file);
	std::string contents;

	while (in.good()) {
		std::string line;
		std::getline(in, line);
		contents.append(line + "\n");
	}

	return contents;
}