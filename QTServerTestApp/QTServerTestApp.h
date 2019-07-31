#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QTServerTestApp.h"

class QTServerTestApp : public QMainWindow
{
	Q_OBJECT

public:
	QTServerTestApp(QWidget *parent = Q_NULLPTR);

private:
	Ui::QTServerTestAppClass ui;
};
