#include <QTCPClient.h>
#include <QTcpSocket>
#include <QHostAddress>
#include <iostream>

QTCPClient::QTCPClient()
	: mTcpSocket{this}
{
	QObject::connect(&mTcpSocket, &QTcpSocket::connected, this, &QTCPClient::clientConnected);
	QObject::connect(&mTcpSocket, &QTcpSocket::disconnected, this, &QTCPClient::clientDisconnected);
	QObject::connect(&mTcpSocket, &QIODevice::readyRead, this, &QTCPClient::dataArrived);

	QObject::connect(&mTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorOccurred(QAbstractSocket::SocketError)));
}

void QTCPClient::assignParameters(const CommunicationParameters& parameters)
{
	mParameters = parameters;
}

bool QTCPClient::initialize()
{
	mIsInitialized = false;

	// 0) Check the list of parameters to see if required parameters are provided
	if (true == mParameters.hasParameter(cParameter_HostAddress) && 
		true == mParameters.hasParameter(cParameter_HostPort))
	{
		mIsInitialized = true;

		// If so check if we required to bind given port and address
		std::string localHost{ "127.0.0.1" };
		int portNo{ -1 };

		bool hasLocalPort = mParameters.hasParameter(cParameter_LocalPort);
		bool hasLocalAddress = mParameters.hasParameter(cParameter_LocalAddress);

		if (false == hasLocalAddress && true == hasLocalPort)
		{
			mParameters.getParameterValue<int>(cParameter_LocalPort, portNo);
			mIsInitialized = mTcpSocket.bind(portNo);
		}
		else if (true == hasLocalAddress && true == hasLocalPort)
		{
			mParameters.getParameterValue<int>(cParameter_LocalPort, portNo);
			mParameters.getParameterValue<std::string>(cParameter_LocalAddress, localHost);
			mIsInitialized = mTcpSocket.bind(QHostAddress(localHost.c_str()), portNo);
		}
		else
		{
			// Random port is used
			mIsInitialized = mTcpSocket.bind();

			// Store local port
			mParameters.updateParameterValue(cParameter_LocalPort, static_cast<int>(mTcpSocket.localPort()));
		}
	}	

	return mIsInitialized;
}

void QTCPClient::finalize()
{
	// Close socket if not already
	if (true == this->isConnected())
		mTcpSocket.disconnectFromHost();
}

bool QTCPClient::isInitialized()
{
	return mIsInitialized;
}

bool QTCPClient::isActive()
{
	return this->isConnected();
}

uInt64 QTCPClient::readData(uInt64 maxByteCount, uByte* data)
{
	if (nullptr != data)
		return mTcpSocket.read(reinterpret_cast<char*>(data), maxByteCount);
	else
		return -1;
}

QByteArray QTCPClient::readData(uInt64 maxByteCount)
{
	return mTcpSocket.read(maxByteCount);
}

uInt64 QTCPClient::writeData(const uByte* data, uInt64 maxSize)
{
	if (nullptr != data)
		return mTcpSocket.write(reinterpret_cast<const char*>(data), maxSize);
	else
		return -1;
}

uInt64 QTCPClient::writeData(const uChar* data)
{
	if (nullptr != data)
		return mTcpSocket.write(reinterpret_cast<const char*>(data));
	else
		return -1;
}

uInt64 QTCPClient::writeData(const QByteArray& data)
{
	return mTcpSocket.write(data);
}

void QTCPClient::connect()
{
	if (true == this->isConnected())
		mTcpSocket.disconnectFromHost();

	int destPort { 0 };
	std::string destAddr;

	if (true == mParameters.getParameterValue<int>(cParameter_HostPort, destPort)
		&&
		true == mParameters.getParameterValue<std::string>(cParameter_HostAddress, destAddr))
		mTcpSocket.connectToHost(destAddr.c_str(), destPort);
}

void QTCPClient::disconnect()
{
	if (true == this->isConnected())
	{
		mTcpSocket.close();
	}
}

bool QTCPClient::isConnected()
{
	return mTcpSocket.state() == QTcpSocket::ConnectedState;
}

void QTCPClient::getPeerInformation(std::vector<PropertyItem>& peerInfo)
{
	if (true == this->isConnected())
	{
		peerInfo.clear();

		// fill peer data
		peerInfo.push_back(PropertyItem{ IClientMedium::cParameter_PeerName, mTcpSocket.peerName() });
		peerInfo.push_back(PropertyItem{ IClientMedium::cParameter_PeerAddress, mTcpSocket.peerAddress() });
		peerInfo.push_back(PropertyItem{ IClientMedium::cParameter_PeerPort, mTcpSocket.peerPort() });
	}
}

uInt64 QTCPClient::availableDataSize()
{
	return mTcpSocket.bytesAvailable();
}

void QTCPClient::clientConnected()
{
	std::cout << "[QTCPClient] Client is connected!" << '\n';

	emit connected();
}

void QTCPClient::clientDisconnected()
{
	std::cout << "[QTCPClient] Client is disconnected!" << '\n';

	emit disconnected();
}

void QTCPClient::dataArrived()
{
	std::cout << "[QTCPClient] Data ready for read!" << '\n';

	emit dataReadyToRead();
}

void QTCPClient::errorOccurred(QAbstractSocket::SocketError socketError)
{
	switch (socketError) 
	{
	case QAbstractSocket::RemoteHostClosedError:
		std::cout << "[QTCPClient] Error: Remote host is closed!" << '\n';
		break;
	case QAbstractSocket::HostNotFoundError:
		std::cout << "[QTCPClient] Error: The host was not found.Please check the host name and port settings." << '\n';
		break;
	case QAbstractSocket::ConnectionRefusedError:

		std::cout << "[QTCPClient] Error: The connection was refused by the peer. Make sure the server is running, and check that the host name and port settings are correct." << '\n';
		break;
	default:
		std::cout << "[QTCPClient] Error: " << mTcpSocket.errorString().data() << '\n';
	}
	
	emit socketErrorOccurred(static_cast<int>(socketError));
}
