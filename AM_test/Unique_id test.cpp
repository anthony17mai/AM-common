#include "CppUnitTest.h"

#include "unique_id/unique_id.h"
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AM_test
{
	
	using namespace AM_common::unique_id;
	struct unique_label_tag {};
	struct type_label_tag {};

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
		struct test_label : type_label<test_label, type_label_tag> { };
		struct labeled_type2 : type_label<labeled_type2, type_label_tag> { };
		TEST_METHOD(type_label_test)
		{
			Assert::AreEqual(labeled_type1::label.id, size_t(0));
			//dummy label is instantiated between the two labels
			Assert::AreEqual(labeled_type2::label.id, size_t(2));
		}
	};
}