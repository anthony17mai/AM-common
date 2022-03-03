#pragma once

#include <iterator>

//for when c++ also needs to be prolog-like

namespace AM_common
{
	namespace meta
	{
		template<int lim, typename... ts>
		concept count_lt = sizeof...(ts) < lim;
	}
}