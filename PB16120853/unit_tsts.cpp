#include "number.hpp"
#include<iostream>
void number_test() {
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
	x = a ^ b;
	x = a ^ c;
	x = a ^ d;
	x = a ^ e;
	x = a ^ g;
	x = b ^ c;
	x = b ^ a;
	x = b ^ d;
	x = b ^ e;
	x = b ^ g;
	x = e * g;
	x = e - g;
	x = e + g;
	x = e / g;

}