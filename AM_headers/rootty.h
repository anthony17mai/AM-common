#pragma once

namespace AM_common
{
	namespace meta
	{
		template<typename t>
		struct rootty { using eval = t; };
		template<typename t>
		struct rootty<t*> { using eval = typename rootty<t>::eval; };
		template<typename t>
		struct rootty<t&> { using eval = typename rootty<t>::eval; };
		template<typename t>
		struct rootty<t&&> { using eval = typename rootty<t>::eval; };

		template<typename t>
		struct unref { using eval = t; };
		template<typename t>
		struct unref<t&> { using eval = t; };
		template<typename t>
		struct unref<t&&> { using eval = t; };

		template<typename t, typename _rootty = typename rootty<t>::eval> struct is_const : std::false_type {};
		template<typename t1, typename t2> struct is_const<t1, const t2> : std::true_type {};
	}
}