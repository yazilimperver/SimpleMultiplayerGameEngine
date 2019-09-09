/**
 * \file    QTClientTestApp.h
 * \date    2019/08/08
 * \author  yazilimperver
 * \brief   Main QT user interface class which contains manually created UI elements
 * Copyright © 2019, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef QTCLIENTTESTAPP_H__
#define QTCLIENTTESTAPP_H__

#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QGroupBox>
#include <QCheckBox>
#include "ui_QTClientTestApp.h"

#include <CommonUILibrary/MultiPurposeInputField/MultiPurposeInputField.h>
#include <CommonUILibrary/IPComponent/QtIpItem.h>

#include <NetworkLibrary/QTCPClient.h>

/*!
 * TCP Client socket test application which provides capabilities for performing socket applications
 */
class QTClientTestApp
	: public QMainWindow
{
	Q_OBJECT

public:

	/*!
	 * Constructor
	 *
	 * @param [in,out]	parent	(Optional) If non-null, the parent.
	 */
	QTClientTestApp(QWidget *parent = Q_NULLPTR);

public slots:

	/*! Slot that will be called when client is connected */
	void connected();

	/*! Slot that will be called when client is disconnected */
	void disconnected();

	/*! Slot that will be called when new data is arrived */
	void dataReadyToRead();
	
	/*! @brief Slot that will be called when socket error occurred */
	void socketErrorOccurred(int errorCode);

	// UI slots
	/*! @brief Slot that will be called when connect button is clicked */
	void connectClicked();

	/*! @brief Slot that will be called when send button is clicked */
	void sendClicked();

	/*! @brief Slot that will be called when clear button is clicked */
	void clearClicked();

	/*! @brief Slot that will be called when save button is clicked */
	void saveClicked();

	/*! @brief Slot that will be called when data representation selection is changed */
	void dataRepresentationChanged(int);

	/*! @brief Slot that will be called when message size data is changed */
	void msgSizeChanged(const QString &text);
private:

	/*!
	 * Adds a message to conversation list
	 *
	 * @param	text	The text.
	 */
	void addMessageToConversation(const QString& text);

	/*! Generates TCP client application user interface elements manually */
	void generateUI();

	/*! Generates TCP client application conversation panel elements manually */
	void generateConversationPanel();

	/*! Generates TCP client application settings panel elements manually */
	void generateSettingPanels();

	/*! Perform all necessary signal/slot connections */
	void performSignalSlotConnections();

	/*!
	 * Perform activities with respect changed connection status
	 *
	 * @param	isConnected	True if is connected, false if disconnected.
	 */
	void updateConnectionStatus(bool isConnected);

	/*! QT UI class */
	Ui::QTClientTestAppClass ui;

	/*! Our client socket which will be used for connection */
	QTCPClient mClientSocket;

	/*!
	 * We are going to keep UI elements that we are going to use for interaction as class member so
	 * that we can easily modify them.
	 */
	QVBoxLayout mMainClientLayout;
	QtIpItem mServerIP;	
	QLineEdit mServerPort{ "15000" };
	QPushButton mServerConnectBtn{ tr("&CONNECT") };
	QGroupBox mServerConversationGBox{ "Connected To <NONE>" };
	QListWidget mServerConversationList;
	MultiPurposeInputField mServerMsgLineEdit;
	QCheckBox mDataRepresentation{ tr("Use Binary/Hex Data") };
	QCheckBox mNewLineAppend{ tr("Add New Line") };
	QLineEdit mMsgSize{ "16" };
	QPushButton mServerSendBtn{ tr("&SEND") };
	QPushButton mSaveConversationBtn{ tr("S&AVE") };
	QPushButton mClearConversationBtn{ tr("C&LEAR") };
};

#endif // QTCLIENTTESTAPP_H__

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

