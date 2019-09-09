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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTClientTestAppClass
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *QTClientTestAppClass)
    {
        if (QTClientTestAppClass->objectName().isEmpty())
            QTClientTestAppClass->setObjectName(QString::fromUtf8("QTClientTestAppClass"));
        QTClientTestAppClass->resize(529, 65);
        centralWidget = new QWidget(QTClientTestAppClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        QTClientTestAppClass->setCentralWidget(centralWidget);

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
