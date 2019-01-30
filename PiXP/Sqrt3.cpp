#include "Sqrt3.h"
#include <math.h>
#include <iostream>

Sqrt3::Sqrt3()
{
}


Sqrt3::~Sqrt3()
{
}

void Sqrt3::init(int d0, bool print_params)
{
	n = ceil(log2((log10(0.125) - d0) / (log10(0.0006))));
	m0 = d0 + 1;
	if (print_params) {
		using namespace std;
		cout << "n = " << n << endl << "m0 = " << m0 << endl;
	}
}

mpfr::mpreal Sqrt3::calc()
{
	using namespace mpfr;
	mpreal::set_default_prec(mpfr::digits2bits(m0 + 2));
	mpreal x = 1.732;
	for (int i = 0; i < n; i++) {
		x = x / 2 + 3 / (2 * x);
	}
	return x;
}
