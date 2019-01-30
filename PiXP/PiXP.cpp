#include "PiXP.h"
#include <QDebug>
#include <iostream>

PiXP::PiXP(QWidget *parent)
	: QWidget(parent)
{
	init();
}

void PiXP::init()
{
	setFixedSize(800, 400);
	setObjectName("centerWidget");
	setWindowIcon(QIcon("./Resources/logo.ico"));
	setContentsMargins(10, 10, 10, 10);

	auto mainLayout = new QVBoxLayout(this);
	auto hLayout1 = new QHBoxLayout;
	piLabel = new QLabel(tr("calc pi: "));
	piComboBox = new QComboBox(this);
	QStringList piMethods;
	piMethods << tr("extra") << tr("taylor");
	piComboBox->addItems(piMethods);
	lnpiLabel = new QLabel(tr("calc ln pi: integral"));
	pixpLabel = new QLabel(tr("calc pi ^ x: ode"));
	hLayout1->addWidget(piLabel, 1);
	hLayout1->addWidget(piComboBox, 1);
	hLayout1->addStretch(1);
	hLayout1->addWidget(lnpiLabel, 2);
	hLayout1->addStretch(1);
	hLayout1->addWidget(pixpLabel, 2);
	mainLayout->addLayout(hLayout1, 1);

	auto hLayout2 = new QHBoxLayout;
	xLineEdit = new QLineEdit(this);
	xLineEdit->setPlaceholderText(tr("input x"));
	QRegExp re("([1-9]\\.[0-9]*)|([1-9])|(10)|(10\\.0*)");
	QRegExpValidator *validator = new QRegExpValidator(re, this);
	xLineEdit->setValidator(validator);
	precisionLabel = new QLabel(tr("set precision: "), this);
	precisionBox = new QSpinBox(this);
	precisionBox->setRange(1, 100);
	solveButton = new QPushButton(tr("solve"), this);
	hLayout2->addWidget(xLineEdit, 2);
	hLayout2->addStretch(1);
	hLayout2->addWidget(precisionLabel, 1);
	hLayout2->addWidget(precisionBox, 1);
	hLayout2->addStretch(1);
	hLayout2->addWidget(solveButton, 2);
	mainLayout->addLayout(hLayout2, 1);

	auto hLayout3 = new QHBoxLayout;
	resultTextEdit = new QTextEdit(this);
	resultTextEdit->setReadOnly(true);
	resultLabel = new QLabel(tr("result: "), this);
	hLayout3->addSpacing(30);
	hLayout3->addWidget(resultLabel);
	hLayout3->addWidget(resultTextEdit);
	hLayout3->addSpacing(30);
	hLayout3->setMargin(20);
	mainLayout->addLayout(hLayout3);

	timeLabel = new QLabel(this);
	mainLayout->addWidget(timeLabel);

	connect(solveButton, SIGNAL(clicked()), this, SLOT(onSolve()));
	connect(xLineEdit, SIGNAL(returnPressed()), this, SLOT(onSolve()));
	connect(xLineEdit, &QLineEdit::textChanged, this, [&]() {
		if (!xLineEdit->text().contains("."))
			precisionBox->setRange(1, 100);
		else 
		{
			precisionBox->setRange(1, 15);
			if (precisionBox->value() > 15)
			{
				precisionBox->setValue(15);
			}
		}
	});

	// Calculator
	calculator = new PiXPCalculator;
	calculator->moveToThread(&calcThread);
	connect(&calcThread, &QThread::finished, calculator, &QObject::deleteLater);
	connect(this, &PiXP::operate, calculator, &PiXPCalculator::calc);
	connect(calculator, &PiXPCalculator::resultReady, this, &PiXP::handleResults);
	calcThread.start();
}

void PiXP::handleResults(const QString & result)
{
	resultTextEdit->setText(result);
	xLineEdit->setEnabled(true);
	precisionBox->setEnabled(true);
	solveButton->setEnabled(true);
	piComboBox->setEnabled(true);
	timeLabel->setText(QString("%1%2 ms").arg(tr("Cost: ")).arg(timer.elapsed()));
}

void PiXP::onSolve()
{
	QString text = xLineEdit->text();
	if (text.isEmpty())
		return;
	xLineEdit->setEnabled(false);
	precisionBox->setEnabled(false);
	solveButton->setEnabled(false);
	piComboBox->setEnabled(false);
	timeLabel->setText(tr("Solving..."));
	timer.start();
	//resultTextEdit->setEnabled(false);
	emit operate(text, precisionBox->value(), piComboBox->currentIndex());
	//qDebug() << "here";
	//using namespace mpfr;
	//mpreal::set_default_prec(mpfr::digits2bits(text.length() + 1));
	//mpreal x = xLineEdit->text().toStdString().c_str();
	//qDebug() << "x: " << x.toString().c_str();

	//// start init
	//int d3 = precisionBox->value();
	//int d2 = solver_pixp.init(d3 + text.length(), x.toDouble(), true);
	//int d1 = solver_lnpi.init(d2, true);
	//solver_pi.init(d1, true, Pi::PiMETHOD(piComboBox->currentIndex()));

	//// solve
	//mpreal pi = solver_pi.calc();
	////3.141592653589793238462643383279502884197169399375105820974
	//mpreal lnpi = solver_lnpi.calc(pi);
	////1.144729885849400174143427351353058711647294812915311571513
	//mpreal::set_default_prec(mpfr::digits2bits(d2 + text.length()));
	//x.setPrecision(mpfr::digits2bits(d2));
	//x = text.toStdString().c_str();
	//mpreal test = x * lnpi;
	//mpreal pixp = solver_pixp.calc(x * lnpi);
	////93648.04747608302097371669018491934563599815727551469412705
	//auto convert = [](mpreal p) {
	//	return QString::fromStdString(p.toString());
	//};

	//qDebug() << "lnpi" << convert(test);
	//qDebug() << convert(pi);
	//qDebug() << convert(lnpi);

	//qDebug() << convert(x * lnpi);
	//qDebug() << convert(pixp);

	//// show results
	//pixp = pixp + 0.5 * mpfr::pow(10, -d3);
	//QString result = QString::fromStdString(pixp.toString());
	//QStringList splited = result.split(".");
	//splited[1] = splited[1].mid(0, d3);
	//resultTextEdit->setText(QString("%1.%2").arg(splited[0]).arg(splited[1]));
}
