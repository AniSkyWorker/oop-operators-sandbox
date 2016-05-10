#include "stdafx.h"
#include "../task1/Rational.h"

BOOST_AUTO_TEST_CASE(Test_Greates_Common_Denominator)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
}


void VerifyRational(const CRational & r, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(r.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(r.GetDenominator(), expectedDenominator);
}

BOOST_AUTO_TEST_SUITE(Rational_number)
	BOOST_AUTO_TEST_CASE(is_0_by_default)
	{
		VerifyRational(CRational(), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_from_integer)
	{
		VerifyRational(CRational(10), 10, 1);
		VerifyRational(CRational(-10), -10, 1);
		VerifyRational(CRational(0), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_with_numerator_and_denominator)
	{
		VerifyRational(CRational(5, 2), 5, 2);
		VerifyRational(CRational(-5, 2), -5, 2);
		VerifyRational(CRational(5, -2), -5, 2);
		VerifyRational(CRational(-5, -2), 5, 2);
	}
	BOOST_AUTO_TEST_CASE(is_normalized_after_construction)
	{
		VerifyRational(CRational(6, 8), 3, 4);
		VerifyRational(CRational(6, -8), -3, 4);
		VerifyRational(CRational(-6, 8), -3, 4);
		VerifyRational(CRational(-6, -8), 3, 4);
		VerifyRational(CRational(-10, 20), -1, 2);
	}
	BOOST_AUTO_TEST_CASE(cant_have_zero_denominator)
	{
		BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(can_get_compound_fraction)
	{
		auto rational = CRational(9, 4);
		auto compoundFraction = rational.ToCompoundFraction();
		BOOST_CHECK_EQUAL(rational.ToCompoundFraction().first, 2);
		VerifyRational(compoundFraction.second, 1, 4);

		rational = CRational(6, 7);
		compoundFraction = rational.ToCompoundFraction();
		BOOST_CHECK_EQUAL(rational.ToCompoundFraction().first, 0);
		VerifyRational(compoundFraction.second, 6, 7);

		rational = CRational(1, 7);
		compoundFraction = rational.ToCompoundFraction();
		BOOST_CHECK_EQUAL(rational.ToCompoundFraction().first, 0);
		VerifyRational(compoundFraction.second, 1, 7);
	}

	BOOST_AUTO_TEST_CASE(can_get_compound_negative_fraction)
	{
		auto rational = CRational(-9, 4);
		auto compoundFraction = rational.ToCompoundFraction();
		BOOST_CHECK_EQUAL(rational.ToCompoundFraction().first, -2);
		VerifyRational(compoundFraction.second, -1, 4);
	}

	BOOST_AUTO_TEST_CASE(unary_minus_returns_number_with_opposite_sign)
	{
		VerifyRational(-CRational(3, 5), -3, 5);
		VerifyRational(-CRational(-3, 5), 3, 5);
		VerifyRational(-CRational(-3, -5), -3, 5);
	}

	BOOST_AUTO_TEST_CASE(unary_plus_returns_number_equal_to_current)
	{
		VerifyRational(+CRational(3, 5), 3, 5);
		VerifyRational(+CRational(-3, 5), -3, 5);
		VerifyRational(+CRational(3, -5), -3, 5);
	}

	struct binary_addition_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(counts_binary_addition_of, binary_addition_)

		BOOST_AUTO_TEST_CASE(two_rational_numbers)
		{
			auto result = rational + CRational(1, 6);
			VerifyRational(result, 2, 3);
		}

		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			auto result = rational + 1;
			VerifyRational(result, 3, 2);
		}

		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			auto result = 1 + rational;
			VerifyRational(result, 3, 2);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct binary_subtraction_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(counts_binary_subtraction_of, binary_subtraction_)

		BOOST_AUTO_TEST_CASE(two_rational_numbers)
		{
			auto result = rational - CRational(1, 6);
			VerifyRational(result, 1, 3);
		}

		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			auto result = rational - 1;
			VerifyRational(result, -1, 2);
		}

		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			auto result = 1 - rational;
			VerifyRational(result, 1, 2);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct addition_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(counts_addition_a_, addition_)

		BOOST_AUTO_TEST_CASE(rational_number)
		{
			rational += CRational(1, 6);
			VerifyRational(rational, 2, 3);
		}

		BOOST_AUTO_TEST_CASE(integer_number)
		{
			rational += 1;
			VerifyRational(rational, 3, 2);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct subtraction_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(counts_subtraction_a, subtraction_)

		BOOST_AUTO_TEST_CASE(rational_number)
		{
			rational -= CRational(1, 6);
			VerifyRational(rational, 1, 3);
		}

		BOOST_AUTO_TEST_CASE(subtraction_integer_number)
		{
			rational -= 1;
			VerifyRational(rational, -1, 2);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct binary_multiplication_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(counts_binary_multiplication_of, binary_multiplication_)

		BOOST_AUTO_TEST_CASE(rational_integers)
		{
			auto result = rational * CRational(2, 3);
			VerifyRational(result, 1, 3);
		}

		BOOST_AUTO_TEST_CASE(rational_and_integer)
		{
			auto result = rational * -3;
			VerifyRational(result, -3, 2);
		}

		BOOST_AUTO_TEST_CASE(integer_and_rational)
		{
			auto result = 7 * rational;
			VerifyRational(result, 7, 2);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct bi_division_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(binary_division_of, bi_division_)

		BOOST_AUTO_TEST_CASE(rational_numbers)
		{
			auto result = rational / CRational(2, 3);
			VerifyRational(result, 3, 4);
		}

		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			auto result = rational / 5;
			VerifyRational(result, 1, 10);
		}

		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			auto result = 7 / rational;
			VerifyRational(result, 14, 1);
		}

		BOOST_AUTO_TEST_CASE(rational_and_zero_as_exeption)
		{
			BOOST_REQUIRE_THROW(auto result = rational / 0, std::invalid_argument::exception);
			BOOST_REQUIRE_THROW(auto result = rational / CRational(0, 1), std::invalid_argument::exception);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct multiplication_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(counts_multiplication_a, multiplication_)

		BOOST_AUTO_TEST_CASE(rational_number)
		{
			rational *= CRational(2, 3);
			VerifyRational(rational, 1, 3);
		}

		BOOST_AUTO_TEST_CASE(integer_number)
		{
			rational *= 3;
			VerifyRational(rational, 3, 2);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct division_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(counst_division_a, division_)

		BOOST_AUTO_TEST_CASE(rational_number)
		{
			rational /= CRational(2, 3);
			VerifyRational(rational, 3, 4);
		}

		BOOST_AUTO_TEST_CASE(integer_number)
		{
			rational /= 3;
			VerifyRational(rational, 1, 6);
		}

		BOOST_AUTO_TEST_CASE(rational_and_zero_throw_exeption)
		{
			BOOST_REQUIRE_THROW(rational /= 0, std::invalid_argument);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct equality_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(checks_equality_of, equality_)

		BOOST_AUTO_TEST_CASE(rational_numbers)
		{
			BOOST_CHECK(rational == CRational(1, 2));
			BOOST_CHECK(!(rational == CRational(2, 3)));
		}

		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			BOOST_CHECK(CRational(4, 1) == CRational(4));
			BOOST_CHECK(!(rational == CRational(7)));
		}

		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			BOOST_CHECK(CRational(3) == CRational(3, 1));
			BOOST_CHECK(!(CRational(3) == CRational(2, 3)));
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct inequality_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(checks_inequality_of, inequality_)

		BOOST_AUTO_TEST_CASE(rational_numbers)
		{
			BOOST_CHECK(!(rational != CRational(1, 2)));
			BOOST_CHECK(rational != CRational(2, 3));
		}

		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			BOOST_CHECK(!(CRational(4, 1) != CRational(4)));
			BOOST_CHECK(rational != CRational(7));
		}

		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			BOOST_CHECK(!(CRational(3) != CRational(3, 1)));
			BOOST_CHECK(CRational(3) != CRational(2, 3));
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct less_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(checks_less_of, less_)

		BOOST_AUTO_TEST_CASE(rational_numbers)
		{
			BOOST_CHECK(!(rational < CRational(1, 2)));

			BOOST_CHECK(!(CRational(2, 3) < rational));
		}

		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			BOOST_CHECK(rational < CRational(7));
			BOOST_CHECK(!(CRational(4, 1) < CRational(4)));
		}

		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			BOOST_CHECK(!(CRational(3) < CRational(3, 1)));
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct less_or_equality_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(checks_less_or_equality_of, less_or_equality_)

		BOOST_AUTO_TEST_CASE(rational_numbers)
		{
			BOOST_CHECK((rational <= CRational(1, 2)));

			BOOST_CHECK(!(CRational(2, 3) <= rational));
		}

		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			BOOST_CHECK(rational <= CRational(7));
			BOOST_CHECK(CRational(4, 1) <= CRational(4));
		}

		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			BOOST_CHECK(CRational(3) <= CRational(3, 1));
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct larger_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(checks_larger_of, larger_)

		BOOST_AUTO_TEST_CASE(rational_numbers)
		{
			BOOST_CHECK(!(rational > CRational(1, 2)));
			BOOST_CHECK((CRational(2, 3) > rational));
		}

		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			BOOST_CHECK(!(rational > CRational(7)));
			BOOST_CHECK(!(CRational(4, 1) > CRational(4)));
		}

		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			BOOST_CHECK(!(CRational(3) > CRational(3, 1)));
		}

		BOOST_AUTO_TEST_CASE(larger_two_integers)
		{
			
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct larger_or_equality_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(checks_larger_or_equality_of, larger_or_equality_)

		BOOST_AUTO_TEST_CASE(rational_numbers)
		{
			BOOST_CHECK((rational >= CRational(1, 2)));
			BOOST_CHECK((CRational(2, 3) >= rational));
		}

		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			BOOST_CHECK(!(rational >= CRational(7)));
			BOOST_CHECK(CRational(4, 1) >= CRational(4));
		}

		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			BOOST_CHECK(CRational(3) >= CRational(3, 1));
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct ostream_
	{
		CRational rational = CRational(7, 15);
	};

	BOOST_FIXTURE_TEST_SUITE(can_outputs_to_ostream_a, ostream_)

		BOOST_AUTO_TEST_CASE(rational_numbrs)
		{
			std::ostringstream strm;
			strm << rational;
			BOOST_CHECK_EQUAL(strm.str(), "7/15");
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct istream_
	{
		CRational rational;
	};

	BOOST_FIXTURE_TEST_SUITE(can_read_from_istream_a, istream_)

		BOOST_AUTO_TEST_CASE(rational_numbers)
		{
			std::istringstream strm("7/15");
			strm >> rational;
			VerifyRational(rational, 7, 15);
		}

		BOOST_AUTO_TEST_CASE(negative_rational_numbers)
		{
			std::istringstream strm("-7/15");
			strm >> rational;
			VerifyRational(rational, -7, 15);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()