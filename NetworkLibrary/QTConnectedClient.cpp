#include <NetworkLibrary/QTConnectedClient.h>
#include <NetworkLibrary/IServerMedium.h>
#include <NetworkLibrary/PropertyItem.h>
#include <NetworkLibrary/QTConnectedClient.h>

#include <QTcpSocket>
#include <QHostAddress>
#include <iostream>

QTConnectedClient::QTConnectedClient(uInt64 uniqueId, QTcpSocket*& clientSocket)
	: mClientSocket{ clientSocket }
	, mUniqueId{uniqueId}
{

}

QTcpSocket* QTConnectedClient::getUnderlyingSocket()
{
	return mClientSocket;
}

uInt64 QTConnectedClient::getClientId()
{
	return mUniqueId;
}

bool QTConnectedClient::isActive()
{
	return mClientSocket->isOpen();
}

void QTConnectedClient::getClientInformation(std::vector<PropertyItem>& clientInfo)
{
	if (mClientSocket->state() == QAbstractSocket::ConnectedState)
	{
		clientInfo.clear();

		// fill peer data
		clientInfo.push_back(PropertyItem{ cParameter_PeerName, mClientSocket->peerName() });
		clientInfo.push_back(PropertyItem{ cParameter_PeerAddress, mClientSocket->peerAddress().toString() });
		clientInfo.push_back(PropertyItem{ cParameter_PeerPort, mClientSocket->peerPort() });
	}
}

uInt64 QTConnectedClient::readData(uInt64 maxByteCount, uByte* data)
{
	uInt64 size{ -1 };
	
	if (mClientSocket->isOpen())
		size = mClientSocket->read(reinterpret_cast<char*>(data), maxByteCount);

	return size;
}

QByteArray QTConnectedClient::readData(uInt64 maxByteCount)
{
	return mClientSocket->read(maxByteCount);
}

uInt64 QTConnectedClient::writeData(const uByte* data, uInt64 maxSize)
{
	if (nullptr != data)
		return mClientSocket->write(reinterpret_cast<const char*>(data), maxSize);
	else
		return -1;
}

uInt64 QTConnectedClient::writeData(const uChar* data)
{
	if (nullptr != data)
		return mClientSocket->write(reinterpret_cast<const char*>(data));
	else
		return -1;
}

void QTConnectedClient::disconnect()
{
	if (mClientSocket->isOpen())
		mClientSocket->disconnectFromHost();
}

uInt64 QTConnectedClient::availableDataSize()
{
	uInt64 size = 0;
	
	if (mClientSocket->isOpen())
		size = mClientSocket->bytesAvailable();
	
	return size;
}
