#pragma once

namespace AM_common {namespace unique_id{

	template<typename id_label>
	struct labeler
	{
		static int i = 0;

		static int get_id() { return i++; }
	};

	template<typename id_label>
	struct unique_label
	{
		static int label = labeler<id_label>::get_id();
	};
} }