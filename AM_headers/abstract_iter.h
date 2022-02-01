#pragma once

#include <typeinfo>
#include "rootty.h"
#include <iterator>

namespace AM_common
{
	template<typename t, typename difference = std::ptrdiff_t, bool _const = false>
	class abstract_fw_iter_base
	{
	public:
		//bool indicating whether or not to use a const iterator
		using reference = typename std::conditional<_const, const t&, t&>::type;
		using pointer = typename std::conditional<_const, const t*, t*>::type;

		//only make the necessary functions abstract - these functions would be overloaded regardless
		//of wheter or not this object was implemented as an iterator
		virtual reference operator*() const = 0;
		virtual void next() = 0;
		virtual bool operator==(const abstract_fw_iter_base&) const = 0;
	};

	template<typename t, typename difference = std::ptrdiff_t, bool _const = false>
	class abstract_fw_iter
	{
	public:
		using base = abstract_fw_iter_base<t, difference, _const>;

		using iterator_category = std::forward_iterator_tag;
		using value_type = t;
		using reference = typename base::reference;
		using pointer = typename base::pointer;
		using difference_type = difference;

		base* _base;

		reference operator*() const { return *(*_base); }

		abstract_fw_iter& operator++() { _base->next(); return *this; }
		abstract_fw_iter operator++(int) { auto cpy = *this; _base->next(); return cpy; }

		//this assumes that in order for two abstract_iter_base objects to equal, their type must match exactly
		bool operator ==(const abstract_fw_iter& o) const { return typeid(this->_base) == typeid(o._base) && this->_base == o._base; }
		bool operator !=(const abstract_fw_iter& o) const { return !(*this == o); }

		operator abstract_fw_iter<t, difference, true>()
		{
			return abstract_fw_iter<t, difference, true>(reinterpret_cast<abstract_fw_iter_base<t, difference, true>*>(_base));
		}

		abstract_fw_iter(base* _base) : _base(_base) {}
	};

	template<typename iter_type, typename traits = std::iterator_traits<iter_type>, bool _enable = std::is_assignable<std::forward_iterator_tag, typename traits::iterator_category>()()>
	class abstract_fw_iter_wrapper;
	template<typename iter_type, typename traits>
	class abstract_fw_iter_wrapper<iter_type, traits, true> : public abstract_fw_iter_base<typename traits::value_type, typename traits::difference_type, meta::is_const<typename traits::reference>()()>
	{
	public:
		using base_class = abstract_fw_iter_base<typename traits::value_type, typename traits::difference_type, meta::is_const<typename traits::reference>()()>;
		using value_type = typename traits::value_type;
		using reference = typename traits::reference;
		using is_const = meta::is_const<typename traits::reference>;

		iter_type iter;

		reference operator*() const override { return *iter; }
		void next() override { ++iter; }
		bool operator==(const base_class& o) const override { return iter == dynamic_cast<const abstract_fw_iter_wrapper<iter_type, traits, true>&>(o).iter; }

		abstract_fw_iter_wrapper(iter_type iter) : iter(iter) {}
	};
}