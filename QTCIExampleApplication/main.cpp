#include <QtCore/QCoreApplication>
#include <../QTCIExampleLibrary/QTCIExampleLibrary.h>
#include <iostream>

void summationCompletedSlot(int value)
{
	std::cout << "The result of summation is: " << value << '\n';
}

int main(int argc, char *argv[])
{
	QTCIExampleLibrary instance;

	QObject::connect(&instance, &QTCIExampleLibrary::summationCompleted, summationCompletedSlot);
	instance.performSummation(3);

	QCoreApplication a(argc, argv);
	return a.exec();
}
