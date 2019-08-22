/**
 * \file    IClientMedium.h
 * \date    2019/06/08
 * \author  yazilimperver
 * \brief   
 * Copyright © 2019, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef ICLIENTMEDIUM_H__
#define ICLIENTMEDIUM_H__


#include <QObject>
#include "BasicTypes.h"
#include "PropertyItem.h"

/*! @brief	A communication parameters. */
class CommunicationParameters;

/*! @brief	A client medium base class. 
		    The name of parameters that can be used for client mediums 
			The host address and port are must 
			If no local port is provided, the currently available port is used this
			purpose. This port then can be queried via assigned port */
class IClientMedium
{
public:
	/*!
	 /*! @brief	The parameter host address */
	const std::string cParameter_HostAddress{ "HostAddress" };
	/*! @brief	The parameter host port */
	const std::string cParameter_HostPort{ "HostPort" };
	/*! @brief	The parameter local address */
	const std::string cParameter_LocalAddress{ "LocalAddress" };
	/*! @brief	The parameter local port */
	const std::string cParameter_LocalPort{ "LocalPort" };
	/*! @brief	The parameter assigned local port */
	const std::string cParameter_AssignedLocalPort{ "LocalPort" };
	/*! @brief	The parameter peer port */
	const std::string cParameter_PeerPort{ "PeerPort" };
	/*! @brief	The parameter peer address */
	const std::string cParameter_PeerAddress{ "PeerAddress" };
	/*! @brief	Name of the parameter peer */
	const std::string cParameter_PeerName{ "PeerName" };

	/*!
	 * @brief	Each communication medium configuration parameters should be passed via this API. The
	 * 			list of parameters are dictated/known by communication medium itself
	 *
	 * @param	parameters	The parameter mapping (name/value)
	 */
	virtual void assignParameters(const CommunicationParameters& parameters) = 0;

	/*!
	 * @brief	Perform initialization activities required for given medium (bind etc for sockets)
	 *
	 * @returns	The result of initialization.
	 */
	virtual bool initialize() = 0;

	/*! @brief	Perform destruction and close activities required for given medium */
	virtual void finalize() = 0;

	/*!
	 * @brief	Is communication medium initialized properly
	 *
	 * @returns	Initialization status.
	 */
	virtual bool isInitialized() = 0;

	/*!
	 * @brief	Is communication medium ready for communication
	 *
	 * @returns	true => can be used for that purpose, false => not ready.
	 */
	virtual bool isActive() = 0;

	/*!
	 * @brief	Data APIs
	 *
	 * @returns	An uInt64.
	 */
	virtual uInt64 availableDataSize() = 0;
	/*!
	 * @brief	Reads a data
	 *
	 * @param 		  	maxByteCount	Number of maximum bytes.
	 * @param [in,out]	data			If non-null, the data.
	 *
	 * @returns	The data.
	 */
	virtual uInt64 readData(uInt64 maxByteCount, uByte* data) = 0;
	/*!
	 * @brief	Reads a data
	 *
	 * @param	maxByteCount	Number of maximum bytes.
	 *
	 * @returns	The data.
	 */
	virtual QByteArray readData(uInt64 maxByteCount) = 0;
	/*!
	 * @brief	Writes a data
	 *
	 * @param	data   	The data.
	 * @param	maxSize	The maximum size of the.
	 *
	 * @returns	An uInt64.
	 */
	virtual uInt64 writeData(const uByte* data, uInt64 maxSize) = 0;
	/*!
	 * @brief	Writes a data
	 *
	 * @param	data	The data.
	 *
	 * @returns	An uInt64.
	 */
	virtual uInt64 writeData(const QByteArray& data) = 0;
	/*!
	 * @brief	Writes a data
	 *
	 * @param	data	The data.
	 *
	 * @returns	An uInt64.
	 */
	virtual uInt64 writeData(const uChar* data) = 0;

	/*! @brief	Client specific APIs */
	virtual void connect() = 0;
	/*! @brief	Disconnects this object */
	virtual void disconnect() = 0;
	/*!
	 * @brief	Query if this object is connected
	 *
	 * @returns	True if connected, false if not.
	 */
	virtual bool isConnected() = 0;
	/*!
	 * @brief	Gets peer information
	 *
	 * @param [in,out]	peerInfo	Information describing the peer.
	 */
	virtual void getPeerInformation(std::vector<PropertyItem>& peerInfo) = 0;

/*! @brief	Connected this object */
signals:
	/*! @brief	The signal is emitted when current client is connected */
	void connected();

	/*! @brief	The signal is emitted when current client is disconnected */
	void disconnected();

	/*!
	 * @brief	The signal is emitted when any kind of error is occurred
	 *
	 * @param	errorCode	The occurred error code.
	 */
	void errorOccurred(int errorCode);

	/*!
	 * @brief	When writing/sending data is completed
	 *
	 * @param	dataSize	The size of written data.
	 */
	void dataWritten(uUInt64 dataSize);

	/*! @brief	There is data that need to be processed */
	void dataReadyToRead();
};


#endif // ICLIENTMEDIUM_H__

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