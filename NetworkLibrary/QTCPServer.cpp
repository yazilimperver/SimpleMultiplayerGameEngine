#include <NetworkLibrary/QTCPServer.h>
#include <NetworkLibrary/PropertyItem.h>
#include <NetworkLibrary/QTConnectedClient.h>

#include <QTcpSocket>
#include <QHostAddress>
#include <iostream>

QTCPServer::QTCPServer()
	: mTCPServer{this}
{
}

void QTCPServer::assignParameters(const CommunicationParameters& parameters)
{
	mParameters = parameters;
}

bool QTCPServer::initialize()
{
	mIsInitialized = false;

	// 0) Check first of all pending connection parameter is provided
	if (true == mParameters.hasParameter(cIServerMedium_Parameter_MaxPendingConnections))
	{
		int maxPendingConnections{ 0 };
		mParameters.getParameterValue<int>(cIServerMedium_Parameter_MaxPendingConnections, maxPendingConnections);

		mTCPServer.setMaxPendingConnections(maxPendingConnections);
	}

	// 1) Check the list of parameters to see if required parameters are provided
	bool hasLocalPort = mParameters.hasParameter(cIServerMedium_Parameter_LocalPort);
	bool hasLocalAddress = mParameters.hasParameter(cIServerMedium_Parameter_LocalAddress);

	if (false == hasLocalAddress && true == hasLocalPort)
	{
		mIsInitialized = true;
		mParameters.getParameterValue<int>(cIServerMedium_Parameter_LocalPort, mListeningPort);
	}
	else if (true == hasLocalAddress && true == hasLocalPort)
	{
		mIsInitialized = true;
		mParameters.getParameterValue<int>(cIServerMedium_Parameter_LocalPort, mListeningPort);
		mParameters.getParameterValue<std::string>(cIServerMedium_Parameter_LocalAddress, mLocalAddress);
	}

	// Server signal slots
	connect(&mTCPServer, SIGNAL(newConnection()), this, SLOT(newClientConnected()));
	connect(&mTCPServer, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(acceptErrorOccurred(QAbstractSocket::SocketError)));

	if (false == mIsInitialized)
		std::cout << "[QTCPServer] Initialization failed!" << '\n';
	
	return mIsInitialized;
}

void QTCPServer::finalize()
{
	// Close socket if not already
	if (mTCPServer.isListening())
	{
		mTCPServer.disconnect();
		mTCPServer.close();
	}
}

bool QTCPServer::isInitialized()
{
	return mIsInitialized;
}

void QTCPServer::startListening()
{
	if (true == mIsInitialized)
		mTCPServer.listen(QHostAddress(mLocalAddress.c_str()), mListeningPort);
}

void QTCPServer::stopListening()
{
	if (mTCPServer.isListening())
		mTCPServer.disconnect();
}

bool QTCPServer::isListening()
{
	return mTCPServer.isListening();
}

void QTCPServer::disconnectClient(uUInt64 clientId)
{
	if (auto itr = mClientMapping.find(clientId); itr != mClientMapping.end())
		itr->second->disconnect();
}

bool QTCPServer::isConnected(uUInt64 clientId)
{
	bool isConnected{ false };
	
	if (auto itr = mClientMapping.find(clientId); itr != mClientMapping.end())
		isConnected = itr->second->isActive();

	return isConnected;
}

void QTCPServer::getClientInformation(uUInt64 clientId, std::vector<PropertyItem>& clientInfo)
{
	if (auto itr = mClientMapping.find(clientId); itr != mClientMapping.end())
		itr->second->getClientInformation(clientInfo);
}

IConnectedClient* QTCPServer::getConnectedClientInterface(uUInt64 clientId)
{
	IConnectedClient* result{ nullptr };

	if (auto itr = mClientMapping.find(clientId); itr != mClientMapping.end())
		result = itr->second;

	return result;
}

void QTCPServer::getConnectedClientList(std::vector<uUInt64>& clientIdList)
{
	clientIdList.clear();

	for (auto& [clientId, connectedClient] : mClientMapping)
		clientIdList.push_back(clientId);
}

void QTCPServer::newClientConnected()
{
	// Traverse all new pending connections
	while (mTCPServer.hasPendingConnections())
	{
		auto newConn = mTCPServer.nextPendingConnection();

		uInt64 currentId = mClientSeedId;
		std::cout << "[QTCPServer] A new client with given id : " << currentId << " is connected!" << '\n';

		mClientIdMapping[newConn] = currentId;
		mClientMapping[currentId] = new QTConnectedClient(currentId, newConn);

		// add new signal/slot for newly connected client
		connect(newConn, &QIODevice::readyRead, [=] {clientDataReadyToRead(currentId); });
		connect(newConn, &QAbstractSocket::disconnected, [=] {clientDisconnected(currentId); });
		connect(newConn, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(clientErrorOccurred(QAbstractSocket::SocketError)));

		mClientSeedId++;

		// Inform listeners
		emit newClientConnected(currentId);
	}
}

void QTCPServer::clientErrorOccurred(QAbstractSocket::SocketError socketError)
{
	QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

	if (nullptr != socket)
	{
		if (auto clientIdItr = mClientIdMapping.find(socket); clientIdItr != mClientIdMapping.end())
		{
			uUInt64 clientId = clientIdItr->second;

			switch (socketError)
			{
			case QAbstractSocket::RemoteHostClosedError:
			{
				std::cout << "[QTCPServer] Client with given ID: " << clientId << " is disconnected!" << '\n';
			}
			break;
			default:
				std::cout << "[QTCPServer] Client Error: " << socket->errorString().data() << '\n';
			}

			emit clientErrorOccurred(clientId, static_cast<int>(socketError));
		}
		else
			std::cout << "[QTCPServer] Given client not found in currently connected client list!" << std::endl;
	}
}

void QTCPServer::acceptErrorOccurred(QAbstractSocket::SocketError socketError)
{
	std::cout << "[QTCPServer] Server Accept Error! Error: " << mTCPServer.errorString().data() << '\n';
}
