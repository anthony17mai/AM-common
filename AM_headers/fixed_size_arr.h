#pragma once

namespace AM_common
{
	template<typename ts>
	class fixed_size_arr
	{
	private:
		const size_t _size;
		ts* const arr;

		//empty constructor
		fixed_size_arr() : _size(0), arr(nullptr) {}

	public:
		static constexpr inline fixed_size_arr make_empty() { return fixed_size_arr(); }

		size_t size() const { return _size; }
		ts& operator[](size_t id) { return arr[id]; }
		const ts& operator[](size_t id) const { return arr[id]; }
		ts& at(size_t id) { return (*this)[id]; }
		const ts& at(size_t id) const { return (*this)[id]; }

		fixed_size_arr(size_t len) : _size(len), arr(new ts[len])
		{ }

		//cp arr
		fixed_size_arr(const fixed_size_arr& o) : fixed_size_arr(o.size())
		{
			for (size_t id = 0; id < o.size(); id++)
			{
				this->at(id) = o[id];
			}
		}

		~fixed_size_arr()
		{
			delete[] arr;
		}
	};

	template<typename ts>
	class fixed_size_arr_ronly
	{
	private:
		const size_t _size;
		const ts* const arr;

		//empty array
		fixed_size_arr_ronly() : _size(0), arr(nullptr) {}

	public:
		//makes an empty array (size 0, arr = nullptr)
		static constexpr inline fixed_size_arr_ronly make_empty() { return fixed_size_arr_ronly(); }

		size_t size() const { return _size; }
		const ts& operator[](size_t id) const { return arr[id]; }
		const ts& at(size_t id) const { return (*this)[id]; }

		fixed_size_arr_ronly(size_t len, const ts* existing) : _size(len), arr(existing) { }

		//dont copy array
		fixed_size_arr_ronly(const fixed_size_arr_ronly& o) : fixed_size_arr_ronly(o.size(), o.arr) { }

		//the readonly array is a shallow copy
		~fixed_size_arr_ronly() { }
	};
}