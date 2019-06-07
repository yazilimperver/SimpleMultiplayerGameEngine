#include <QtCore/QCoreApplication>
#include <NetworkLibrary/QTCPClient.h>
#include <NetworkLibrary/QTCPServer.h>
#include "QtClass.h"
#include <qobject>
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QTCPServer server;

	CommunicationParameters params;
	params.updateParameterValue(cIServerMedium_Parameter_LocalPort, 15000);

	server.assignParameters(params);
	server.initialize();
	server.startListening();

	return a.exec();
}
