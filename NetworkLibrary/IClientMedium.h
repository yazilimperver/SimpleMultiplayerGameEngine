#pragma once

#include <QObject>
#include <BasicTypes.h>
#include <PropertyItem.h>

class CommunicationParameters;

class IClientMedium 
{
public:
	/// <summary>
	/// The name of parameters that can be used for QTCPClient
	/// The host address and port are must
	/// If no local port is provided, the currently available port is used this purpose
	/// This port then can be queried via assigned port
	/// </summary>
	const std::string cParameter_HostAddress{ "HostAddress" };
	const std::string cParameter_HostPort{ "HostPort" };
	const std::string cParameter_LocalAddress{ "LocalAddress" };
	const std::string cParameter_LocalPort{ "LocalPort" };
	const std::string cParameter_AssignedLocalPort{ "LocalPort" };
	const std::string cParameter_PeerPort{ "PeerPort" };
	const std::string cParameter_PeerAddress{ "PeerAddress" };
	const std::string cParameter_PeerName{ "PeerName" };

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

	/// <summary>
	/// Data APIs
	/// </summary>
	virtual uInt64 readData(uInt64 maxByteCount, uByte* data) = 0;
	virtual uInt64 writeData(const uByte* data, uInt64 maxSize) = 0;
	virtual uInt64 writeData(const uChar* data) = 0;

	/// <summary>
	/// Client specific APIs
	/// </summary>
	virtual void connect() = 0;
	virtual void disconnect() = 0;
	virtual bool isConnected() = 0;
	virtual void getPeerInformation(std::vector<PropertyItem>& peerInfo) = 0;

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
	/// <param name="errorCode">The occurred error code</param>
	void errorOccurred(int errorCode);

	/// <summary>
	/// When writing/sending data is completed
	/// </summary>
	/// <param name="dataSize">The size of written data</param>
	void dataWritten(uUInt64 dataSize);

	/// <summary>
	/// There is data that need to be processed
	/// </summary>
	void dataReadyToRead();
};

Q_DECLARE_INTERFACE(IClientMedium, "IClientMedium")
