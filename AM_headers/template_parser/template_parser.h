#pragma once

#include "unique_id/unique_id.h"
#include <iostream>
#include <vector>

namespace AM_common
{
	/*
	Algorithm: 
		start with an initial symbolid.
		lookup symbol id to find a recipe list.
		use the recipes to preform DFS:
			try to 
	*/
	namespace template_parser
	{
		struct default_parser_tag {};

		template<typename tag>
		struct parse_node {};
		template<typename tag>
		struct dynam_sem_node {};
		template<typename symb, typename tag> requires(symbol<symb, tag>)
		struct dynam_sem
		{
			static_assert(false, "a symbol requires dynamic semantics");
		};

		template<typename T, typename tag>
		concept symbol = requires(T a)
		{
			{ dynam_sem<T, tag>::sem(parse_node<tag>()) } -> std::convertible_to<dynam_sem_node<tag>>;
		};

		template<typename tag> struct symbol_table
		{
			using fctn_entry = int;
			static inline std::vector<fctn_tab> tab;
		};
		template<typename symb, typename tag> struct _add_entry
		{
			using lab = unique_id::type_label<symb, tag>;
			_add_entry() {
				symbol_table<tag>::tab.push_back(0);

#ifdef DEBUG_TEMPLATE_PARSER
				if (symbol_table<tag>::tab.size() != lab::label_type::lab_val)
					throw -1;
#endif // DEBUG_TEMPLATE_PARSER
			}
		};
		template<typename symb, typename tag> struct table_entry : unique_id::type_label<symb, tag>
		{

		};

		template<typename symb, typename = void> struct symbol_traits { static_assert(false, "Symbols must have stuff i think") };
		template<typename symb> struct symbol_traits<symb, std::void_t<typename symb::result_type>>
		{
			using result_type = symb::result_type;
		};

		//forms a parse rule
		template<typename... symb> struct composite {};

		template<typename symb, typename parse_rule, typename tag = default_parser_tag> struct parser;
		template<typename symb, typename tag, typename... symbols> struct parser<symb, composite<symbols...>, tag>
		{
			
		};

		/*
		template<typename symbol> struct parse_node
		{
			unique_id::unique_label<symbol, size_t> label;
			//std::vector<
		};
		*/
	}
}