#pragma once

#include <QMainWindow>
#include "ui_QTClientTestApp.h"

class QTClientTestApp : public QMainWindow
{
	Q_OBJECT

public:
	QTClientTestApp(QWidget *parent = Q_NULLPTR);

private:
	Ui::QTClientTestAppClass ui;
};
