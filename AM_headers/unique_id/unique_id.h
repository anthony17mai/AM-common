#pragma once

namespace AM_common {namespace unique_id{

	template<typename id_tag, typename id_type = size_t>
	struct unique_label
	{
		static inline id_type lab_val = 0;
		static unique_label make_label() { return unique_label<id_tag, id_type>(); }

		id_type id;

		bool operator==(unique_label<id_tag, id_type> o) { return id == o.id; }
		bool operator==(id_type id) { return id == id; }
		bool operator==(int id) { return id == (size_t)id; }

		operator id_type() { return id; }

	private:
		unique_label() : id(lab_val++) {}
	};

	template<typename t, typename id_tag, typename id_type = size_t>
	struct type_label
	{
		using label_type = unique_label<id_tag, id_type>;
		static inline unique_label<id_tag, id_type> label = unique_label<id_tag, id_type>::make_label();
	};

	template<typename t, typename id_tag, typename id_type = size_t>
	struct label : type_label<t, id_tag, id_type>
	{
		unique_label<id_tag, id_type> id = type_label<t, id_tag, id_type>::label;
	};
} }