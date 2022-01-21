#pragma once

#include "meta_arr.h"

//this is garbage

#define DECLARE_FIELD(fieldname, fieldty) struct _FIELD_ ## fieldname { \
	fieldty fieldname; \
	_FIELD_ ## fieldname(fieldty o) {fieldname = o;}\
	_FIELD_ ## fiendname() = default\
};

#define FIELD(fieldname) AM_common::field_unions::field_union<meta::meta_arr<_FIELD_ ## fieldname>>

namespace AM_common { namespace field_unions {
	
	template<typename arr>								struct field_union;
	template<typename t1, typename t2, typename... ts>	struct field_union<meta::meta_arr<t1, t2, ts...>> : public t1, public field_union<meta::meta_arr<t2, ts...>> { };
	template<typename t>								struct field_union<meta::meta_arr<t>> : public t { using t::t; };

	template<typename t1, typename t2>					struct unioner;
	template<typename... ts1, typename... ts2>			struct unioner<field_union<meta::meta_arr<ts1...>>, field_union<meta::meta_arr<ts2...>>> : public field_union<typename meta::arr_union<meta::meta_arr<ts1...>, meta::arr_union<ts2...>>::eval> { };

	template<typename t1, typename t2>					unioner<t1, t2> unite(t1 u1, t2 u2)
	{
		unioner<t1, t2> ret;
		ret = u1;
		ret = u2;
		return ret;
	}
} }