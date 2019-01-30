#include "EXP.h"
#include <math.h>
#include <iostream>

EXP::EXP()
{
}


EXP::~EXP()
{
}

int EXP::init(int d3, double x, bool print_params)
{
	double Delta = 0.5 * pow(10, -d3);
	double Ea = pow(3.2, ceil(x));
	for (N = 1; pow(N, 4) < pow(10, d3) * 2 * Ea * pow(x, 5) / 15; ++N);
	double Eh = pow(3.2, ceil(x / N));
	double h = 1.144 * x / N;
	m3 = d3 + ceil(log10(4 * (Ea - 1) * ((Ea + Delta) * Eh + 1) / h));
	d2 = ceil(d3 + log10(4 * x * Ea));
	d2 = (d2 > 6) ? d2 : 6;
	if (print_params) {
		using namespace std;
		cout << "N = " << N << endl << "m3 = " << m3 << endl << "d2 = " << d2;
	}
	return d2;
}

mpfr::mpreal EXP::calc(mpfr::mpreal a)
{
	using namespace mpfr;
	mpreal::set_default_prec(mpfr::digits2bits(m3 + 10));
	mpreal h = a / N;
	mpreal y = 1;
	mpreal K1, K2, K3, K4;
	for (int i = 0; i < N; i++) {
		K1 = y;
		K2 = y + h * K1 / 2;
		K3 = y + h * K2 / 2;
		K4 = y + h * K3;
		y = y + h * (K1 + 2 * K2 + 2 * K3 + K4) / 6;
	}
	return y;
}
