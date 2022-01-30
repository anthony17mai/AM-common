#pragma once

#include <limits>

namespace AM_common
{
	namespace util
	{
		template<typename integ> constexpr inline integ circ_lsh(integ val, unsigned int shamt)
		{
			static_assert(!std::numeric_limits<integ>::is_signed, "type of val should be unsigned");
			const unsigned int mask = (CHAR_BIT * sizeof(val) - 1);		//utilize the assumption that the bit size of integ is guarenteed to be a power of 2 - creates a mask which will truncate bits from the shiftammount
			return (val << (shamt & mask)) | (val >> (-shamt) & mask);	//this line brilliantly reinterprets a negative number into a positive number within the range by truncating bits
		}
		template<typename integ> constexpr inline integ circ_rsh(integ val, unsigned int shamt)
		{
			static_assert(!std::numeric_limits<integ>::is_signed, "type of val should be unsigned");
			const unsigned int mask = (CHAR_BIT * sizeof(val) - 1);		//utilize the assumption that the bit size of integ is guarenteed to be a power of 2 - creates a mask which will truncate bits from the shiftammount
			return (val >> (shamt & mask)) | (val << (-shamt) & mask);	//this line brilliantly reinterprets a negative number into a positive number within the range by truncating bits
		}
	}
}