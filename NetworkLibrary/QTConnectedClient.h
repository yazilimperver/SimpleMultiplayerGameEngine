/**
 * \file    QTConnectedClient.h
 * \date    2019/06/07
 * \author  yazilimperver
 * \brief   
 * Copyright © 2019, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef QTCONNECTEDCLIENT_H__
#define QTCONNECTEDCLIENT_H__

#include <IConnectedClient.h>
class QTcpSocket;

class QTConnectedClient
	: public IConnectedClient
{
public:
	/// <summary>
	/// The constructor that takes underlying socket
	/// </summary>
	/// <param name="uniqueId">The unique id that will be used to identify this sockets</param>
	/// <param name="clientSocket">The socket that this interface manage</param>
	QTConnectedClient(uInt64 uniqueId, QTcpSocket*& clientSocket);

	/// <summary>
	/// Returns the underlying socket
	/// </summary>
	/// <returns>Underlying socket</returns>
	QTcpSocket* getUnderlyingSocket();

	/// <summary>
	/// Returns the unique id associated with this client
	/// </summary>
	/// <returns>-1 if no socket associated ow unique id</returns>
	virtual uInt64 getClientId() override;

	/// <summary>
	/// Is this client still connected
	/// </summary>
	/// <returns>The client socket connection status</returns>
	virtual bool isActive() override;

	/// <summary>
	/// Return the information related with this client (address, port, name)
	/// </summary>
	/// <param name="clientInfo">The list of parameters</param>
	virtual void getClientInformation(std::vector<PropertyItem>& clientInfo) override;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="maxByteCount"></param>
	/// <param name="data"></param>
	/// <returns></returns>
	virtual uInt64 readData(uInt64 maxByteCount, uByte* data) override;
	virtual uInt64 writeData(const uByte* data, uInt64 maxSize) override;
	virtual uInt64 writeData(const uChar* data) override;
	virtual void disconnect() override;
protected:
	/// <summary>
	/// The unique identifier
	/// </summary>
	uInt64 mUniqueId{ -1 };

	/// <summary>
	/// Underlying socket
	/// </summary>
	QTcpSocket* mClientSocket{ nullptr };
};

#endif // QTCONNECTEDCLIENT_H__

/*
  Copyright (c) [2019][Yazilimperver <yazilimpervergs@gmail.com>]
  
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
