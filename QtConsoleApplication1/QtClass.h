#pragma once

#include <QObject>
#include <iostream>
#include <NetworkLibrary/BasicTypes.h>

class QtClass : public QObject
{
	Q_OBJECT

public:
	QtClass(QObject *parent);
	~QtClass();
public slots:
	void connected()
	{
		std::cout << "Connected!" << std::endl;
	}

	void dataArrived(uInt64 id)
	{
		std::cout << "Data received from client with id: " << id << std::endl;
	}
	void disconnected(uInt64 id)
	{
		std::cout << "Client with id: " << id << " is disconnected!" << std::endl;
	}
};
