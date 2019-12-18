#include "NetworkUtility.h"

#include <QNetworkInterface>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>

NetworkUtility::NetworkUtility()
	: mManager{this}
{
	// Cevabimizin gelecegi slotu atayalým
	connect(&mManager, SIGNAL(finished(QNetworkReply*)), SLOT(gotReply(QNetworkReply*)));

	// Umumi IP sorgulama icin http://api.ipify.org i kullanacagiz. Bu servisi JSON formatinda alip isleyecegiz
	mManager.get(QNetworkRequest(QUrl("http://api.ipify.org?format=json")));

	// Cihazlara iliskin mac adreslerini sorgulayalim
	foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
	{
		// Return only the first non-loopback MAC Address
		if (!(netInterface.flags() & QNetworkInterface::IsLoopBack))
		{
			if (netInterface.hardwareAddress() != "")
				mDeviceAddresses.append("<" + netInterface.name() + "> " + netInterface.hardwareAddress());
		}
	}
}

void NetworkUtility::gotReply(QNetworkReply* networkReply)
{
	networkReply->deleteLater();

	if (networkReply->error() != QNetworkReply::NoError)
	{
		// Hatali bir durum olustu. Neymis bakalim
		qDebug() << "Error: " << networkReply->error();
	}
	else
	{
		// JSON formatinda gelen cevabi isleyerek adresi alalim
		mPublicIP = QHostAddress(QJsonDocument::fromJson(networkReply->readAll()).object().value("ip").toString()).toString();
		
		qDebug() << "Public IP: " << mPublicIP;
	}
}

QString NetworkUtility::getPublicIPAddress()
{
	return mPublicIP;
}

QString NetworkUtility::getPrivateIPAddress()
{
	QString result;
	const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);

	for (const QHostAddress &address : QNetworkInterface::allAddresses())
	{
		if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
		{
			mPrivateIP = address.toString();
			result = mPrivateIP;
			break;
		}
	}

	return result;
}

QVector<QString> NetworkUtility::getDeviceList()
{
	return mDeviceAddresses;
}