#pragma once

#include "unique_id\unique_id.h"
#include <concepts>
#include <cwctype>
#include <type_traits>
#include <numeric>
#include <string>
#include <vector>

namespace AM_common
{
	namespace template_lexer
	{
		struct lexeme;
		struct lexeme_traits;

		template<typename tag>
		struct lexer
		{
			using value_type = lexeme;
			using reference = const lexeme&;
			using pointer = const lexeme*;
			using difference_type = ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;

			std::istream& str;
			lexeme cur;

			reference operator*() const { return cur; }
			lexer& operator++() {}	//usr define
			lexer operator++(int) { auto tmp = *this; ++(*this); return tmp; }
		};
	}
}