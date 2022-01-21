#pragma once

#include <iostream>
#include <string>

namespace AM_common
{
	//searches for a line matching the string str and returns true if found
	bool seek_line(std::istream& stream, const std::string& str, char delim = '\n')
	{
		std::string line;
		while (stream)
		{
			std::getline(stream, line, delim);

			//found line return
			if (line == str)
				return true;
		}

		//did not find line return
		return false;
	}
}