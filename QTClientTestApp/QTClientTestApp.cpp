#include "QTClientTestApp.h"

#include <QPushButton>
#include <QGroupBox>
#include <QFile>
#include <QLabel>
#include <qpixmap>
#include <QDateTime>
#include <QListWidget>
#include <QMessageBox>

QTClientTestApp::QTClientTestApp(QWidget *parent)
	: QMainWindow{ parent }
	, mServerIP{this}
{
	ui.setupUi(this);

	// Set application icon
	this->setWindowIcon(QIcon(":/data/app-ico.ico"));
	this->setWindowTitle("Yazilimperver Socket TCP Client Application");

	// Generate custom UI
	this->generateUI();

	// Perform connections
	this->performSignalSlotConnections();

	// Initial settings
	this->msgSizeChanged(mMsgSize.text());
}

void QTClientTestApp::performSignalSlotConnections()
{
	// UI signal/slots
	connect(&mServerConnectBtn, &QPushButton::clicked, this, &QTClientTestApp::connectClicked);
	connect(&mServerSendBtn, &QPushButton::clicked, this, &QTClientTestApp::sendClicked);
	connect(&mClearConversationBtn, &QPushButton::clicked, this, &QTClientTestApp::clearClicked);
	connect(&mSaveConversationBtn, &QPushButton::clicked, this, &QTClientTestApp::saveClicked);
	connect(&mDataRepresentation, &QCheckBox::stateChanged, this, &QTClientTestApp::dataRepresentationChanged);
	connect(&mMsgSize, &QLineEdit::textChanged, this, &QTClientTestApp::msgSizeChanged);

	// Connection signal/slots
	connect(&mClientSocket, &QTCPClient::connected, this, &QTClientTestApp::connected);
	connect(&mClientSocket, &QTCPClient::disconnected, this, &QTClientTestApp::disconnected);
	connect(&mClientSocket, &QTCPClient::socketErrorOccurred, this, &QTClientTestApp::socketErrorOccurred);
	connect(&mClientSocket, &QTCPClient::dataReadyToRead, this, &QTClientTestApp::dataReadyToRead);
}

void QTClientTestApp::connected()
{
	this->updateConnectionStatus(true);
}

void QTClientTestApp::disconnected()
{
	this->updateConnectionStatus(false);
}

void QTClientTestApp::dataReadyToRead()
{
	// Check currently available data and read it
	// According to display mode add it to conversation list
	qint64 size = mClientSocket.availableDataSize();
	QByteArray rcvdData = mClientSocket.readData(size);

	if (mDataRepresentation.isChecked())
		this->addMessageToConversation("[RCVD] 0x" + QString(rcvdData.toHex(':')));
	else
		this->addMessageToConversation("[RCVD] " + QString(rcvdData));
}

void QTClientTestApp::socketErrorOccurred(int errorCode)
{
	this->addMessageToConversation("[ERROR] Error occurred in client connection. Error code: " + QString::number(errorCode));
}

void QTClientTestApp::connectClicked()
{	
	CommunicationParameters params;

	try
	{
		if (false == mClientSocket.isConnected())
		{
			params.updateParameterValue(mClientSocket.cParameter_HostAddress, mServerIP.ipAddress().toStdString());

			bool isNumberValid{ false };
			int portNo{ mServerPort.text().toInt(&isNumberValid) };

			if (true == isNumberValid)
			{
				params.updateParameterValue(mClientSocket.cParameter_HostPort, portNo);
				mClientSocket.assignParameters(params);

				if (true == mClientSocket.initialize())
				{
					mClientSocket.connect();
				}
				else
				{
					QMessageBox::information(this, "Connection Error", "Server is not available!");
				}
			}
		}
		else
		{
			mClientSocket.disconnect();
		}
	}
	catch (...)
	{
		QMessageBox::critical(this, "Connection Error", "IP Address or port number format is not valid!");
	}
}

void QTClientTestApp::sendClicked()
{
	if (mDataRepresentation.isChecked())
	{
		QByteArray bytes = mServerMsgLineEdit.getBinaryData();
		mClientSocket.writeData(bytes);
		this->addMessageToConversation("[SEND] " + QString(bytes.toHex()));
	}
	else
	{
		std::string textToSend = mServerMsgLineEdit.getText();

		if (mNewLineAppend.isChecked())
			mClientSocket.writeData((textToSend + "\n").c_str());
		else
			mClientSocket.writeData(textToSend.c_str());

		this->addMessageToConversation("[SEND] " + QString(textToSend.c_str()));
	}
}

void QTClientTestApp::clearClicked()
{
	mServerConversationList.clear();
}

void QTClientTestApp::saveClicked()
{
	// Save content to a text file
	QString fileName = QString("Conversation_") + QDateTime::currentDateTime().toString("ddMMyy_HHmm") + QString(".txt");
	QFile file(fileName);

	// Trying to open in WriteOnly and Text mode
	if (!file.open(QFile::WriteOnly |
		QFile::Text))
	{
		qDebug() << " Could not open file for writing";
		return;
	}

	// Text stream can be used to fill given file
	QTextStream out(&file);

	for (int itemIndex{ 0 }; itemIndex < mServerConversationList.count(); itemIndex++)
		out << mServerConversationList.item(itemIndex)->text() << "\n";

	file.flush();
	file.close();	
}

void QTClientTestApp::dataRepresentationChanged(int)
{
	if (mDataRepresentation.isChecked())
	{
		mServerMsgLineEdit.setInputDataType(MultiPurposeInputField::InputDataType::eINPUT_DATA_TYPE_BINARY_HEX);
		mNewLineAppend.setChecked(false);
		mNewLineAppend.setEnabled(false);
	}
	else
	{
		mServerMsgLineEdit.setInputDataType(MultiPurposeInputField::InputDataType::eINPUT_DATA_TYPE_ASCII);
		mNewLineAppend.setEnabled(true);
	}
}

void QTClientTestApp::msgSizeChanged(const QString & text)
{
	// obtain the size of message
	int msgSize = text.toInt();

	if (msgSize == 0)
		msgSize = 32;

	mServerMsgLineEdit.setMaxSize(msgSize);
}

void QTClientTestApp::addMessageToConversation(const QString& text)
{
	mServerConversationList.addItem("> " + text);
	mServerConversationList.scrollToBottom();
}

void QTClientTestApp::generateUI()
{
	// This function will generate upper settings panels
	this->generateSettingPanels();

	// This function will generate conversation panel with associated controls
	this->generateConversationPanel();

	// Assign layout to overall panel
	ui.centralWidget->setLayout(&mMainClientLayout);
}

void QTClientTestApp::generateConversationPanel()
{
	QVBoxLayout* conversationVLayout = new QVBoxLayout;

	// 0) Conversation title
	QLabel* conversationTitle = new QLabel{ tr("Conversation with host: ") };
	conversationTitle->setAlignment(Qt::AlignLeft);
	conversationVLayout->addWidget(conversationTitle);

	// 1) Conversation list
	mServerConversationList.setMinimumHeight(200);
	mServerConversationList.setEditTriggers(QAbstractItemView::NoEditTriggers);
	conversationVLayout->addWidget(&mServerConversationList);

	// 2) Message send group box and conversation control buttons
	// 2-a) Overall horizontal row
	QHBoxLayout* msgConversationLayout = new QHBoxLayout;

	// 2-b) Message send group box
	QGroupBox* msgToSendGroupBox = new QGroupBox{ "Message To Send" };
	QHBoxLayout* msgToSendLayout = new QHBoxLayout;
	QLabel* msgLabel = new QLabel{ tr("Message") };

	mServerMsgLineEdit.setEnabled(false);
	mServerMsgLineEdit.setMinimumWidth(100);

	msgToSendLayout->addWidget(msgLabel);
	msgToSendLayout->addWidget(&mServerMsgLineEdit);
	msgToSendLayout->addWidget(&mServerSendBtn);
	msgToSendGroupBox->setLayout(msgToSendLayout);

	msgConversationLayout->addWidget(msgToSendGroupBox);

	// 2-c) Conversation control buttons
	QVBoxLayout* msgControlLayout = new QVBoxLayout;

	msgControlLayout->addWidget(&mSaveConversationBtn);
	msgControlLayout->addWidget(&mClearConversationBtn);
	msgConversationLayout->addLayout(msgControlLayout);

	conversationVLayout->addLayout(msgConversationLayout);

	// Assign layout to conversation panel
	mServerConversationGBox.setLayout(conversationVLayout);
	mMainClientLayout.addWidget(&mServerConversationGBox);
}

void QTClientTestApp::generateSettingPanels()
{
	QHBoxLayout* settingsPanels = new QHBoxLayout;

	// Server settings panel and corresponding items
	QGroupBox* serverConfigGroupBox = new QGroupBox{ "Server Settings" };
	QGridLayout* serverConfigGridLayout = new QGridLayout;

	// Server IP
	QLabel* ipLabel = new QLabel{ tr("IP Address") };
	serverConfigGridLayout->addWidget(ipLabel, 0, 0);
	serverConfigGridLayout->addWidget(&mServerIP, 0, 1);

	// Server port
	QLabel* portLabel = new QLabel(tr("Port"));
	portLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	serverConfigGridLayout->addWidget(portLabel, 1, 0);

	// Connect button
	QHBoxLayout* portAndConnection = new QHBoxLayout;
	portAndConnection->addWidget(&mServerPort);
	portAndConnection->addWidget(&mServerConnectBtn);
	serverConfigGridLayout->addLayout(portAndConnection, 1, 1);

	serverConfigGroupBox->setLayout(serverConfigGridLayout);

	// Data settings panel and corresponding items
	QGroupBox* dataConfigGroupBox = new QGroupBox{ "Data Configuration" };
	QGridLayout* dataConfigGridLayout = new QGridLayout;

	dataConfigGridLayout->addWidget(&mDataRepresentation, 0, 0);
	dataConfigGridLayout->addWidget(&mNewLineAppend, 0, 1);
	dataConfigGridLayout->addWidget(new QLabel{ tr("Message Size: ") }, 1, 0);
	dataConfigGridLayout->addWidget(&mMsgSize, 1, 1);
	mMsgSize.setInputMask(QString{ "999" });

	dataConfigGroupBox->setLayout(dataConfigGridLayout);

	// Our application logo
	QLabel* logoLabel = new QLabel{};
	QPixmap* logoPix = new QPixmap(":/data/app-logo.png");
	logoLabel->setPixmap(*logoPix);

	settingsPanels->addWidget(serverConfigGroupBox);
	settingsPanels->addWidget(dataConfigGroupBox);
	settingsPanels->addWidget(logoLabel);
	mMainClientLayout.addLayout(settingsPanels);
}

void QTClientTestApp::updateConnectionStatus(bool isConnected)
{
	// Data representation settings
	if (true == isConnected)
	{
		if (true == mDataRepresentation.isChecked())
		{
			mServerMsgLineEdit.setInputDataType(MultiPurposeInputField::InputDataType::eINPUT_DATA_TYPE_BINARY_HEX);

			// In case of non-ascii, no new line will be appended
			mNewLineAppend.setChecked(false);
		}
		else
			mServerMsgLineEdit.setInputDataType(MultiPurposeInputField::InputDataType::eINPUT_DATA_TYPE_ASCII);

		mServerConnectBtn.setText("DISCONNECT");
	}
	else
	{
		mServerConnectBtn.setText("CONNECT");
	}

	// UI enabling/disabling settings
	mServerIP.setEnabled(!isConnected);
	mServerPort.setEnabled(!isConnected);
	mDataRepresentation.setEnabled(!isConnected);
	mMsgSize.setEnabled(!isConnected);

	mServerMsgLineEdit.setEnabled(isConnected);
	mServerSendBtn.setEnabled(isConnected);

	if (true == isConnected)
	{
		this->addMessageToConversation("Connected To Server <" + mServerIP.ipAddress() + ":" + mServerPort.text() + ">");
		this->mServerConversationGBox.setTitle("Connected To <" + mServerIP.ipAddress() + ":" + mServerPort.text() + ">");
	}
	else
	{
		this->addMessageToConversation("Disconnected From Server!");		
		this->mServerConversationGBox.setTitle("Connected To <NONE>");
	}

}
