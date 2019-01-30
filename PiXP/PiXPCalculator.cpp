#include "PiXPCalculator.h"
#include <QDebug>

void PiXPCalculator::calc(QString x_string, int d3, int method)
{
	mpfr::mpreal pixp;
	auto convert = [](mpfr::mpreal p) {
		return QString::fromStdString(p.toString());
	};
	if (x_string.length() == 1)//integer
	{
		using namespace mpfr;
		mpreal x_real = x_string.toStdString().c_str();
		x_real += 0.5;
		int x = (int)x_real.toDouble();
		qDebug() << "x = " << x;
		int m3 = ceil(d3 + x * log10(3.15));
		int d1 = ceil(d3 + 2 * x * std::pow(3.15, x - 1));
		solver_pi.init(d1, true, Pi::PiMETHOD(method));
		mpreal pi = solver_pi.calc();
		pixp.setPrecision(mpfr::digits2bits(m3 + 5));
		pixp = pow(pi, x);

		qDebug() << "pi = " << convert(pi);
		qDebug() << "pixp" << convert(pixp);
	}
	else
	{
		using namespace mpfr;
		int length = x_string.length();
		mpreal::set_default_prec(mpfr::digits2bits(length + 1));
		mpreal x = x_string.toStdString().c_str();

		// start init
		int d2 = solver_pixp.init(d3 + length, x.toDouble(), true);
		int d1 = solver_lnpi.init(d2, true);
		solver_pi.init(d1, true, Pi::PiMETHOD(method));

		// solve
		mpreal pi = solver_pi.calc();
		//3.141592653589793238462643383279502884197169399375105820974
		mpreal lnpi = solver_lnpi.calc(pi);
		//1.144729885849400174143427351353058711647294812915311571513
		mpreal::set_default_prec(mpfr::digits2bits(d2 + length));
		x.setPrecision(mpfr::digits2bits(d2));
		x = x_string.toStdString().c_str();
		mpreal test = x * lnpi;
		pixp = solver_pixp.calc(x * lnpi);

		qDebug() << "pi = " << convert(pi);
		qDebug() << "lnpi = " << convert(lnpi);
		qDebug() << "pixp" << convert(pixp);
	}
	// show results
	pixp = pixp + 0.5 * mpfr::pow(10, -d3);
	QString result = QString::fromStdString(pixp.toString());
	QStringList splited = result.split(".");
	splited[1] = splited[1].mid(0, d3);
	emit resultReady(QString("%1.%2").arg(splited[0]).arg(splited[1]));
}