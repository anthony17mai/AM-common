#pragma once

namespace AM_common {namespace unique_id{

	template<typename id_tag, typename id_type = size_t>
	struct unique_label
	{
		static id_type lab_val = 0;

		id_type i;

		bool operator==(unique_label<id_tag, id_type> o) { return i == o.i; }

	private:
		unique_label() : i(lab_val++) {}

		template<typename t>
		friend struct type_label<t, id_tag, id_type>;
	};

	template<typename t, typename id_tag, typename id_type = size_t>
	struct type_label
	{
		static unique_label<id_tag, id_type> label;

		unique_label<id_tag, id_type> local_label;
	};
} }