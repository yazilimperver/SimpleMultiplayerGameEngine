#include "QTServerTestApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTServerTestApp w;
	w.show();
	return a.exec();
}
