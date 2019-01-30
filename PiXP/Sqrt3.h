#pragma once
#include <mpreal.h>
class Sqrt3
{
public:
	Sqrt3();
	~Sqrt3();
	void init(int d0, bool print_params = false);
	mpfr::mpreal calc();
private:
	int n;
	int m0;
	mpfr::mpreal x0 = 1.732;
};

