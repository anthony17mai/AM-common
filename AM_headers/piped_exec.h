#pragma once

#include <fstream>

namespace AM_common
{
	//opens a pipe to executing command
	void piped_exec(const char* command, std::fstream& out_stream, const char* openmode = "rw")
	{
		//not sure why there is an underscore before popen
		out_stream = std::fstream(_popen(command, openmode));
	}
}