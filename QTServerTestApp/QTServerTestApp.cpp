#include "QTServerTestApp.h"

#include <QFile>
#include <QDateTime>
#include <QMessageBox>
#include <QHostAddress>
#include <NetworkLibrary/IConnectedClient.h>

QTServerTestApp::QTServerTestApp(QWidget *parent)
	: QMainWindow(parent)
{
	mUi.setupUi(this);

	/* This settings is for making list widget non-editable */
	mUi.conversationList->setEditTriggers(QAbstractItemView::NoEditTriggers);

	this->performSignalSlotConnections();

	/* Prepare model and corresponding filter proxy */
	mConversationModel = new QStringListModel(this);
	mFilter = new QSortFilterProxyModel();
	mFilter->setSourceModel(mConversationModel);
	mUi.conversationList->setModel(mFilter);

	/* Initial settings */
	this->msgSizeChanged(mUi.msgSizeLineEdit->text());
}

void QTServerTestApp::newClientConnected(uInt64 clientId)
{
	/* A new client with given id is connected. We should obtain corresponding connected client info */
	std::vector<PropertyItem> clientInfo;

	mServerSocket.getClientInformation(clientId, clientInfo);

	QString clientLabel = std::any_cast<QString>(clientInfo[1].mValue) + ":"
		+ QString::number(std::any_cast<quint16>(clientInfo[2].mValue));

	mListOfConnectedClients[clientId] = mServerSocket.getConnectedClientInterface(clientId);
	mListOfConnectedClientLabels[clientId] = clientLabel;
	mListOfConnectedClientIds[clientLabel.toStdString()] = clientId;
	
	mUi.connectedClientsComboBox->addItem(clientLabel);
	mUi.messageFilterComboBox->addItem(clientLabel);

	this->addMessageToConversation("[" + clientLabel + "] Client is connected!");
}

void QTServerTestApp::clientDisconnected(uInt64 clientId)
{
	this->addMessageToConversation("[" + mListOfConnectedClientLabels[clientId] + "] Client is disconnected!");

	this->removeClient(mListOfConnectedClientLabels[clientId]);
}

void QTServerTestApp::removeClient(const QString clientLabel)
{
	auto clientLabelStr = clientLabel.toStdString();
	uUInt64 clientId = mListOfConnectedClientIds[clientLabelStr];

	mUi.connectedClientsComboBox->removeItem(mUi.connectedClientsComboBox->findText(clientLabel));
	mUi.messageFilterComboBox->removeItem(mUi.messageFilterComboBox->findText(clientLabel));

	mListOfConnectedClients.erase(clientId);
	mListOfConnectedClientLabels.erase(clientId);
	mListOfConnectedClientIds.erase(clientLabelStr);
}

void QTServerTestApp::sendMessageToClient(uUInt64 clientId)
{
	auto clientLabel = mListOfConnectedClientLabels[clientId];
	auto clientInterface = mListOfConnectedClients[clientId];

	if (mUi.binaryHexCheckBox->isChecked())
	{
		QByteArray bytes = mUi.msgToSendLineEdit->getBinaryData();
		clientInterface->writeData(bytes);
		this->addMessageToConversation("[" + clientLabel + "] " + QString(bytes.toHex()));
	}
	else
	{
		std::string textToSend = mUi.msgToSendLineEdit->getText();

		if (mUi.addNewLineCheckBox->isChecked())
			clientInterface->writeData((textToSend + "\n").c_str());
		else
			clientInterface->writeData(textToSend.c_str());

		this->addMessageToConversation("[" + clientLabel + "] " + QString(textToSend.c_str()));
	}
}

void QTServerTestApp::disconnectClientClicked()
{
	if (mUi.connectedClientsComboBox->currentIndex() >= 0)
	{
		auto clientId = mListOfConnectedClientIds[mUi.connectedClientsComboBox->currentText().toStdString()];
		auto clientLabel = mListOfConnectedClientLabels[clientId];

		// Disconnect given client
		mServerSocket.disconnectClient(clientId);

		this->addMessageToConversation("[" + clientLabel + "] Client is disconnected!");

		this->removeClient(clientLabel);
	}
}

void QTServerTestApp::sendMessageClicked()
{
	if (mUi.connectedClientsComboBox->currentIndex() >= 0)
	{
		// Send message to all connected clients
		if (mUi.connectedClientsComboBox->currentIndex() == 0)
		{
			for (auto&[clientId, clientLabel] : mListOfConnectedClientLabels)
				sendMessageToClient(clientId);
		}
		// Send message to corresponding client
		else
		{
			auto clientId = mListOfConnectedClientIds[mUi.connectedClientsComboBox->currentText().toStdString()];
			sendMessageToClient(clientId);
		}
	}

	mUi.msgToSendLineEdit->setText("");
}

void QTServerTestApp::filterItemChanged(const QString &text)
{
	if (text == "ALL")
	{
		mFilter->setFilterFixedString("");
	}
	else
	{
		mFilter->setFilterFixedString(text);
	}
}

void QTServerTestApp::clientDataReadyToRead(uInt64 clientId)
{
	// Read corresponding data from client interface
	if (auto itr = mListOfConnectedClients.find(clientId); itr != mListOfConnectedClients.end())
	{
		qint64 size = itr->second->availableDataSize();
		QByteArray rcvdData = itr->second->readData(size);

		if (mUi.binaryHexCheckBox->isChecked())
			this->addMessageToConversation("[" + mListOfConnectedClientLabels[clientId] +"] 0x" + QString(rcvdData.toHex(':')));
		else
			this->addMessageToConversation("[" + mListOfConnectedClientLabels[clientId] + "] " + QString(rcvdData));
	}
}

void QTServerTestApp::clientErrorOccurred(uInt64 clientId, int errorCode)
{
	this->addMessageToConversation("[" + mListOfConnectedClientLabels[clientId] + "]  Error occurred in client connection. Error code: " + QString::number(errorCode));
}

void QTServerTestApp::errorOccurred(int errorCode)
{
	this->addMessageToConversation("[Server] Error occurred in server socket. Error code: " + QString::number(errorCode));
}

void QTServerTestApp::clearClicked()
{
	mConversationModel->removeRows(0, mConversationModel->rowCount());
	mFilter->setFilterFixedString("");
}

const std::string cIServerMedium_Parameter_LocalAddress{ "LocalAddress" };
const std::string cIServerMedium_Parameter_LocalPort{ "LocalPort" };
const std::string cIServerMedium_Parameter_MaxPendingConnections{ "MaxPendingConnections" };

void QTServerTestApp::startStopListenClicked()
{
	CommunicationParameters params;

	try
	{
		if (false == mServerSocket.isListening())
		{
			/* We are currently allowing at most 20 clients */
			params.updateParameterValue(mServerSocket.cIServerMedium_Parameter_MaxPendingConnections, 20);

			/* Get port number from UI */
			bool isOk{ false };
			int portNo{ 0 };

			portNo = mUi.portToListenLineEdit->text().toInt(&isOk);

			if (true == isOk)
			{
				params.updateParameterValue(mServerSocket.cIServerMedium_Parameter_LocalPort, portNo);
				mServerSocket.assignParameters(params);
				
				if (true == mServerSocket.initialize())
				{
					mServerSocket.startListening();

					this->updateListeningStatus(true);
				}
				else
				{
					QMessageBox::information(this, "Connection Error", "Server could not started!");
				}
			}
		}
		else
		{
			mServerSocket.stopListening();

			this->updateListeningStatus(false);
		}
	}
	catch (...)
	{
		QMessageBox::critical(this, "Connection Error", "IP Address or port number format is not valid!");
	}
}

void QTServerTestApp::saveClicked()
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
	auto conversationList = mConversationModel->stringList();

	for (int itemIndex{ 0 }; itemIndex < conversationList.count(); itemIndex++)
		out << conversationList[itemIndex] << "\n";

	file.flush();
	file.close();
}

void QTServerTestApp::dataRepresentationChanged(int)
{
	if (mUi.binaryHexCheckBox->isChecked())
	{
		mUi.msgToSendLineEdit->setInputDataType(MultiPurposeInputField::InputDataType::eINPUT_DATA_TYPE_BINARY_HEX);
		mUi.addNewLineCheckBox->setChecked(false);
		mUi.addNewLineCheckBox->setEnabled(false);
	}
	else
	{
		mUi.msgToSendLineEdit->setInputDataType(MultiPurposeInputField::InputDataType::eINPUT_DATA_TYPE_ASCII);
		mUi.addNewLineCheckBox->setEnabled(true);
	}
}

void QTServerTestApp::msgSizeChanged(const QString & text)
{
	// obtain the size of message
	int msgSize = text.toInt();

	if (msgSize == 0)
		msgSize = 32;

	mUi.msgToSendLineEdit->setMaxSize(msgSize);
}

void QTServerTestApp::addMessageToConversation(const QString & text)
{
	if (mConversationModel->insertRow(mConversationModel->rowCount())) 
	{
		QModelIndex index = mConversationModel->index(mConversationModel->rowCount() - 1, 0);
		mConversationModel->setData(index, "> " + text);
	}

	mUi.conversationList->scrollToBottom();
}

void QTServerTestApp::updateListeningStatus(bool isListening)
{
	// Data representation settings
	if (true == isListening)
	{
		if (true == mUi.binaryHexCheckBox->isChecked())
		{
			mUi.msgToSendLineEdit->setInputDataType(MultiPurposeInputField::InputDataType::eINPUT_DATA_TYPE_BINARY_HEX);

			// In case of non-ascii, no new line will be appended
			mUi.addNewLineCheckBox->setChecked(false);
		}
		else
			mUi.msgToSendLineEdit->setInputDataType(MultiPurposeInputField::InputDataType::eINPUT_DATA_TYPE_ASCII);

		mUi.listenButton->setText("STOP &LISTENING");
	}
	else
	{
		mUi.listenButton->setText("START &LISTENING");
	}

	// UI enabling/disabling settings
	mUi.portToListenLineEdit->setEnabled(!isListening);
	mUi.binaryHexCheckBox->setEnabled(!isListening);
	mUi.msgSizeLineEdit->setEnabled(!isListening);
	
	mUi.messageFilterComboBox->setEnabled(isListening);
	mUi.connectedClientsComboBox->setEnabled(isListening);
	mUi.disconnectButton->setEnabled(isListening);
	mUi.msgToSendLineEdit->setEnabled(isListening);
	mUi.sendButton->setEnabled(isListening);

	if (true == isListening)
	{
		this->addMessageToConversation("[Server] Server Started!");
	}
	else
	{
		this->addMessageToConversation("[Server] Server Stopper!");
	}
}

void QTServerTestApp::performSignalSlotConnections()
{
	// UI signal/slots
	connect(mUi.clearHistoryButton, &QPushButton::clicked, this, &QTServerTestApp::clearClicked);
	connect(mUi.saveHistoryButton, &QPushButton::clicked, this, &QTServerTestApp::saveClicked);
	connect(mUi.binaryHexCheckBox, &QCheckBox::stateChanged, this, &QTServerTestApp::dataRepresentationChanged);
	connect(mUi.msgSizeLineEdit, &QLineEdit::textChanged, this, &QTServerTestApp::msgSizeChanged);
	connect(mUi.messageFilterComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(filterItemChanged(const QString &)));

	connect(mUi.listenButton, &QPushButton::clicked, this, &QTServerTestApp::startStopListenClicked);
	connect(mUi.disconnectButton, &QPushButton::clicked, this, &QTServerTestApp::disconnectClientClicked);
	connect(mUi.sendButton, &QPushButton::clicked, this, &QTServerTestApp::sendMessageClicked);

	// Connection signal/slots
	// Note that this is a special signal slot connection which requires casting for overloaded signals
	connect(&mServerSocket, static_cast<void(QTCPServer::*)(uInt64)>(&QTCPServer::newClientConnected), this,  &QTServerTestApp::newClientConnected);
	connect(&mServerSocket, &QTCPServer::clientDisconnected, this, &QTServerTestApp::clientDisconnected);
	connect(&mServerSocket, &QTCPServer::clientDataReadyToRead, this, &QTServerTestApp::clientDataReadyToRead);
	
	// Note that this is a special signal slot connection which requires casting for overloaded signals
	connect(&mServerSocket, static_cast<void(QTCPServer::*)(uInt64, int)>(&QTCPServer::clientErrorOccurred), this, &QTServerTestApp::clientErrorOccurred);
	connect(&mServerSocket, &QTCPServer::errorOccurred, this, &QTServerTestApp::errorOccurred);
}
