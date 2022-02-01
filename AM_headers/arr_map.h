#pragma once

#include <functional>

namespace AM_common
{
	template<typename ts, size_t arrlen>
	void arr_map(ts input[arrlen], ts output[arrlen], std::function<ts(ts)> map)
	{
		for (int id = 0; id < arrlen; id++)
		{
			output[id] = map(input[id]);
		}
	}
}