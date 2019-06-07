#include <NetworkLibrary/QTConnectedClient.h>
#include <NetworkLibrary/IServerMedium.h>
#include <NetworkLibrary/PropertyItem.h>
#include <NetworkLibrary/QTConnectedClient.h>

#include <QTcpSocket>
#include <QHostAddress>
#include <iostream>

QTConnectedClient::QTConnectedClient(QTcpSocket*& clientSocket) 
	: mClientSocket{ clientSocket }
{

}

uUInt64 QTConnectedClient::getClientId()
{
	return static_cast<uUInt64>(mClientSocket->socketDescriptor());
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
		clientInfo.push_back(PropertyItem{ cParameter_PeerAddress, mClientSocket->peerAddress() });
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
