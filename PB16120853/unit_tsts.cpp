#include "number.hpp"
#include<iostream>


int main() {
	fraction a(1, 0), b(0, 1), c(2, 3), d(5, 6), e(8, 4), g(18, 9);
	fraction x;
	x = a + b;
	x = a * b;
	x = a - b;
	x = a / b;
	x = a / c;
	x = a + c;
	x = a * c;
	x = a - c;
	x = b + c;
	x = b - c;
	x = b * c;
	x = b / c;
	x = c * d;
	x = c / d;
	x = c + d;
	x = c - d;

}