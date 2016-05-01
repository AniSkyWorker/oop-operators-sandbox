#pragma once
#include <sstream>
#include <cmath>

class CRational final
{
public:
	CRational(int numerator = 0, int denominator = 1);
	std::pair<int, CRational>ToCompoundFraction() const;

	int GetNumerator() const;
	int GetDenominator() const;

	double ToDouble() const;

	const CRational operator -() const;
	const CRational operator +() const;

	CRational &  operator +=(const CRational &  rValue);
	CRational &  operator -=(const CRational &  rValue);

	CRational &  operator *=(const CRational &  rValue);
	CRational &  operator /=(const CRational &  rValue);

private:
	int m_numerator;
	int m_denominator;

	void Normalize();
};

unsigned GCD(unsigned a, unsigned b);

CRational const operator +(const CRational &  rational1, const CRational &  rational2);
CRational const operator -(const CRational &  rational1, const CRational &  rational2);
CRational const operator *(const CRational &  rational1, const CRational &  rational2);
CRational const operator /(const CRational &  rational1, const CRational &  rational2);

bool const operator ==(const CRational & rational1, const CRational & rational2);
bool const operator !=(const CRational & rational1, const CRational & rational2);

bool const operator <(const CRational & rational1, const CRational & rational2);
bool const operator <=(const CRational & rational1, const CRational & rational2);

bool const operator >(const CRational & rational1, const CRational & rational2);
bool const operator >=(const CRational & rational1, const CRational & rational2);

std::ostream &  operator <<(std::ostream & strm, const CRational & rational);
std::istream &  operator >>(std::istream & strm, CRational & rational);