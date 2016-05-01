#include "stdafx.h"
#include "../task1/Rational.h"
#include <utility>
#include <stdexcept>

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}

	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}

double CRational::ToDouble()const
{
	return m_numerator / m_denominator;
}

const CRational CRational::operator-()const
{
	return CRational(-m_numerator, m_denominator);
}

const CRational CRational::operator+()const
{
	return *this;
}

CRational & CRational::operator +=(const CRational & rValue)
{
	*this = *this + rValue;
	return *this;
}

CRational & CRational::operator -=(const CRational & rValue)
{
	*this = *this - rValue;
	return *this;
}

CRational &  CRational::operator *=(const CRational & rValue)
{
	*this = *this * rValue;
	return *this;
}

CRational &  CRational::operator /=(const CRational & rValue)
{
	*this = *this / rValue;
	return *this;
}

const CRational operator *(const CRational & rational1, const CRational & rational2)
{
	return (CRational(rational1.GetNumerator() * rational2.GetNumerator()
		, rational1.GetDenominator() * rational2.GetDenominator()));
}

const CRational operator +(const CRational & rational1, const CRational & rational2)
{
	return (CRational((rational1.GetNumerator() * rational2.GetDenominator())
		+ (rational2.GetNumerator() * rational1.GetDenominator()),
		rational1.GetDenominator() * rational2.GetDenominator()));
}

const CRational operator -(const CRational & rational1, const CRational & rational2)
{
	return rational1 + -rational2;
}

const CRational operator /(const CRational & rational1, const CRational & rational2)
{
	return (CRational(rational1.GetNumerator() * rational2.GetDenominator()
		, rational1.GetDenominator() * rational2.GetNumerator()));
}

bool const operator ==(const CRational & rational1, const CRational & rational2)
{
	return (rational1.GetNumerator() == rational2.GetNumerator()
		&& rational1.GetDenominator() == rational2.GetDenominator());
}

bool const operator !=(const CRational & rational1, const CRational & rational2)
{
	return !(rational1 == rational2);
}

bool const operator <(const CRational & rational1, const CRational & rational2)
{
	return (rational1.GetNumerator() * rational2.GetDenominator()
		< rational2.GetNumerator() * rational1.GetDenominator());
}

bool const operator <=(const CRational & rational1, const CRational & rational2)
{
	return (rational1 == rational2 || rational1 < rational2);
}

bool const operator >(const CRational & rational1, const CRational & rational2)
{
	return !(rational1 <= rational2);
}

bool const operator >=(const CRational & rational1, const CRational & rational2)
{
	return (rational1 == rational2 || rational1 > rational2);
}

std::ostream & operator <<(std::ostream & strm, const CRational & rational)
{
	strm << rational.GetNumerator() << '/' << rational.GetDenominator();
	return strm;
}

std::istream & operator >> (std::istream & strm, CRational & rational)
{
	std::streamoff startPos = strm.tellg();
	int numerator;
	int denominator;
	if ((strm >> numerator) && (strm.get() == '/') && (strm >> denominator))
	{
		rational = CRational(numerator, denominator);
		return strm;
	}
	strm.seekg(startPos);
	return strm;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int integer = static_cast<int>(ToDouble());
	int numerator = m_numerator - m_denominator * integer;

	return std::make_pair(integer, CRational(numerator, m_denominator));
}