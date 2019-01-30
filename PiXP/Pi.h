#pragma once
#include <mpreal.h>
class Pi
{
public:
	enum PiMETHOD
	{
		EXTRAPOLATION,
		TAYLOR,
	};
	Pi();
	~Pi();
	void init(int d1, bool print_params = false, PiMETHOD method = TAYLOR);//d: expection precision
	mpfr::mpreal calc();

	// calculate pk from p_{k-1}
private:
	PiMETHOD _method;

	mpfr::mpreal calc_p(mpfr::mpreal pk_1, int k);
	const int p_0 = 3;
	const int n_0 = 6;
	int m1; // digits for each step
	int k; // iteration times

	//Taylor method
	int n;
	int d0;
};

