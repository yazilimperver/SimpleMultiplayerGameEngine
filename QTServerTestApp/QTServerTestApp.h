/**
 * \file    QTServerTestApp.h
 * \date    2019/09/15
 * \author  yazilimperver
 * \brief    Main QT user interface class which contains UI that is created by qt designer
 * Copyright © 2019, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef QTSERVERTESTAPP_H__
#define QTSERVERTESTAPP_H__

#include <QtWidgets/QMainWindow>

#include <QStringListModel>

#include <QSortFilterProxyModel>

#include "ui_QTServerTestApp.h"

#include <NetworkLibrary/QTCPServer.h>

#include <CommonUILibrary/MultiPurposeInputField/MultiPurposeInputField.h>


// Promoted widgets. http://www.informit.com/articles/article.aspx?p=1405227&seqNum=3

class QTServerTestApp
	: public QMainWindow
{
	Q_OBJECT

public:
	QTServerTestApp(QWidget *parent = Q_NULLPTR);

public slots:

	void newClientConnected(uInt64 clientId);
	void clientDisconnected(uInt64 clientId);
	void clientDataReadyToRead(uInt64 clientId);
	void clientErrorOccurred(uInt64 clientId, int errorCode);
	void errorOccurred(int errorCode);

private slots:
	
	/*! @brief Slot that will be called when clear button is clicked */
	void clearClicked();

	/* @brief  Start/stop server listen operation */
	void startStopListenClicked();

	/*! @brief Slot that will be called when save button is clicked */
	void saveClicked();

	/*! @brief Slot that will be called when data representation selection is changed */
	void dataRepresentationChanged(int);
	
	/*! @brief Slot that will be called when message size data is changed */
	void msgSizeChanged(const QString &text);

	/*! @brief Slot that will be called when a client is forcefully disconnected from server */
	void disconnectClientClicked();

	/*! @brief Slot that will be called when a message is send to client */
	void sendMessageClicked();

	/*! @brief Slot that will be called when conversation list filtering selection is updated */
	void filterItemChanged(const QString &text);
private:

	/*!
	 * Remove the client with given label from all lists
	 *
	 * @param	clientLabel	The client label
	 */
	void removeClient(const QString clientLabel);

	/*!
	 * Send currently entered message to given client with respect to selected data representation
	 *
	 * @param	clientId	The text.
	 */
	void sendMessageToClient(uUInt64 clientId);

	/*!
	 * Adds a message to conversation list
	 *
	 * @param	text	The text.
	 */
	void addMessageToConversation(const QString& text);

	/*!
	 * Perform activities with respect changed listening status
	 *
	 * @param	isListening	True if server is listening, false if not.
	 */
	void updateListeningStatus(bool isListening);

	/*! Perform all necessary signal/slot connections */
	void performSignalSlotConnections();

	/*! Connected list of clients with corresponding information
	    <ClientId, IConnectedClient*>
		<ClientId, ClientIdentificationString>
		<ClientIdentificationString, ClientId>	
	*/
	std::unordered_map<uUInt64, IConnectedClient*> mListOfConnectedClients;
	std::unordered_map<uUInt64, QString> mListOfConnectedClientLabels;
	std::unordered_map<std::string, uUInt64> mListOfConnectedClientIds;

	/*! Our client socket which will be used for connection */
	QTCPServer mServerSocket;

	/*! This class represent the user interface designed by qt designer */
	Ui::QTServerTestAppClass mUi;

	/* The string list model that we will hold the conversation items */
	QStringListModel* mConversationModel;
	QSortFilterProxyModel* mFilter;
};


#endif // QTSERVERTESTAPP_H__

/*
  Copyright (c) [2019] [Yazilimperver <yazilimpervergs@gmail.com>]

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/