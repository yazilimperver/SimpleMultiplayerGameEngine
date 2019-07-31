/********************************************************************************
** Form generated from reading UI file 'QTClientTestApp.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCLIENTTESTAPP_H
#define UI_QTCLIENTTESTAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTClientTestAppClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTClientTestAppClass)
    {
        if (QTClientTestAppClass->objectName().isEmpty())
            QTClientTestAppClass->setObjectName(QString::fromUtf8("QTClientTestAppClass"));
        QTClientTestAppClass->resize(600, 400);
        menuBar = new QMenuBar(QTClientTestAppClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QTClientTestAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTClientTestAppClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QTClientTestAppClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QTClientTestAppClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QTClientTestAppClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QTClientTestAppClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QTClientTestAppClass->setStatusBar(statusBar);

        retranslateUi(QTClientTestAppClass);

        QMetaObject::connectSlotsByName(QTClientTestAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTClientTestAppClass)
    {
        QTClientTestAppClass->setWindowTitle(QApplication::translate("QTClientTestAppClass", "QTClientTestApp", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QTClientTestAppClass: public Ui_QTClientTestAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCLIENTTESTAPP_H
