/**
 * \file    IServerMedium.h
 * \date    2019/06/06
 * \author  yazilimperver
 * \brief   
 * Copyright © 2019, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef ISERVERMEDIUM_H__
#define ISERVERMEDIUM_H__

#include <QObject>
#include <NetworkLibrary/BasicTypes.h>
#include <NetworkLibrary/PropertyItem.h>
#include <string>
class IConnectedClient;
class CommunicationParameters;


class IServerMedium
{
public:

	/// <summary>
	/// The name of parameters that can be used for server mediums
	/// The host address and port are must
	/// If no local port is provided, the currently available port is used this purpose
	/// This port then can be queried via assigned port
	/// </summary>
	const std::string cIServerMedium_Parameter_LocalAddress{ "LocalAddress" };
	const std::string cIServerMedium_Parameter_LocalPort{ "LocalPort" };
	const std::string cIServerMedium_Parameter_MaxPendingConnections{ "MaxPendingConnections" };

	/// <summary>
	/// Each communication medium configuration parameters should be passed via this API.
	/// The list of parameters are dictated/known by communication medium itself
	/// </summary>
	/// <param name="parameters">The parameter mapping (name/value)</param>
	virtual void assignParameters(const CommunicationParameters& parameters) = 0;

	/// <summary>
	/// Perform initialization activities required for given medium (bind etc for sockets)
	/// </summary>
	/// <returns>The result of initialization</returns>
	virtual bool initialize() = 0;

	/// <summary>
	/// Perform destruction and close activities required for given medium
	/// </summary>
	virtual void finalize() = 0;

	/// <summary>
	/// Is communication medium initialized properly
	/// </summary>
	/// <returns>Initialization status</returns>
	virtual bool isInitialized() = 0;

	/// <summary>
	/// Server specific APIs
	/// </summary>
	virtual void startListening() = 0;
	virtual void stopListening() = 0;
	/// <summary>
	/// Is communication medium listening given the port
	/// </summary>
	/// <returns>true => can be used for that purpose, false => not ready </returns>
	virtual bool isListening() = 0;
	
	/// <summary>
	/// Disconnect given client. The client will also removed from our connected list
	/// </summary>
	/// <param name="clientId">The unique id of client</param>
	virtual void disconnectClient(uUInt64 clientId) = 0;

	/// <summary>
	/// Check if provided client is connected
	/// </summary>
	/// <param name="clientId">The unique id of client</param>
	/// <returns>Connection status</returns>
	virtual bool isConnected(uUInt64 clientId) = 0;

	/// <summary>
	/// Obtain corresponding client information
	/// </summary>
	/// <param name="clientId">The unique id of client</param>
	/// <param name="clientInfo">The client information</param>
	virtual void getClientInformation(uUInt64 clientId, std::vector<PropertyItem>& clientInfo) = 0;

	/// <summary>
	/// Obtain an interface for connected client that identified with given id
	/// </summary>
	/// <param name="clientId">The unique id of client</param>
	/// <returns>The interface for given connected client</returns>
	virtual IConnectedClient* getConnectedClientInterface(uUInt64 clientId) = 0;

	/// <summary>
	/// Obtain list of connected client unique ids
	/// </summary>
	/// <param name="clientIdList">The list of unique ids</param>
	virtual void getConnectedClientList(std::vector<uUInt64>& clientIdList) = 0;
signals:
	/// <summary>
	/// The signal is emitted when a new client is connected
	/// </summary>
	/// <param name="clientId">The unique id of client</param>	
	void newClientConnected(uUInt64 clientId);

	/// <summary>
	/// The signal is emitted when a connected client is disconnected
	/// </summary>
	/// <param name="clientId">The unique id of client</param>
	void clientDisconnected(uUInt64 clientId);

	/// <summary>
	/// When writing/sending data is completed
	/// </summary>
	/// <param name="clientId">The unique id of client</param>
	void clientDataWritten(uUInt64 clientId);

	/// <summary>
	/// There is data that need to be processed for given client
	/// </summary>
	/// <param name="clientId">The unique id of client</param>
	void clientDataReadyToRead(uUInt64 clientId);

	/// <summary>
	/// The signal is emitted when any kind of error is occurred for given client
	/// </summary>
	/// <param name="clientId">The unique id of client</param>
	/// <param name="errorCode">The occurred error code</param>
	void clientErrorOccurred(uUInt64 clientId, int errorCode);
	
	/// <summary>
	/// The signal is emitted when server associated error is occurred
	/// </summary>
	/// <param name="errorCode">The occurred error code</param>
	void errorOccurred(int errorCode);
};


#endif // ISERVERMEDIUM_H__

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
