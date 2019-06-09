#include <QtCore/QCoreApplication>
#include <NetworkLibrary/QTCPClient.h>
#include <NetworkLibrary/QTCPServer.h>
#include "QtClass.h"
#include <qobject>
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QtClass tmp{ nullptr };
	QTCPServer server;

	QObject::connect(&server, &QTCPServer::clientDisconnected, &tmp, &QtClass::disconnected);
	QObject::connect(&server, &QTCPServer::clientDataReadyToRead, &tmp, &QtClass::dataArrived);
	CommunicationParameters params;
	params.updateParameterValue(cIServerMedium_Parameter_LocalPort, 15000);

	server.assignParameters(params);
	server.initialize();
	server.startListening();

	return a.exec();
}
