#include "Pi.h"
#include <math.h>
#include <iostream>
#include "Sqrt3.h"

Pi::Pi()
{
}


Pi::~Pi()
{
}

void Pi::init(int d1, bool print_params, PiMETHOD method)
{
	_method = method;
	switch (method)
	{
	case EXTRAPOLATION:
		k = ceil(1 / 6.0 * (log2(0.12) + d1 * log2(10) - 6 * log2(3)));
		k = (k > 0) ? k : 0;
		m1 = ceil(d1 + log10(13.14) + k * log10(2.2));
		if (print_params) {
			using namespace std;
			cout << "calculate pi" << endl;
			std::cout << "k = " << k << std::endl << "m1 = " << m1 << std::endl;
		}
		break;
	case TAYLOR:
		n = ceil(log(32 * pow(10, d1)) / log(3) - 1);
		m1 = ceil(d1 + log10(4 * n));
		d0 = d1 + 1;
		if (print_params) {
			std::cout << "n = " << n << std::endl << "m1 = " << m1 << std::endl << "d0 = " << d0;
		}
		break;
	default:
		break;
	}
}

mpfr::mpreal Pi::calc()
{
	using namespace mpfr;
	if (_method == EXTRAPOLATION) {
		mpreal::set_default_prec(mpfr::digits2bits(m1 + 2));
		mpreal pi;
		mpreal pk = 3;
		for (int i = 1; i <= k; i++)
		{
			pk = calc_p(pk, i);
		}
		mpreal pk_plus_1 = calc_p(pk, k + 1);
		mpreal pk_plus_2 = calc_p(pk_plus_1, k + 2);

		pi = pk / 45 - 4 * pk_plus_1 / 9 + 64 * pk_plus_2 / 45;
		std::cout.precision(51);
		std::cout << pi << std::endl;
		return pi;
	}
	else {
		Sqrt3 s;
		s.init(d0, true);
		mpreal sqrt3 = s.calc();
		std::cout.precision(10);
		mpreal::set_default_prec(mpfr::digits2bits(m1 + 2));
		mpreal pi = 0;
		mpreal term;
		for (int i = 0; i <= n; i++) {
			term = 2 * sqrt3 / (pow(3, i) * (2 * i + 1));
			if (i % 2 == 0) {
				pi += term;
			}
			else {
				pi -= term;
			}
		}
		return pi;
	}
}

mpfr::mpreal Pi::calc_p(mpfr::mpreal pk_1, int k)
{
	using namespace mpfr;
	mpreal::set_default_prec(mpfr::digits2bits(m1 + k));
	return sqrt((pow(2, 2 * k) * n_0 * n_0 - n_0 * sqrt(pow(2, 4 * k) * n_0 * \
		n_0 - pow(2, 2 * k + 2) * pk_1 * pk_1)) / 2);
}
