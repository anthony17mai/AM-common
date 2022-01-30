#pragma once

#include <utility>

//utility struct that overloads + and - operators
namespace AM_common
{
	namespace util
	{
		//+
		template<typename t1, typename t2> struct p_pair : public std::pair<t1, t2> 
		{
			p_pair operator+(const p_pair& o) const { return p_pair(this->first + o.first, this->second + o.second); }
			using std::pair<t1, t2>::pair;
		};
		//- unary
		template<typename t1, typename t2> struct n_pair : public std::pair<t1, t2>
		{
			n_pair operator-() const { return n_pair(-this->first, -this->second); }
			using std::pair<t1, t2>::pair;
		};
		//+, - unary
		template<typename t1, typename t2> struct npm_pair : public std::pair<t1, t2>
		{
			npm_pair operator-() const { return npm_pair(-this->first, -this->second); }
			npm_pair operator+(const npm_pair& o) const { return npm_pair(this->first + o.first, this->second + o.second); }
			npm_pair operator-(const npm_pair& o) const { return *this + (-o); }
			using std::pair<t1, t2>::pair;
		};

		// *k
		template<typename t1, typename t2, typename k_ty> struct k_pair : public std::pair<t1, t2>
		{
			k_pair operator*(k_ty k) const { return k_pair(k * this->first, k * this->second); }
			using std::pair<t1, t2>::pair;
		};
		// +, *k, k: signed
		template<typename t1, typename t2, typename k_ty> struct npmk_pair : public std::pair<t1, t2>
		{
			npmk_pair operator+(const npmk_pair& o) const { return npmk_pair(this->first + o.first, this->second + o.second); }
			npmk_pair operator*(k_ty k) const { return npmk_pair(k * this->first, k * this->second); }

			npmk_pair operator-() const { return *this * (k_ty)(-1); }
			npmk_pair operator-(const npmk_pair& o) const { return *this + (-o); }
			
			using std::pair<t1, t2>::pair;
		};

		template<typename t1, typename t2>
		struct def_pair_hash
		{
			inline size_t operator()(const std::pair<t1, t2>& pair)
			{
				return std::hash<decltype(pair.first)>(pair.first) ^ (std::hash<decltype(pair.second)>(pair.second) << (4 * sizeof(size_t)));
			}
		};
	}
}

template<typename t1, typename t2> struct std::hash<AM_common::util::n_pair<t1, t2>> : AM_common::util::def_pair_hash<t1, t2>{ };
template<typename t1, typename t2> struct std::hash<AM_common::util::p_pair<t1, t2>> : AM_common::util::def_pair_hash<t1, t2>{ };
template<typename t1, typename t2> struct std::hash<AM_common::util::npm_pair<t1, t2>> : AM_common::util::def_pair_hash<t1, t2>{ };
template<typename t1, typename t2, typename k_ty> struct std::hash<AM_common::util::k_pair<t1, t2, k_ty>> : AM_common::util::def_pair_hash<t1, t2>{ };
template<typename t1, typename t2, typename k_ty> struct std::hash<AM_common::util::npmk_pair<t1, t2, k_ty>> : AM_common::util::def_pair_hash<t1, t2>{ };