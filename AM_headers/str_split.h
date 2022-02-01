#pragma once

#include <vector>
#include <string>

//TODO: DO REWORK

namespace AM_common
{
	//splits using delim
	//skips empties
	//new strings as opposed to shallow coppies - which somtimes might be preferable
	void str_split(const std::string& str, std::vector<std::string>& out, char delim = ' ')
	{
		size_t id = 0;

		do
		{
			//get the substring
			size_t j = str.find(delim, id);
			std::string s = str.substr(id, j - id);
			id = j + 1;	//intended overflow

			//if substring is empty then skip
			if (str.length() == 0)
			{
				continue;
			}
			//if not empty then add to vector
			else
			{
				out.push_back(s);
				continue;
			}
		} while (id != 0);
	}

	//finds the first occurance of delim and splits the string excluding the delimeter
	void str_divide(const std::string& str, std::vector<std::string>& out, char delim = ' ')
	{
		size_t divide = str.find(delim, 0);
		std::string first = str.substr(0, divide);
		out.push_back(first);
		//this is probably branch free
		divide = (divide == std::numeric_limits<size_t>::max()) ? str.size() : divide + 1;
		std::string second = str.substr(divide);
		out.push_back(second);
	}

	std::string _trim_front(const std::string& str, char delim)
	{
		size_t id = 0;
		while (id < str.size() && str[id] == delim)
		{
			id++;
		}
		return str.substr(id);
	}
	std::string _trim_back(const std::string& str, char delim)
	{
		size_t j = str.size();
		while (j > 0 && str[j - 1] == delim)
		{
			j--;
		}
		return str.substr(0, j);
	}
	std::string str_trim(const std::string& str, char delim = ' ')
	{
		return _trim_back(_trim_front(str, delim), delim);
	}
}