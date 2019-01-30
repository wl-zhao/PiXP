#pragma once
#include <mpreal.h>

class LnX
{
public:
	LnX();
	~LnX();
	// @params precision: expected precision
	// @return: precision for pi
	int init(int precision, bool print_params = false);
	mpfr::mpreal calc(mpfr::mpreal pi);
private:
	int n;
	int m2;
	int d1;
};

