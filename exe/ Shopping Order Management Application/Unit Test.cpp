#include "pch.h"
#include "CppUnitTest.h"
#include "truck_r.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackboxTests
{
	//TEST_CLASS(UnitTest)
	//{
	//public:
	//	// Test example from class
	//	TEST_METHOD(TestMethod1)
	//	{
	//		struct Map baseMap = populateMap();
	//		int i = getNumRows(&baseMap);
	//		Assert::AreEqual(25, i);
	//	}
	//};

	TEST_CLASS(ShipmentWeightBlackboxTest)
	{
	public:
		TEST_METHOD(Valid)
		{
			double input = 20;
			int i = isValidWeight(input);
			Assert::AreEqual(1, i);
		}

		TEST_METHOD(MinimumWeight)
		{
			double input = 1;
			int i = isValidWeight(input);
			Assert::AreEqual(1, i);
		}

		TEST_METHOD(MaximumWeight)
		{
			double input = 1200;
			int i = isValidWeight(input);
			Assert::AreEqual(1, i);
		}

		TEST_METHOD(NegativeWeight)
		{
			double input = -1;
			int i = isValidWeight(input);
			Assert::AreEqual(0, i);
		}

		TEST_METHOD(Empty)
		{
			double input = NULL;
			int i = isValidWeight(input);
			Assert::AreEqual(0, i);
		}

		TEST_METHOD(Overweight)
		{
			double input = 100000;
			int i = isValidWeight(input);
			Assert::AreEqual(0, i);
		}
	};

	TEST_CLASS(BoxSizeBlackboxTest)
	{
	public:

		TEST_METHOD(Valid)
		{
			double input = 1;
			double i = isValidSize(input);
			Assert::AreEqual(1.0, i, 0.01);
		}

		TEST_METHOD(MinimumSize)
		{
			double input = 0.5;
			double i = isValidSize(input);
			Assert::AreEqual(0.5, i, 0.01);
		}

		TEST_METHOD(MaximumSize)
		{
			double input = 5;
			double i = isValidSize(input);
			Assert::AreEqual(5.0, i, 0.01);
		}

		TEST_METHOD(NegativeSize)
		{
			double input = -1;
			double i = isValidSize(input);
			Assert::AreEqual(0, i, 0.01);
		}

		TEST_METHOD(Empty)
		{
			double input = NULL;
			double i = isValidSize(input);
			Assert::AreEqual(0.0, i, 0.01);
		}

		TEST_METHOD(Zero)
		{
			double input = 0;
			double i = isValidSize(input);
			Assert::AreEqual(0.0, i, 0.01);
		}
	};

	TEST_CLASS(AddressValidityBlackboxTest) 
	{
	public:
		TEST_METHOD(Valid)
		{
			int number = 10;
			char letter = 'C';
			int result = isValidAddress(number, letter);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(InvalidNumber)
		{
			int number = 0;
			char letter = 'D';
			int result = isValidAddress(number, letter);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(InvalidLetter)
		{
			int number = 15;
			char letter = 'Z';
			int result = isValidAddress(number, letter);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(BothInvalid)
		{
			int number = 0;
			char letter = 'Z';
			int result = isValidAddress(number, letter);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(EmptyNumber)
		{
			int number = NULL;
			char letter = 'A';
			int result = isValidAddress(number, letter);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(EmptyLetter)
		{
			int number = 10;
			char letter = NULL;
			int result = isValidAddress(number, letter);
			Assert::AreEqual(0, result);
		}
	};

	TEST_CLASS(DistanceCalculationBlackboxTest)
	{
	public:
		TEST_METHOD(Valid)
		{
			struct Point p1 = { 1, 1 };
			struct Point p2 = { 4, 5 };
			double result = distance(&p1, &p2);
			Assert::AreEqual(sqrt(3 * 3 + 4 * 4), result);
		}

		TEST_METHOD(ZeroDistance)
		{
			struct Point p = { 1, 1 };
			double result = distance(&p, &p);
			Assert::AreEqual(0.0, result);
		}

		TEST_METHOD(HorizontalDistance)
		{
			struct Point p1 = { 1, 1 };
			struct Point p2 = { 1, 5 };
			double result = distance(&p1, &p2);
			Assert::AreEqual(4.0, result);
		}

		TEST_METHOD(VerticalDistance)
		{
			struct Point p1 = { 1, 1 };
			struct Point p2 = { 5, 1 };
			double result = distance(&p1, &p2);
			Assert::AreEqual(4.0, result);
		}

		TEST_METHOD(NegativeHorizontalDistance)
		{
			struct Point p1 = { 1, 5 };
			struct Point p2 = { 1, 1 };
			double result = distance(&p1, &p2);
			Assert::AreEqual(4.0, result);
		}

		TEST_METHOD(NegativeVerticalDistance)
		{
			struct Point p1 = { 5, 1 };
			struct Point p2 = { 1, 1 };
			double result = distance(&p1, &p2);
			Assert::AreEqual(4.0, result);
		}
	};
}

namespace WhiteboxTests
{
	TEST_CLASS(ShipmentWeightWhiteboxTest)
	{
	public:
		TEST_METHOD(ValidWeight)
		{
			double input = 20;
			int i = isValidWeight(input);
			Assert::AreEqual(1, i);
		}

		TEST_METHOD(NegativeWeightReturnsZero)
		{
			double input = -1;
			int i = isValidWeight(input);
			Assert::AreEqual(0, i);
		}

		TEST_METHOD(WeightZeroReturnsZero)
		{
			double input = 0;
			int i = isValidWeight(input);
			Assert::AreEqual(0, i);
		}

		TEST_METHOD(LargeWeightReturnsOne)
		{
			double input = 1000;
			int i = isValidWeight(input);
			Assert::AreEqual(1, i);
		}

		TEST_METHOD(BelowMinimumWeightReturnsZero)
		{
			double input = 0.5;
			int i = isValidWeight(input);
			Assert::AreEqual(0, i);
		}

		TEST_METHOD(MaximumDoubleWeightReturnsOne)
		{
			double input = 1199.99;
			int i = isValidWeight(input);
			Assert::AreEqual(1, i);
		}
	};

	TEST_CLASS(BoxSizeWhiteboxTest)
	{
	public:
		TEST_METHOD(ValidSize)
		{
			double input = 1;
			double i = isValidSize(input);
			Assert::AreEqual(1.0, i, 0.01);
		}

		TEST_METHOD(SizeGreaterThanFiveReturnsZero)
		{
			double input = 6;
			double i = isValidSize(input);
			Assert::AreEqual(0.0, i, 0.01);
		}

		TEST_METHOD(SizeZeroReturnsZero)
		{
			double input = 0;
			double i = isValidSize(input);
			Assert::AreEqual(0.0, i, 0.01);
		}

		TEST_METHOD(MediumReturnsMedium)
		{
			double input = 0.5;
			double i = isValidSize(input);
			Assert::AreEqual(0.5, i, 0.01);
		}

		TEST_METHOD(MaximumIntSizeReturnsLarge)
		{
			double input = 5;
			double i = isValidSize(input);
			Assert::AreEqual(5.0, i, 0.01);
		}

		TEST_METHOD(MaximumDoubleSizeReturnsLarge)
		{
			double input = 5.0;
			double i = isValidSize(input);
			Assert::AreEqual(5.0, i, 0.01);
		}
	};

	TEST_CLASS(AddressValidityWhiteboxTest)
	{
	public:
		TEST_METHOD(ValidAddress)
		{
			int number = 10;
			char letter = 'C';
			int result = isValidAddress(number, letter);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(NumberZeroReturnsZero)
		{
			int number = 0;
			char letter = 'D';
			int result = isValidAddress(number, letter);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(LetterGreaterThanYReturnsZero)
		{
			int number = 15;
			char letter = 'Z';
			int result = isValidAddress(number, letter);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(MaximumIntAddressReturnsZero)
		{
			int number = 32000;
			char letter = 'Y';
			int result = isValidAddress(number, letter);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(MinimumIntAddressReturnsZero)
		{
			int number = -32000;
			char letter = 'A';
			int result = isValidAddress(number, letter);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(ValidAddressWithMinimumValuesReturnsOne)
		{
			int number = 1;
			char letter = 'A';
			int result = isValidAddress(number, letter);
			Assert::AreEqual(1, result);
		}
	};

	TEST_CLASS(DistanceCalculationWhiteboxTest)
	{
	public:
		TEST_METHOD(SamePoint)
		{
			struct Point p = { 3, 5 };
			double result = distance(&p, &p);
			Assert::AreEqual(0.0, result);
		}

		TEST_METHOD(HorizontalDistance)
		{
			struct Point p1 = { 2, 3 };
			struct Point p2 = { 5, 3 };
			double result = distance(&p1, &p2);
			Assert::AreEqual(3.0, result);
		}

		TEST_METHOD(VerticalDistance)
		{
			struct Point p1 = { 4, 7 };
			struct Point p2 = { 4, 2 };
			double result = distance(&p1, &p2);
			Assert::AreEqual(5.0, result);
		}

		TEST_METHOD(DiagonalDistance)
		{
			struct Point p1 = { 2, 2 };
			struct Point p2 = { 5, 5 };
			double result = distance(&p1, &p2);
			Assert::AreEqual(sqrt(3 * 3 + 3 * 3), result);
		}

		TEST_METHOD(NegativeHorizontalDistance)
		{
			struct Point p1 = { 4, 5 };
			struct Point p2 = { 2, 5 };
			double result = distance(&p1, &p2);
			Assert::AreEqual(2.0, result);
		}

		TEST_METHOD(NegativeVerticalDistance)
		{
			struct Point p1 = { 6, 3 };
			struct Point p2 = { 6, 6 };
			double result = distance(&p1, &p2);
			Assert::AreEqual(3.0, result);
		}

		TEST_METHOD(NegativeDiagonalDistance)
		{
			struct Point p1 = { 7, 4 };
			struct Point p2 = { 4, 7 };
			double result = distance(&p1, &p2);
			Assert::AreEqual(sqrt(3 * 3 + 3 * 3), result);
		}
	};

}

namespace IntegrationTest {

	TEST_CLASS(WeightAndSize)
	{
	public:
		TEST_METHOD(InvalidWeightAndSize)
		{
			double weight = -5.0;
			double size = -1.0;
			int weightResult = isValidWeight(weight);
			double sizeResult = isValidSize(size);
			Assert::AreEqual(0, weightResult);
			Assert::AreEqual(0.0, sizeResult, 0.01);
		}

		TEST_METHOD(ValidWeightAndSize)
		{
			double weight = 100.0;
			double size = 0.5;
			int weightResult = isValidWeight(weight);
			double sizeResult = isValidSize(size);
			Assert::AreEqual(1, weightResult);
			Assert::AreEqual(0.5, sizeResult, 0.01);
		}

		TEST_METHOD(InvalidWeightValidSize)
		{
			double weight = -10.0;
			double size = 0.5;
			int weightResult = isValidWeight(weight);
			double sizeResult = isValidSize(size);
			Assert::AreEqual(0, weightResult);
			Assert::AreEqual(0.5, sizeResult, 0.01);
		}

		TEST_METHOD(ValidWeightInvalidSize)
		{
			double weight = 50.0;
			double size = -2.0;
			int weightResult = isValidWeight(weight);
			double sizeResult = isValidSize(size);
			Assert::AreEqual(1, weightResult);
			Assert::AreEqual(0.0, sizeResult, 0.01);
		}

		TEST_METHOD(SizeInvalidWeightValid)
		{
			double weight = 15.0;
			double size = 6.0;
			int weightResult = isValidWeight(weight);
			double sizeResult = isValidSize(size);
			Assert::AreEqual(1, weightResult);
			Assert::AreEqual(0.0, sizeResult, 0.01);
		}

		TEST_METHOD(BothInvalid)
		{
			double weight = -5.0;
			double size = 6.0;
			int weightResult = isValidWeight(weight);
			double sizeResult = isValidSize(size);
			Assert::AreEqual(0, weightResult);
			Assert::AreEqual(0.0, sizeResult, 0.01);
		}

		TEST_METHOD(ValidWeightAndInvalidSize)
		{
			double weight = 20.0;
			double size = -1.0;
			int weightResult = isValidWeight(weight);
			double sizeResult = isValidSize(size);
			Assert::AreEqual(1, weightResult);
			Assert::AreEqual(0.0, sizeResult, 0.01);
		}

		TEST_METHOD(BothValidButNearLimits)
		{
			double weight = 1.0;
			double size = 0.5;
			int weightResult = isValidWeight(weight);
			double sizeResult = isValidSize(size);
			Assert::AreEqual(1, weightResult);
			Assert::AreEqual(0.5, sizeResult, 0.01);
		}

		TEST_METHOD(BothInvalidNearLimits)
		{
			double weight = 1201.0;
			double size = 5.1;
			int weightResult = isValidWeight(weight);
			double sizeResult = isValidSize(size);
			Assert::AreEqual(0, weightResult);
			Assert::AreEqual(0.0, sizeResult, 0.01);
		}
	};

	TEST_CLASS(WeightAndAddress)
	{
	public:
		TEST_METHOD(ValidWeightAndValidAddress)
		{
			double weight = 1000.0;
			int number = 10;
			char letter = 'C';
			int weightResult = isValidWeight(weight);
			int addressResult = isValidAddress(number, letter);
			Assert::AreEqual(1, weightResult);
			Assert::AreEqual(1, addressResult);
		}

		TEST_METHOD(InvalidWeightValidAddress)
		{
			double weight = 1500.0;
			int number = 10;
			char letter = 'C';
			int weightResult = isValidWeight(weight);
			int addressResult = isValidAddress(number, letter);
			Assert::AreEqual(0, weightResult);
			Assert::AreEqual(1, addressResult);
		}

		TEST_METHOD(ValidWeightInvalidAddress)
		{
			double weight = 1000.0;
			int number = 30;
			char letter = 'Z';
			int weightResult = isValidWeight(weight);
			int addressResult = isValidAddress(number, letter);
			Assert::AreEqual(1, weightResult);
			Assert::AreEqual(0, addressResult);
		}

		TEST_METHOD(InvalidWeightAndInvalidAddress)
		{
			double weight = 1500.0;
			int number = 30;
			char letter = 'Z';
			int weightResult = isValidWeight(weight);
			int addressResult = isValidAddress(number, letter);
			Assert::AreEqual(0, weightResult);
			Assert::AreEqual(0, addressResult);
		}

		TEST_METHOD(ValidWeightNearLimitValidAddress)
		{
			double weight = 1200.0;
			int number = 1;
			char letter = 'A';
			int weightResult = isValidWeight(weight);
			int addressResult = isValidAddress(number, letter);
			Assert::AreEqual(1, weightResult);
			Assert::AreEqual(1, addressResult);
		}

		TEST_METHOD(InvalidWeightNearLimitInvalidAddress)
		{
			double weight = 1300.0;
			int number = 30;
			char letter = 'Z';
			int weightResult = isValidWeight(weight);
			int addressResult = isValidAddress(number, letter);
			Assert::AreEqual(0, weightResult);
			Assert::AreEqual(0, addressResult);
		}
	};

	TEST_CLASS(SizeAndAddress)
	{
	public:
		TEST_METHOD(ValidSizeAndValidAddress)
		{
			double size = 1.0;
			int number = 10;
			char letter = 'C';
			double sizeResult = isValidSize(size);
			int addressResult = isValidAddress(number, letter);
			Assert::AreEqual(1.0, sizeResult, 0.01);
			Assert::AreEqual(1, addressResult);
		}

		TEST_METHOD(InvalidSizeValidAddress)
		{
			double size = 6.0;
			int number = 10;
			char letter = 'C';
			double sizeResult = isValidSize(size);
			int addressResult = isValidAddress(number, letter);
			Assert::AreEqual(0.0, sizeResult, 0.01);
			Assert::AreEqual(1, addressResult);
		}

		TEST_METHOD(ValidSizeInvalidAddress)
		{
			double size = 1.0;
			int number = 30;
			char letter = 'Z';
			double sizeResult = isValidSize(size);
			int addressResult = isValidAddress(number, letter);
			Assert::AreEqual(1.0, sizeResult, 0.01);
			Assert::AreEqual(0, addressResult);
		}

		TEST_METHOD(InvalidSizeAndInvalidAddress)
		{
			double size = 6.0;
			int number = 30;
			char letter = 'Z';
			double sizeResult = isValidSize(size);
			int addressResult = isValidAddress(number, letter);
			Assert::AreEqual(0.0, sizeResult, 0.01);
			Assert::AreEqual(0, addressResult);
		}

		TEST_METHOD(ValidSizeNearLimitValidAddress)
		{
			double size = 5.0;
			int number = 1;
			char letter = 'A';
			double sizeResult = isValidSize(size);
			int addressResult = isValidAddress(number, letter);
			Assert::AreEqual(5.0, sizeResult, 0.01);
			Assert::AreEqual(1, addressResult);
		}

		TEST_METHOD(InvalidSizeNearLimitInvalidAddress)
		{
			double size = 5.0;
			int number = 30;
			char letter = 'Z';
			double sizeResult = isValidSize(size);
			int addressResult = isValidAddress(number, letter);
			Assert::AreEqual(5.0, sizeResult, 0.01);
			Assert::AreEqual(0, addressResult);
		}
	};
}

namespace AcceptanceTest {

	TEST_CLASS(ValidationFunctionsTests)
	{
	public:
		TEST_METHOD(IsValidWeight_ValidInputs)
		{
			Assert::AreEqual(1, isValidWeight(100.0)); // Valid weight
			Assert::AreEqual(1, isValidWeight(TRUCK_WEIGHT_LIMIT)); // Maximum weight
		}

		TEST_METHOD(IsValidWeight_InvalidInputs)
		{
			Assert::AreEqual(0, isValidWeight(0.0)); // Zero weight
			Assert::AreEqual(0, isValidWeight(-50.0)); // Negative weight
			Assert::AreEqual(0, isValidWeight(TRUCK_WEIGHT_LIMIT + 1)); // Exceeds limit
		}

		TEST_METHOD(IsValidSize_ValidInputs)
		{
			Assert::AreEqual(0.5, isValidSize(VOL_SMALL)); // Valid size (small)
			Assert::AreEqual(1.0, isValidSize(VOL_MEDIUM)); // Valid size (medium)
			Assert::AreEqual(5.0, isValidSize(VOL_LARGE)); // Valid size (large)
		}

		TEST_METHOD(IsValidSize_InvalidInputs)
		{
			Assert::AreEqual(0.0, isValidSize(0.0)); // Zero size
			Assert::AreEqual(0.0, isValidSize(-1.0)); // Negative size
			Assert::AreEqual(0.0, isValidSize(4.0)); // Invalid size
		}

		TEST_METHOD(IsValidAddress_ValidInputs)
		{
			Assert::AreEqual(1, isValidAddress(10, 'C')); // Valid address (within range)
			Assert::AreEqual(1, isValidAddress(1, 'A')); // Valid address (minimum range)
			Assert::AreEqual(1, isValidAddress(25, 'Y')); // Valid address (maximum range)
		}

		TEST_METHOD(IsValidAddress_InvalidInputs)
		{
			Assert::AreEqual(0, isValidAddress(0, 'A')); // Invalid address (number below range)
			Assert::AreEqual(0, isValidAddress(26, 'A')); // Invalid address (number above range)
			Assert::AreEqual(0, isValidAddress(10, 'Z')); // Invalid address (letter above range)
			Assert::AreEqual(0, isValidAddress(10, '@')); // Invalid address (symbol)
		}

		TEST_METHOD(IsValidAddress_NoSpaces)
		{
			Assert::AreEqual(1, isValidAddress(10, 'C')); // Valid address (no spaces)
		}

		TEST_METHOD(IsValidAddress_LeadingSpaces)
		{
			Assert::AreEqual(1, isValidAddress(10, ' C')); // Valid address (leading spaces)
		}

		TEST_METHOD(IsValidAddress_RandomSymbols)
		{
			Assert::AreEqual(0, isValidAddress(10, '@')); // Invalid address (random symbol)
		}
	};
}