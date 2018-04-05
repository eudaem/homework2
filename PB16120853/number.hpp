/*
* number.hpp
*
*/
#include <algorithm>
using namespace std;
class fraction;
bool is_bad_value(const fraction& x);
bool is_bad_value(const double& x);
long GCD(long u, long v) {
	if (!(u&&v)) {
		return 1;
	}
	while (v != 0) {
		long r = u % v;
		u = v;
		v = r;
	}
	return u;
}

class fraction {

public:
	long numerator, denominator;

	fraction(long m = 1, long n = 1) {
		this->numerator = m;
		this->denominator = n;
	}

	void reduction() {
		long x = GCD(this->numerator, this->denominator);
		this->numerator /= x;
		this->denominator /= x;
		if (this->denominator < 0) {
			this->numerator *= -1;
			this->denominator *= -1;
		}
		if (!this->numerator) {
			this->denominator = 1;
		}
		if (!this->denominator) {
			this->numerator = 1;
		}
		return;
	}

	fraction operator + (const fraction x) const {
		if (is_bad_value(*this))return *this;
		if (is_bad_value(x))return x;
		fraction result;
		result.numerator = this->numerator * x.denominator + this->denominator * x.numerator;
		result.denominator = this->denominator * x.denominator;
		result.reduction();
		return result;
	}


	fraction operator - (const fraction& x) const {
		if (is_bad_value(*this))return *this;
		if (is_bad_value(x))return x;
		fraction result;
		result.numerator = this->numerator * x.denominator - this->denominator * x.numerator;
		result.denominator = this->denominator * x.denominator;
		result.reduction();
		return result;
	}

	fraction operator * (const fraction& x) const {
		if (is_bad_value(*this))return *this;
		if (is_bad_value(x))return x;
		fraction result;
		result.numerator = this->numerator * x.numerator;
		result.denominator = this->denominator * x.denominator;
		result.reduction();
		return result;
	}

	fraction operator / (const fraction& x) const {
		if (is_bad_value(*this))return *this;
		if (is_bad_value(x))return x;
		fraction result;
		result.numerator = this->numerator * x.denominator;
		result.denominator = this->denominator * x.numerator;
		result.reduction();
		return result;
	}

	fraction operator ^ (fraction x) const {
		if (is_bad_value(*this))return *this;
		if (is_bad_value(x))return x;

		x.reduction();
		if (x.denominator != 1) {
			fraction bad_value;
			bad_value.numerator = 1;
			bad_value.denominator = 0;
			return bad_value;
		}
		long index = x.numerator;

		fraction result;
		result.numerator = powl(this->numerator, abs(index));
		result.denominator = powl(this->denominator, abs(index));
		if (index < 0) {
			long temp;
			temp = result.numerator;
			result.numerator = result.denominator;
			result.denominator = temp;
		}
		result.reduction();
		return result;
	}
};

bool is_bad_value(const fraction& x) {
	if (!x.denominator) {
		return true;
	}
	else {
		return false;
	}
}

bool is_bad_value(const double& x) {
	if (isnan(x) || isfinite(x) || isinf(x)) {
		return true;
	}
	else {
		return false;
	}
}