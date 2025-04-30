#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../ArrayIterator.h"
#include "../MyArray.h"

SCENARIO("Push and check size")
{
	WHEN("create int array")
	{
		MyArray<double> arr;
		THEN("array should be an empty")
		{
			CHECK(arr.GetSize() == 0);
		}

		AND_WHEN("push one element")
		{
			arr.Push(2.3);
			THEN("array should be of size 1")
			{
				CHECK(arr.GetSize() == 1);
			}
			AND_WHEN("push another element")
			{
				arr.Push(5.2);
				THEN("array should be of size 2")
				{
					CHECK(arr.GetSize() == 2);
				}
			}
		}
	}

	WHEN("create string array")
	{
		MyArray<std::string> arr;
		THEN("array should be an empty")
		{
			CHECK(arr.GetSize() == 0);
		}

		AND_WHEN("push one element")
		{
			arr.Push("2");
			THEN("array should be of size 1")
			{
				CHECK(arr.GetSize() == 1);
			}
			AND_WHEN("push another element")
			{
				arr.Push("5");
				THEN("array should be of size 2")
				{
					CHECK(arr.GetSize() == 2);
				}
			}
		}
	}
}

SCENARIO("indexed access")
{
	GIVEN("array with 3 double elements")
	{
		MyArray<double> arr;
		arr.Push(1.1);
		arr.Push(2.2);
		arr.Push(3.3);
		WHEN("get access by index")
		{
			THEN("elements must match index")
			{
				CHECK(arr[0] == 1.1);
				CHECK(arr[1] == 2.2);
				CHECK(arr[2] == 3.3);
			}
		}

		WHEN("try to access an invalid index")
		{
			THEN("an exception should be thrown")
			{
				CHECK_THROWS_AS(arr[-1], std::out_of_range);
				CHECK_THROWS_AS(arr[3], std::out_of_range);
			}
		}
	}

	GIVEN("array with 3 string elements")
	{
		MyArray<std::string> arr;
		arr.Push("a");
		arr.Push("b");
		arr.Push("c");
		WHEN("get access by index")
		{
			THEN("elements must match index")
			{
				CHECK(arr[0] == "a");
				CHECK(arr[1] == "b");
				CHECK(arr[2] == "c");
			}
		}

		WHEN("try to access an invalid index")
		{
			THEN("an exception should be thrown")
			{
				CHECK_THROWS_AS(arr[-1], std::out_of_range);
				CHECK_THROWS_AS(arr[3], std::out_of_range);
			}
		}
	}
}

SCENARIO("resize array")
{
	GIVEN("empty double array")
	{
		MyArray<double> arr;
		WHEN("change the size to 3")
		{
			arr.Resize(3);
			THEN("size should become 3 and the elements are initialized to 0")
			{
				CHECK(arr.GetSize() == 3);
				CHECK(arr[0] == 0);
				CHECK(arr[1] == 0);
				CHECK(arr[2] == 0);
			}
		}
	}

	GIVEN("empty string array")
	{
		MyArray<std::string> arr;
		WHEN("change the size to 3")
		{
			arr.Resize(3);
			THEN("size should become 3 and the elements are initialized to emprty string")
			{
				CHECK(arr.GetSize() == 3);
				CHECK(arr[0] == "");
				CHECK(arr[1] == "");
				CHECK(arr[2] == "");
			}
		}
	}

	GIVEN("array with 3 double elements")
	{
		MyArray<double> arr;
		arr.Push(1.1);
		arr.Push(2.2);
		arr.Push(3.3);
		WHEN("change the size to 4")
		{
			arr.Resize(4);
			THEN("the last element should be initialized to 0, and the previous ones should not change")
			{
				CHECK(arr.GetSize() == 4);
				CHECK(arr[0] == 1.1);
				CHECK(arr[1] == 2.2);
				CHECK(arr[2] == 3.3);
				CHECK(arr[3] == 0);
			}
		}

		WHEN("change the size to 2")
		{
			arr.Resize(2);
			THEN("array should decrease")
			{
				CHECK(arr.GetSize() == 2);
				CHECK(arr[0] == 1.1);
				CHECK(arr[1] == 2.2);
			}
		}

		WHEN("change the size to 0")
		{
			arr.Resize(0);
			THEN("array should become empty")
			{
				CHECK(arr.GetSize() == 0);
			}
		}
	}

	GIVEN("array with 3 string elements")
	{
		MyArray<std::string> arr;
		arr.Push("a");
		arr.Push("b");
		arr.Push("c");
		WHEN("change the size to 4")
		{
			arr.Resize(4);
			THEN("the last element should be initialized to empty string, and the previous ones should not change")
			{
				CHECK(arr.GetSize() == 4);
				CHECK(arr[0] == "a");
				CHECK(arr[1] == "b");
				CHECK(arr[2] == "c");
				CHECK(arr[3] == "");
			}
		}

		WHEN("change the size to 2")
		{
			arr.Resize(2);
			THEN("array should decrease")
			{
				CHECK(arr.GetSize() == 2);
				CHECK(arr[0] == "a");
				CHECK(arr[1] == "b");
			}
		}

		WHEN("change the size to 0")
		{
			arr.Resize(0);
			THEN("array should become empty")
			{
				CHECK(arr.GetSize() == 0);
			}
		}
	}
}

SCENARIO("clear array")
{
	GIVEN("empty int array")
	{
		MyArray<int> arr;
		WHEN("clear array")
		{
			arr.Clear();
			THEN("array must remain empty")
			{
				CHECK(arr.GetSize() == 0);
			}
		}
	}

	GIVEN("array with 1 double elements")
	{
		MyArray<double> arr;
		arr.Push(1.1);
		WHEN("clear array")
		{
			arr.Clear();
			THEN("array should become empty")
			{
				CHECK(arr.GetSize() == 0);
			}
		}
	}

	GIVEN("array with 3 double elements")
	{
		MyArray<double> arr;
		arr.Push(1.1);
		arr.Push(2.2);
		arr.Push(3.3);
		WHEN("clear array")
		{
			arr.Clear();
			THEN("array should become empty")
			{
				CHECK(arr.GetSize() == 0);
			}
		}
	}
}

template <typename T>
bool AreEqual(MyArray<T>& arr1, MyArray<T>& arr2)
{
	return std::equal(arr1.begin(), arr1.end(), arr2.begin(), arr2.end());
}

SCENARIO("copy constructor test")
{
	GIVEN("empty double array")
	{
		MyArray<double> arr;
		WHEN("create new array with this array in params")
		{
			MyArray<double> newArr(arr);
			THEN("new array must be the same")
			{
				CHECK(AreEqual(arr, newArr));
			}
		}
	}

	GIVEN("double array with 3 elements")
	{
		MyArray<double> arr;
		arr.Push(1.1);
		arr.Push(2.2);
		arr.Push(3.3);

		WHEN("create new array with this array in params")
		{
			MyArray<double> newArr(arr);
			THEN("new array must be the same")
			{
				CHECK(AreEqual(arr, newArr));
			}
		}
	}

	GIVEN("empty string array")
	{
		MyArray<std::string> arr;
		WHEN("create new array with this array in params")
		{
			MyArray<std::string> newArr(arr);
			THEN("new array must be the same")
			{
				CHECK(AreEqual(arr, newArr));
			}
		}
	}

	GIVEN("string array with 3 elements")
	{
		MyArray<std::string> arr;
		arr.Push("a");
		arr.Push("b");
		arr.Push("c");

		WHEN("create new array with this array in params")
		{
			MyArray<std::string> newArr(arr);
			THEN("new array must be the same")
			{
				CHECK(AreEqual(arr, newArr));
			}
		}
	}
}

SCENARIO("move constructor test")
{
	GIVEN("empty double array")
	{
		MyArray<double> arr;
		MyArray<double> copy(arr);
		WHEN("create new array with this array in params")
		{
			MyArray<double> newArr(std::move(arr));
			THEN("new array should become the same as the first one")
			{
				CHECK(AreEqual(newArr, copy));
			}
		}
	}

	GIVEN("double array with 3 elements")
	{
		MyArray<double> arr;
		arr.Push(1.1);
		arr.Push(2.2);
		arr.Push(3.3);
		MyArray<double> copy(arr);
		WHEN("create new array with this array in params")
		{
			MyArray<double> newArr(std::move(arr));
			THEN("new array should become the same as the first one")
			{
				CHECK(AreEqual(newArr, copy));
			}
		}
	}

	GIVEN("empty string array")
	{
		MyArray<std::string> arr;
		MyArray<std::string> copy(arr);
		WHEN("create new array with this array in params")
		{
			MyArray<std::string> newArr(std::move(arr));
			THEN("new array should become the same as the first one")
			{
				CHECK(AreEqual(newArr, copy));
			}
		}
	}

	GIVEN("string array with 3 elements")
	{
		MyArray<std::string> arr;
		arr.Push("a");
		arr.Push("b");
		arr.Push("c");
		MyArray<std::string> copy(arr);
		WHEN("create new array with this array in params")
		{
			MyArray<std::string> newArr(std::move(arr));
			THEN("new array should become the same as the first one")
			{
				CHECK(AreEqual(newArr, copy));
			}
		}
	}
}

SCENARIO("assignment operator test")
{
	GIVEN("empty double array")
	{
		MyArray<double> arr;
		MyArray<double> copy(arr);
		WHEN("assign an array to itself")
		{
			arr = arr;
			THEN("array should not change")
			{
				CHECK(AreEqual(arr, copy));
			}
		}
	}

	GIVEN("double array with 3 elements")
	{
		MyArray<double> arr;
		arr.Push(3.4);
		arr.Push(2.3);
		arr.Push(1.1);
		MyArray<double> copy(arr);
		WHEN("assign an array to itself")
		{
			arr = arr;
			THEN("array should not change")
			{
				CHECK(AreEqual(arr, copy));
			}
		}
	}

	GIVEN("two empty double arrays")
	{
		MyArray<double> arr;
		MyArray<double> arr2;
		WHEN("assign the first to the seconds")
		{
			arr = arr2;
			THEN("the second must be equal to the first")
			{
				CHECK(AreEqual(arr, arr2));
			}
		}
	}

	GIVEN("two double array, one is empty, the other is not")
	{
		MyArray<double> arr;
		arr.Push(1.1);
		arr.Push(2.2);
		arr.Push(3.3);

		MyArray<double> arr2;
		WHEN("assign the first to the seconds")
		{
			arr2 = arr;
			THEN("the second must be equal to the first")
			{
				CHECK(AreEqual(arr, arr2));
			}
		}
	}

	GIVEN("two double array, one is empty, the other is not")
	{
		MyArray<double> arr;
		arr.Push(1.1);
		arr.Push(2.2);
		arr.Push(3.3);

		MyArray<double> arr2;
		WHEN("assign the second to the firsts")
		{
			arr = arr2;
			THEN("the second must be equal to the first")
			{
				CHECK(AreEqual(arr, arr2));
			}
		}
	}

	GIVEN("two empty string arrays")
	{
		MyArray<std::string> arr;
		MyArray<std::string> arr2;
		WHEN("assign the first to the seconds")
		{
			arr = arr2;
			THEN("the second must be equal to the first")
			{
				CHECK(AreEqual(arr, arr2));
			}
		}
	}

	GIVEN("two string array, one is empty, the other is not")
	{
		MyArray<std::string> arr;
		arr.Push("a");
		arr.Push("b");
		arr.Push("c");

		MyArray<std::string> arr2;
		WHEN("assign the first to the seconds")
		{
			arr2 = arr;
			THEN("the second must be equal to the first")
			{
				CHECK(AreEqual(arr, arr2));
			}
		}
	}

	GIVEN("two string array, one is empty, the other is not")
	{
		MyArray<std::string> arr;
		arr.Push("a");
		arr.Push("b");
		arr.Push("c");

		MyArray<std::string> arr2;
		WHEN("assign the second to the firsts")
		{
			arr = arr2;
			THEN("the second must be equal to the first")
			{
				CHECK(AreEqual(arr, arr2));
			}
		}
	}
}

SCENARIO("move assignment operator test")
{
	GIVEN("empty double array")
	{
		MyArray<double> arr;
		MyArray<double> copy(arr);
		WHEN("assign an array to itself")
		{
			arr = std::move(arr);
			THEN("array should not change")
			{
				CHECK(AreEqual(arr, copy));
			}
		}
	}

	GIVEN("double array with 3 elements")
	{
		MyArray<double> arr;
		arr.Push(3.4);
		arr.Push(2.3);
		arr.Push(1.1);
		MyArray<double> copy(arr);
		WHEN("assign an array to itself")
		{
			arr = std::move(arr);
			THEN("array should not change")
			{
				CHECK(AreEqual(arr, copy));
			}
		}
	}

	GIVEN("two empty double arrays")
	{
		MyArray<double> arr;
		MyArray<double> copy(arr);
		MyArray<double> arr2;
		WHEN("assign the first to the seconds")
		{
			arr = std::move(arr2);
			THEN("the second must be equal to the copy")
			{
				CHECK(AreEqual(copy, arr));
			}
		}
	}

	GIVEN("two double array, one is empty, the other is not")
	{
		MyArray<double> arr;
		arr.Push(1.1);
		arr.Push(2.2);
		arr.Push(3.3);
		MyArray<double> arr2;
		MyArray<double> copy(arr);
		WHEN("assign the first to the seconds")
		{
			arr2 = std::move(arr);
			THEN("the second must be equal to the copy")
			{
				CHECK(AreEqual(copy, arr2));
			}
		}
	}

	GIVEN("two double array, one is empty, the other is not")
	{
		MyArray<double> arr;
		arr.Push(1.1);
		arr.Push(2.2);
		arr.Push(3.3);

		MyArray<double> arr2;
		MyArray<double> copy(arr2);
		WHEN("assign the second to the firsts")
		{
			arr = std::move(arr2);
			THEN("the first must be equal to the copy")
			{
				CHECK(AreEqual(arr, copy));
			}
		}
	}

	GIVEN("two empty string arrays")
	{
		MyArray<std::string> arr;
		MyArray<std::string> arr2;
		MyArray<std::string> copy(arr2);
		WHEN("assign the first to the seconds")
		{
			arr = std::move(arr2);
			THEN("the second must be equal to the copy")
			{
				CHECK(AreEqual(arr, copy));
			}
		}
	}

	GIVEN("two string array, one is empty, the other is not")
	{
		MyArray<std::string> arr;
		arr.Push("a");
		arr.Push("b");
		arr.Push("c");
		MyArray<std::string> copy(arr);
		MyArray<std::string> arr2;
		WHEN("assign the first to the seconds")
		{
			arr2 = std::move(arr);
			THEN("the second must be equal to the copy")
			{
				CHECK(AreEqual(copy, arr2));
			}
		}
	}

	GIVEN("two string array, one is empty, the other is not")
	{
		MyArray<std::string> arr;
		arr.Push("a");
		arr.Push("b");
		arr.Push("c");
		MyArray<std::string> arr2;
		MyArray<std::string> copy(arr2);
		WHEN("assign the second to the firsts")
		{
			arr = std::move(arr2);
			THEN("the second must be equal to the copy")
			{
				CHECK(AreEqual(arr, copy));
			}
		}
	}
}

SCENARIO("iterators testing")
{
	std::ostringstream output;

	GIVEN("empty int array")
	{
		MyArray<int> arr;
		WHEN("get begin and end iterators")
		{
			auto itBegin = arr.begin();
			auto itEnd = arr.end();
			THEN("iterators must be equal")
			{
				CHECK(itBegin == itEnd);
			}
		}

		WHEN("get rbegin and rend iterators")
		{
			auto itBegin = arr.rbegin();
			auto itEnd = arr.rend();
			THEN("iterators must be equal")
			{
				CHECK(itBegin == itEnd);
			}
		}
	}

	GIVEN("int array with 4 elements")
	{
		MyArray<int> arr;
		arr.Push(1);
		arr.Push(2);
		arr.Push(3);
		arr.Push(4);

		WHEN("output in for range cycle")
		{
			for (auto it = arr.begin(); it != arr.end(); ++it)
			{
				output << *it;
			}
			THEN("output stream must contain all elements")
			{
				CHECK(output.str() == "1234");
			}
		}

		WHEN("output in temporary range cycle")
		{
			for (auto item : arr)
			{
				output << item;
			}
			THEN("output stream must contain all elements")
			{
				CHECK(output.str() == "1234");
			}
		}

		WHEN("output in reverse for range cycle")
		{
			for (auto it = arr.rbegin(); it != arr.rend(); ++it)
			{
				output << *it;
			}
			THEN("output stream must contain all elements in reverse order")
			{
				CHECK(output.str() == "4321");
			}
		}
	}

	GIVEN("string array with 4 elements")
	{
		MyArray<std::string> arr;
		arr.Push("he");
		arr.Push("ll");
		arr.Push("ow");
		arr.Push("orld");
		WHEN("output in for range cycle")
		{
			for (auto it = arr.begin(); it != arr.end(); ++it)
			{
				output << *it;
			}
			THEN("output stream must contain all elements")
			{
				CHECK(output.str() == "helloworld");
			}
		}

		WHEN("output in temporary range cycle")
		{
			for (auto item : arr)
			{
				output << item;
			}
			THEN("output stream must contain all elements")
			{
				CHECK(output.str() == "helloworld");
			}
		}

		WHEN("output in reverse for range cycle")
		{
			for (auto it = arr.rbegin(); it != arr.rend(); ++it)
			{
				output << *it;
			}
			THEN("output stream must contain all elements in reverse order")
			{
				CHECK(output.str() == "orldowllhe");
			}
		}
	}
}

SCENARIO("assignment of arrays of different types")
{
	GIVEN("double and int array")
	{
		MyArray<int> arrI;
		arrI.Push(4);
		arrI.Push(5);
		arrI.Push(6);
		MyArray<double> arrD;
		arrD.Push(1.1);
		arrD.Push(2.2);
		arrD.Push(3.3);

		WHEN("assign an int array to a double array")
		{
			arrD = arrI;
			THEN("the array should be copied correctly")
			{
				CHECK(arrD[0] == 4);
				CHECK(arrD[1] == 5);
				CHECK(arrD[2] == 6);
			}
		}

		WHEN("assign an double array to a int array")
		{
			arrI = arrD;
			THEN("the array should be copied correctly")
			{
				CHECK(arrI[0] == 1);
				CHECK(arrI[1] == 2);
				CHECK(arrI[2] == 3);
			}
		}
	}
}