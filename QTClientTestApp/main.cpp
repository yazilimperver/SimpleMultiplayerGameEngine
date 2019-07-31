#include "QTClientTestApp.h"
#include <QApplication.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTClientTestApp w;
	w.show();
	return a.exec();
}
