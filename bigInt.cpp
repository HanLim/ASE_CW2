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
		Integer res = *this;	

		int ll = digits.size(), lr = right.digits.size();

		int longer = (ll < lr ? lr : ll);

		std::fill_n(back_inserter(res.digits), longer - ll, 0);

		std::transform(right.digits.begin(), right.digits.end(),
			res.digits.begin(), res.digits.begin(), std::plus<int>());

		res.adjust();
		
		return (res);

	}

	Integer Integer::operator-(const Integer & right) const
	{
		Integer l = *this, r = right;
		std::list<Digit>::iterator lIterator = l.digits.begin(),
			rIterator = r.digits.begin();

		for (; lIterator != l.digits.end() && rIterator != r.digits.end(); lIterator++, rIterator++) {
			if (*lIterator < *rIterator) {
				int count = 0;

				do {
					if (lIterator == l.digits.end()) break;
					*lIterator += 10;
					lIterator++;
					*lIterator -= 1;
					count++;
				} while (*lIterator < 0);

				for (int a = 0; a < count; a++) {
					lIterator--;
				}
			}
			*lIterator -= *rIterator;
		}
		l.adjust();
		return l;
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
	Integer & Integer::operator+=(const Integer &r)
	{
		*this = *this + r;
		return *this;
	}

	Integer & Integer::operator-=(const Integer & r)
	{
		*this = *this - r;
		return *this;
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
		*this = *this + Integer(1);
		adjust();
		return *this;
	}

	// post-increment
	Integer Integer::operator++(int)
	{
		Integer res = *this;
		*this += Integer(1);
		adjust();
		return res;
	}

	// pre-decrement
	Integer & Integer::operator--()
	{
		*this = *this - Integer(1);
		adjust();
		return *this;
	}

	// post-decrement
	Integer Integer::operator--(int)
	{
		Integer res = *this;
		*this -= Integer(1);
		adjust();
		return res;
	}

	std::string Integer::toString() const
	{
		std::string str;
		Integer res = *this;
		std::list<Digit>::reverse_iterator first = res.digits.rbegin();
		std::list<Digit>::reverse_iterator last = res.digits.rend();
		while (first != last) {
			str.push_back(*first + '0');
			first++;
		}
		return str;
	}

	// Friend declarations
	std::ostream & operator<<(std::ostream & out, const Integer & integer)
	{
		out << integer.toString();
		return out;
	}

	std::istream & operator>>(std::istream & in, Integer & integer)
	{
		std::string str;
		in >> str;
		integer = Integer(str);
		return in;
	}

} // End of namespace ExactArithmetic