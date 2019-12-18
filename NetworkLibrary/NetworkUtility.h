#pragma once

#include <QObject>
#include <QString>
#include <QVector>

#include <QNetworkAccessManager>

class NetworkUtility
	: public QObject
{
	Q_OBJECT
public:
	NetworkUtility();

	// Ilgili bilgileri donecek API'lerimiz
	QString getPublicIPAddress();
	QString getPrivateIPAddress();
	QVector<QString> getDeviceList();

private slots:
	// Umumi adresimize iliskin almis oldugumuz cevap
	void gotReply(QNetworkReply* networkReply);

private:
	// Umumi IP adresimiz
	QString mPublicIP;

	// Ozel IP adresimiz
	QString mPrivateIP;

	// Kullanilabilir cihazlarin mac adreslerinin listesi
	QVector<QString> mDeviceAddresses;

	// Umumi IP'yi ogrenmek icin kullacagimiz servis iletisimine dair araci sinifimiz
	QNetworkAccessManager mManager;
};