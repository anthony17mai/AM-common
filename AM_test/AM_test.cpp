#include "CppUnitTest.h"
#include "casefreecmp.h"
#include "str_split.h"
#include "box_arr.h"
#include <utility>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AM_test
{
	TEST_CLASS(CASEFREECMP)
	{
	public:
		
		TEST_METHOD(casefreeeqq)
		{
			std::string str = "CPU";
			const char* cmp = "cpu";
			Assert::IsTrue(AM_common::casefreeeqq()(str, cmp));
		}
	};

	TEST_CLASS(STR_SPLIT)
	{
	public:

		TEST_METHOD(str_divide)
		{
			std::string str = "quantum: 1";
			std::vector<std::string> expected({ "quantum: 1", "" });
			std::vector<std::string> res;
			AM_common::str_divide(str, res, '=');	//bad case

			Assert::AreEqual(expected[0], res[0]);
			Assert::AreEqual(expected[1], res[1]);

			//does not trim
			std::vector<std::string> expected2({ "quantum", " 1" });
			res.clear();
			AM_common::str_divide(str, res, ':');	//valid case

			Assert::AreEqual(expected2[0], res[0]);
			Assert::AreEqual(expected2[1], res[1]);
		}

		TEST_METHOD(str_trim)
		{
			std::string test = "RR\r";
			char delim = '\r';
			std::string expected = "RR";
			std::string res = AM_common::str_trim(test, delim);
			Assert::AreEqual(expected, res);
		}
	};

	TEST_CLASS(BOX_ARR)
	{
		typedef AM_common::box_arr<double, 2, 3, 5> box_t;

	public:
		TEST_METHOD(index_tests)
		{
			box_t res;
			double expected[box_t::arr_size::value] =
			{
				//[0][i][j]
				0, 0, 0, 0, 0,
				0, 0, 0, 0, 0,
				0, 0, 0, 0, 0,

				//[1][i][j]
				0, 0, 0, 0, 0,
				0, 1, 2, 3, 4,
				0, 2, 4, 6, 8,
			};

			//cheat to get the pointer
			double* _arr = res.begin().ptr;

			//create a 2 x 3 x 5 multiplication table
			for (int id = 0; id < 2; id++)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 5; k++)
					{
						res[id][j][k] = (double)id * j * k;
					}
				}
			}

			//compare each element of the array
			for (int id = 0; id < 30; id++)
			{
				Assert::AreEqual(expected[id], _arr[id]);
			}
		}
	};
}
