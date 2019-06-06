/**
 * \file    QTCPClient.h
 * \date    2019/06/05
 * \author  yazilimperver
 * \brief   
 * Copyright © 2018, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef QTCPCLIENT_H__
#define QTCPCLIENT_H__

#include <IClientMedium.h>
#include <CommunicationParameters.h>

#include <qtcpsocket.h>

class QTCPClient
	: public QObject, public IClientMedium
{
	Q_OBJECT
	Q_INTERFACES(IClientMedium)
public:

	/// <summary>
	/// Constructor for TCP client
	/// </summary>
	QTCPClient();

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
	/// Is communication medium ready for communication
	/// </summary>
	/// <returns>true => can be used for that purpose, false => not ready </returns>
	virtual bool isActive() override;

	/// <summary>
	/// Data APIs
	/// </summary>
	virtual uInt64 readData(uInt64 maxByteCount, uByte* data) override;
	virtual uInt64 writeData(const uByte* data, uInt64 maxSize) override;
	virtual uInt64 writeData(const uChar* data) override;

	/// <summary>
	/// To connect given destination with respect to provided parameters
	/// The medium should be initialized beforehand
	/// </summary>
	virtual void connect() override;

	/// <summary>
	/// Disconnect from destination
	/// </summary>
	virtual void disconnect() override;

	/// <summary>
	/// Is medium connected
	/// </summary>
	/// <returns>Connection status</returns>
	virtual bool isConnected() override;

	/// <summary>
	/// Returns the information about other end point
	/// </summary>
	/// <param name="peerInfo">End point information</param>
	virtual void getPeerInformation(std::vector<PropertyItem>& peerInfo) override;

signals:
	/// <summary>
	/// The signal is emitted when current client is connected
	/// </summary>
	void connected();

	/// <summary>
	/// The signal is emitted when current client is disconnected
	/// </summary>
	void disconnected();

	/// <summary>
	/// The signal is emitted when any kind of error is occurred
	/// </summary>
	/// <param name="errorCode">The occurred error</param>
	void errorOccurred(int errorCode);

	/// <summary>
	/// There is data that need to be processed
	/// </summary>
	void dataReadyToRead();

private slots:
	void clientConnected();
	void clientDisconnected();
	void dataArrived();
	void errorOccurred(QAbstractSocket::SocketError socketError);
protected:

	/// <summary>
	/// Initialization status
	/// </summary>
	bool mIsInitialized{ false };

	/// <summary>
	/// Underlying TCP client socket
	/// </summary>
	QTcpSocket mTcpSocket;

	/// <summary>
	/// The parameters that will be used for socket creation/bind and connection to target host
	/// </summary>
	CommunicationParameters mParameters;
};

#endif // QTCPCLIENT_H__

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
