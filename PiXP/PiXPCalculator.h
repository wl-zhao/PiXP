#pragma once
#include <QtWidgets/QWidget>
#include <mpreal.h>
#include "Pi.h"
#include "LnX.h"
#include "EXP.h"

class PiXPCalculator : public QObject
{
	Q_OBJECT
public slots:
	void calc(QString x_string, int precision, int method);
signals:
	void resultReady(const QString &result);

private:
	// solvers
	Pi solver_pi;
	LnX solver_lnpi;
	EXP solver_pixp;
};

