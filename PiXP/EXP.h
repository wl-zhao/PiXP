#pragma once
#include <mpreal.h>
class EXP
{
public:
	EXP();
	~EXP();
	int init(int d3, double x, bool print_params = false);
	mpfr::mpreal calc(mpfr::mpreal a);

private:
	int N;
	int m3;
	int d2;
};

