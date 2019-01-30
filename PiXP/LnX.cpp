#include "lnx.h"
#include <math.h>
#include <iostream>

LnX::LnX()
{
}


LnX::~LnX()
{
}

int LnX::init(int d2, bool print_params)
{
	for (n = 1; pow(n, 4) < 3.04 * pow(10, d2); ++n);
	m2 = ceil(d2 + log10(10 * n + 8.8));
	d1 = d2 + 1;
	d1 = (d1 > 6) ? d1 : 6;
	if (print_params) {
		std::cout << "n = " << n << std::endl \
			<< "m2 = " << m2 << std::endl << "d1 = " << d1 << std::endl;
	}
	return d1;
}

mpfr::mpreal LnX::calc(mpfr::mpreal pi)
{
	using namespace mpfr;
	mpreal::set_default_prec(mpfr::digits2bits(m2 + 4));
	mpreal I = 0;
	mpreal h = (pi - 1) / n;
	I += h / 6 * (1 + 1 / pi + 4 * 1 / (1 + h / 2));
	for (int k = 1; k < n; k++) {
		mpreal xk = k * h + 1;
		I += h  / 6 * (2 * 1 / xk + 4 * 1 / (xk + h / 2));
	}
	return I;
}
