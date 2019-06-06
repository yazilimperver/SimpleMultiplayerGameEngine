#pragma once

#include <QObject>
#include <iostream>

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
};
