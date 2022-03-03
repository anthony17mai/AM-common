#include "CppUnitTest.h"

#include "unique_id/unique_id.h"
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AM_test
{
	using namespace AM_common::unique_id;
	struct unique_label_tag {};
	struct type_label_tag {};

	template<typename tag> struct read_lab_num
	{
		static inline size_t val = unique_label<tag>::lab_val;
	};

	TEST_CLASS(unique_id_test)
	{
		using label_type1 = unique_label<unique_label_tag>;
		label_type1 label_1 = label_type1::make_label();
		label_type1 label_2 = label_type1::make_label();
		label_type1 label_3 = label_type1::make_label();

		TEST_METHOD(label_test)
		{
			Assert::AreEqual(label_1.id, size_t(0));
			Assert::AreEqual(label_2.id, size_t(1));
			Assert::AreEqual(label_3.id, size_t(2));
		}

		using label_type2 = unique_label<type_label_tag>;
		struct labeled_type1 : type_label<labeled_type1, type_label_tag> { };
		struct dummy_label : type_label<dummy_label, type_label_tag> 
		{
			/*
			* 
			* having a function that references a value from read_lab_num does not instantiate the class read_lab_num
			* because if it did then val would be incorrect
			* 
			*/
			size_t getnumlabels() { return read_lab_num<type_label_tag>::val; }

			/*
			* 
			* having read_lab_num as a field can instantiate read_lab_num intrestingly
			* 
			read_lab_num<type_label_tag> try_instantiate;
			*/
		};
		
		/*
		* 
		* when this struct is created, it reads the lab val of the unique label before labeled_type2 is instantiated.
		* 
		struct instan_reader : read_lab_num<type_label_tag> { };
		*/
		struct labeled_type2 : type_label<labeled_type2, type_label_tag> { };
		TEST_METHOD(type_label_test)
		{
			static_assert(std::is_same<labeled_type1::label_type, unique_label<type_label_tag>>()());
			Assert::AreEqual(size_t(3), labeled_type1::label_type::lab_val);
			Assert::AreEqual(labeled_type1::label.id, size_t(0));
			//dummy label is instantiated between the two labels
			Assert::AreEqual(labeled_type2::label.id, size_t(2));
		}

		TEST_METHOD(more_testing)
		{
			using lab = unique_label<type_label_tag>;
			Assert::AreEqual(lab::lab_val, read_lab_num<type_label_tag>::val);
		}
	};
}