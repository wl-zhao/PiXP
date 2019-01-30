#include "PiXP.h"
#include <QtWidgets/QApplication>
#include <QTranslator>
#include <QDebug>
#include <QFile>

void setStyle(const QString &style) {
	QFile qss(style);
	qss.open(QFile::ReadOnly);
	qApp->setStyleSheet(qss.readAll());
	qss.close();
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTranslator *translator = new QTranslator();
	if (translator->load(":/PiXP/pixp_zh.qm"))
		qApp->installTranslator(translator);
	else
		qDebug() << "unable to load translator file" << endl;
	QFont f(QString::fromLocal8Bit("»ªÎÄ¿¬Ìå"), 13);
	a.setFont(f);
	setStyle("./Resources/white.qss");
	PiXP w;
	w.show();
	return a.exec();
}
