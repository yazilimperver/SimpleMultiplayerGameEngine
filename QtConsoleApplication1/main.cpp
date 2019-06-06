#include <QtCore/QCoreApplication>
#include <../NetworkLibrary/QTCPClient.h>
#include "QtClass.h"
#include <qobject>
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QTCPClient tmp;
	QtClass deneme{ 0 };

	CommunicationParameters params;
	params.updateParameterValue("PortNo", 15000);
	params.updateParameterValue("Address", std::string("127.0.0.1"));
	tmp.assignParameters(params);


	QObject::connect(&tmp, &QTCPClient::connected, &deneme, &QtClass::connected);
	tmp.initialize();
	tmp.connect();
	tmp.disconnect();

	return a.exec();
}
