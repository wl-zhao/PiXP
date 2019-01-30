#pragma once

#include <QtWidgets/QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QSPinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QThread>
#include <QTime>
#include "PiXPCalculator.h"

class PiXP : public QWidget
{
	Q_OBJECT

public:
	PiXP(QWidget *parent = Q_NULLPTR);
	~PiXP() {
		calcThread.quit();
		calcThread.wait();
	}

private:
	QLabel *piLabel;
	QComboBox *piComboBox;
	QLabel *lnpiLabel;
	QLabel *pixpLabel;

	QLineEdit *xLineEdit;
	QSpinBox *precisionBox;
	QLabel *precisionLabel;
	QPushButton *solveButton;

	QTextEdit *resultTextEdit;
	QLabel *resultLabel;
	QLabel *timeLabel;
	QTime timer;

	// calculator
	PiXPCalculator *calculator;
	QThread calcThread;

private:
	void init();
protected slots:
	void onSolve();
	void handleResults(const QString &result);
signals:
	void operate(QString x_string, int d3, int method);
};
