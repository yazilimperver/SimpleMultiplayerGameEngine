/**
 * \file    QTCPServer.h
 * \date    2019/06/07
 * \author  yazilimperver
 * \brief   
 * Copyright © 2018, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef QTCPSERVER_H__
#define QTCPSERVER_H__

#include <NetworkLibrary/IServerMedium.h>
#include <NetworkLibrary/CommunicationParameters.h>

#include <QTcpServer>
#include <QTcpSocket>

class QTConnectedClient;

class QTCPServer
	: public QObject, public IServerMedium
{
	Q_OBJECT
public:

	/// <summary>
	/// Constructor for TCP server
	/// </summary>
	QTCPServer();

	/// <summary>
	/// Each communication medium configuration parameters should be passed via this API.
	/// The list of parameters are dictated/known by communication medium itself
	/// </summary>
	/// <param name="parameters">The parameter mapping (name/value)</param>
	virtual void assignParameters(const CommunicationParameters& parameters) override;

	/// <summary>
	/// Perform initialization activities required for given medium (bind etc for sockets)
	/// </summary>
	/// <returns>The result of initialization</returns>
	virtual bool initialize() override;

	/// <summary>
	/// Perform destruction and close activities required for given medium
	/// </summary>
	virtual void finalize() override;

	/// <summary>
	/// Is communication medium initialized properly
	/// </summary>
	/// <returns>Initialization status</returns>
	virtual bool isInitialized() override;

	/// <summary>
	/// Server specific APIs
	/// </summary>
	virtual void startListening() override;
	virtual void stopListening() override;
	virtual bool isListening() override;

	/// <summary>
	/// Disconnect given client. The client will also removed from our connected list
	/// </summary>
	/// <param name="clientId">The unique id of client</param>
	virtual void disconnectClient(uUInt64 clientId) override;

	/// <summary>
	/// Check if provided client is connected
	/// </summary>
	/// <param name="clientId">The unique id of client</param>
	/// <returns>Connection status</returns>
	virtual bool isConnected(uUInt64 clientId) override;

	/// <summary>
	/// Obtain corresponding client information
	/// </summary>
	/// <param name="clientId">The unique id of client</param>
	/// <param name="clientInfo">The client information</param>
	virtual void getClientInformation(uUInt64 clientId, std::vector<PropertyItem>& clientInfo) override;

	/// <summary>
	/// Obtain an interface for connected client that identified with given id
	/// </summary>
	/// <param name="clientId">The unique id of client</param>
	/// <returns>The interface for given connected client</returns>
	virtual IConnectedClient* getConnectedClientInterface(uUInt64 clientId) override;

	/// <summary>
	/// Obtain list of connected client unique ids
	/// </summary>
	/// <param name="clientIdList">The list of unique ids</param>
	virtual void getConnectedClientList(std::vector<uUInt64>& clientIdList) override;

private slots:
	/// <summary>
	/// Slots for TCPServer
	/// </summary>
	void newClientConnected();
	void acceptErrorOccurred(QAbstractSocket::SocketError socketError);

	/// <summary>
	/// Slots for connected clients
	/// </summary>
	void clientErrorOccurred(QAbstractSocket::SocketError socketError);

signals:
	/// <summary>
	/// The signal is emitted when a new client is connected
	/// </summary>
	/// <param name="clientId">The unique id of client</param>	
	void newClientConnected(uInt64 clientId);

	/// <summary>
	/// The signal is emitted when a connected client is disconnected
	/// </summary>
	/// <param name="clientId">The unique id of client</param>
	void clientDisconnected(uInt64 clientId);

	/// <summary>
	/// There is data that need to be processed for given client
	/// </summary>
	/// <param name="clientId">The unique id of client</param>
	void clientDataReadyToRead(uInt64 clientId);

	/// <summary>
	/// The signal is emitted when any kind of error is occurred for given client
	/// </summary>
	/// <param name="clientId">The unique id of client</param>
	/// <param name="errorCode">The occurred error code</param>
	void clientErrorOccurred(uInt64 clientId, int errorCode);

	/// <summary>
	/// The signal is emitted when server associated error is occurred
	/// </summary>
	/// <param name="errorCode">The occurred error code</param>
	void errorOccurred(int errorCode);
protected:

	/// <summary>
	/// Initialization status
	/// </summary>
	bool mIsInitialized{ false };

	/// <summary>
	/// The TCP server socket
	/// </summary>
	QTcpServer mTCPServer;

	/// <summary>
	/// The parameters that will be used for socket creation/bind and connection to target host
	/// </summary>
	CommunicationParameters mParameters;

	/// <summary>
	/// The server parameters
	/// </summary>
	int mListeningPort{ 0 };
	std::string mLocalAddress{ "127.0.0.1" };

	/// <summary>
	/// The id that will be used for uniquely identifying clients
	/// </summary>
	uInt64 mClientSeedId{ 0 };

	/// <summary>
	/// Each client is keyed with address of corresponding client as well as unique id
	/// </summary>
	std::unordered_map<QTcpSocket*, uInt64> mClientIdMapping;
	std::unordered_map<uInt64, QTConnectedClient*> mClientMapping;
};

#endif // QTCPSERVER_H__

/*
  Copyright (c) [2018] [Yazilimperver <yazilimpervergs@gmail.com>]
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
