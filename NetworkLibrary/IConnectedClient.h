/**
 * \file    IConnectedClient.h
 * \date    2019/06/06
 * \author  yazilimperver
 * \brief   
 * Copyright © 2019, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef ICONNECTEDCLIENT_H__
#define ICONNECTEDCLIENT_H__

#include <NetworkLibrary/BasicTypes.h>

#include <vector>
#include <NetworkLibrary/PropertyItem.h>

/// <summary>
/// This class is responsible for providing information about connected clients to server
/// </summary>
class IConnectedClient
{
public:
	const std::string cParameter_PeerPort{ "PeerPort" };
	const std::string cParameter_PeerAddress{ "PeerAddress" };
	const std::string cParameter_PeerName{ "PeerName" };

		/// <summary>
		/// Close socket connection with given client
		/// </summary>
		virtual void disconnect() = 0;

		/// <summary>
		/// Return the id of this client
		/// </summary>
		/// <returns>Client id</returns>
		virtual uInt64 getClientId() = 0;

		/// <summary>
		/// Is client active
		/// </summary>
		/// <returns></returns>
		virtual bool isActive() = 0;

		/// <summary>
		/// Obtain corresponding client information
		/// </summary>
		/// <param name="clientInfo"></param>
		virtual void getClientInformation(std::vector<PropertyItem>& clientInfo) = 0;

		/// <summary>
		/// Data APIs. Read can be initiated when a data read is ready
		/// </summary>
		virtual uInt64 readData(uInt64 maxByteCount, uByte* data) = 0;
		virtual uInt64 writeData(const uByte* data, uInt64 maxSize) = 0;
		virtual uInt64 writeData(const uChar* data) = 0;
};

#endif // ICONNECTEDCLIENT_H__

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
