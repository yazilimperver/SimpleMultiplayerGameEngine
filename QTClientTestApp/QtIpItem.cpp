#include "QtIpItem.h"
#include <QRegExp>
#include <QRegExpValidator>

QtIpItem::QtIpItem(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
	QRegExp ipRegex("^" + ipRange
		+ "\\." + ipRange
		+ "\\." + ipRange
		+ "\\." + ipRange + "$");
	
	QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
	ui.ipAddress->setText("127.0.0.1");
	ui.ipAddress->setValidator(ipValidator);
	ui.ipAddress->setInputMask("000.000.000.000");

	// Avoid having to move cursor before typing
	ui.ipAddress->setCursorPosition(0);
}

QtIpItem::~QtIpItem()
{
}

QString QtIpItem::ipAddress()
{
	// remove consequtive 0
	return ui.ipAddress->text();
}
