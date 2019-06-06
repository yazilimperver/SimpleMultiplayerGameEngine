/**
 * \file    IClientMedium.h
 * \date    2019/05/31
 * \author  yazilimperver
 * \brief   
 * Copyright © 2018, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef ICLIENTMEDIUM_H__
#define ICLIENTMEDIUM_H__

#include <vector>
#include <PropertyItem.h>
#include <BasicTypes.h>

#include <ICommunicationMedium.h>

class IClientObserver
	: public ICommObserver
{
public:
	virtual void connected() = 0;
	virtual void disconnected() = 0;
	virtual void errorOccurred(int errorCode) = 0;
};

class IClientMedium
{
	Q_OBJECT
public:
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
	/// Is communication medium ready for communication
	/// </summary>
	/// <returns>true => can be used for that purpose, false => not ready </returns>
	virtual bool isActive() = 0;

	virtual uInt64 readData(uInt64 maxByteCount, uByte* data) = 0;
	virtual void   readData(std::vector<uByte>& data) = 0;
	virtual uInt64 writeData(const uByte* data, uInt64 maxSize) = 0;
	virtual uInt64 writeData(const uChar* data) = 0;
	virtual uInt64 writeData(const std::vector<uByte>& data) = 0;

	/// <summary>
	/// Client specific APIs
	/// </summary>
	virtual void connect() = 0;
	virtual void disconnect() = 0;	
	virtual bool isConnected() = 0;
	virtual void getPeerInformation(std::vector<PropertyItem>& peerInfo) = 0;
};

#endif // ICLIENTCOMMUNICATIONMEDIUM_H__

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
