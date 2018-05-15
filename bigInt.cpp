#include <algorithm>
#include "bigInt.h"
using namespace std;
namespace ExactArithmetic
{

	//  Default constructor, creates an Integer with value 0.
	Integer::Integer()
	{
		digits.push_back(0);
	}

	//  Converting constructor.
	Integer::Integer(unsigned long long int x)
	{
		if (x == 0) {
			digits.push_back(0);
			return;
		}
		while (x > 0)
		{
			digits.push_back(x % 10);
			x = x / 10;
		}
	}

	// Accepts a sequence of digits.
	// For any other input, throws a std::invalid_argument exception.
	// (For full integers, it should also allow an optional initial  '+' or '-' character.)
	Integer::Integer(const std::string & s)
	{
		for (int i = s.length()-1; i >= 0; i--)
		{
			digits.push_back(s[i] - '0');
		}
	}

	//  Adjust
	void Integer::adjust()
	{
		digits.push_back(0);		// most sign zero, to carry into
		int c = 0, s, d;
		std::list<Digit>::iterator	bni;

		for (bni = digits.begin(); bni != digits.end(); bni++)
		{
			d = *bni + c;
			s = d % 10;
			c = d / 10;
			*bni = s;
		}

		while ((digits.back() == 0) && (digits.size() > 1))
		digits.pop_back();		// remove leading zeros
	}


	//  Arithmetic Operators
	Integer Integer::operator+(const Integer & right) const
	{
		Integer res = *this;	// Copy left argument to result list

		// ensure l is long enough & add in all of r
		// will work with const & parameters
		int ll = digits.size(), lr = right.digits.size();

		int longer = (ll < lr ? lr : ll);

		// Could pad to same length (with leading 0)
		std::fill_n(back_inserter(res.digits), longer - ll, 0);

		// Add right argument to result
		std::transform(right.digits.begin(), right.digits.end(),
			res.digits.begin(), res.digits.begin(), std::plus<int>());

		// Adjust the result if there is any digits > 9
		res.adjust();

		return (res);

	}

	Integer Integer::operator-(const Integer &) const
	{
		Integer res;

		return res;
	}

	Integer Integer::operator*(const Integer &) const
	{
		Integer res;

		return res;
	}

	Integer Integer::operator/(const Integer &) const // Throws a DivideByZeroError for a 0 divisor.
	{
		Integer res;

		return res;
	}

	Integer Integer::operator%(const Integer &) const // Throws a DivideByZeroError for a 0 divisor.
	{
		Integer res;

		return res;
	}

	// Comparison operators
	bool Integer::operator<(const Integer &r) const
	{
		if (r.digits.size() > digits.size()) return false;
		if (r.digits.size() < digits.size()) return true;
		if (*this == r) return false;

		Integer rr = r;
		std::list<Digit> lD = digits, rD = rr.digits;
		//std::list<Digit>::iterator lIterator = lD.end(),
		//	rIterator = rD.end();
		//for (; lIterator != lD.begin(); lIterator--, rIterator--) {
		//	if (*lIterator > *rIterator) return false;
		//}
		std::reverse(lD.begin(), lD.end());
		std::reverse(rD.begin(), rD.end());
		std::pair<std::list<Digit>::iterator, std::list<Digit>::iterator> num;
		num = std::mismatch(lD.begin(), lD.end(), rD.begin());
		if (*num.first > *num.second) return false;
		return true;
	}

	bool Integer::operator>(const Integer &r) const
	{
		if (r.digits.size() < digits.size()) return false;
		if (r.digits.size() > digits.size()) return true;
		if (*this == r) return false;

		Integer rr = r;
		std::list<Digit> lD = digits, rD = rr.digits;
		//std::list<Digit>::iterator lIterator = lD.end(),
		//	rIterator = rD.end();
		//for (; lIterator != lD.begin(); lIterator--, rIterator--) {
		//	if (*lIterator < *rIterator) return false;
		//}
		std::reverse(lD.begin(), lD.end());
		std::reverse(rD.begin(), rD.end());
		std::pair<std::list<Digit>::iterator, std::list<Digit>::iterator> num;
		num = std::mismatch(lD.begin(), lD.end(), rD.begin());
		if (*num.first < *num.second) return false;
		return true;
	}

	bool Integer::operator<=(const Integer &r) const
	{
		return *this < r || *this == r;
	}

	bool Integer::operator>=(const Integer &r) const
	{
		return *this > r || *this == r;
	}

	bool Integer::operator==(const Integer &r) const
	{
		if (digits.size() != r.digits.size()) {
			return false;
		}
		Integer rr = r;
		std::list<Digit> lD = digits,
			rD = rr.digits;
		std::list<Digit>::iterator lIterator = lD.begin(),
			rIterator = rD.begin();

		for (; lIterator != lD.end(); lIterator++, rIterator++){
			if (*lIterator != *rIterator) return false;
		}
		
		return true;
	}

	bool Integer::operator!=(const Integer &r) const
	{
		if (*this == r) return false;
		return true;
	}


	// Compound Assignment operators
	Integer & Integer::operator+=(const Integer &)
	{
		Integer res;

		return res;
	}

	Integer & Integer::operator-=(const Integer &)
	{
		Integer res;

		return res;
	}

	Integer & Integer::operator*=(const Integer &)
	{
		Integer res;

		return res;
	}

	// Throws a DivideByZeroError for a 0 divisor.
	Integer & Integer::operator/=(const Integer &)
	{
		Integer res;

		return res;
	}

	// Throws a DivideByZeroError for a 0 divisor.
	Integer & Integer::operator%=(const Integer &)
	{
		Integer res;

		return res;
	}

	// Increment and Decrement operators
	// pre-increment
	Integer & Integer::operator++()
	{
		Integer res;

		return res;
	}

	// post-increment
	Integer Integer::operator++(int)
	{
		Integer res;

		return res;
	}

	// pre-decrement
	Integer & Integer::operator--()
	{
		Integer res;

		return res;
	}

	// post-decrement
	Integer Integer::operator--(int)
	{
		Integer res;

		return res;
	}

	std::string Integer::toString() const
	{
		std::string aStr;

		return aStr;
	}

	// Friend declarations
	std::ostream & operator<<(std::ostream & out, const Integer &)
	{
		return out;
	}

	std::istream & operator>>(std::istream & in, Integer &)
	{
		return in;
	}

} // End of namespace ExactArithmetic