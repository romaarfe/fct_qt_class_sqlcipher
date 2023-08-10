/********************************************************************************
** Form generated from reading UI file 'secondwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECONDWINDOW_H
#define UI_SECONDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SecondWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *btnCriarBD;
    QPushButton *btnImprimir;
    QPushButton *btnTabela;
    QPushButton *btnJson;
    QPushButton *btnShowJson;
    QLabel *lblResultado;
    QTableView *tbvTabela;
    QPlainTextEdit *textEdit;

    void setupUi(QMainWindow *SecondWindow)
    {
        if (SecondWindow->objectName().isEmpty())
            SecondWindow->setObjectName("SecondWindow");
        SecondWindow->resize(672, 609);
        centralwidget = new QWidget(SecondWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        btnCriarBD = new QPushButton(centralwidget);
        btnCriarBD->setObjectName("btnCriarBD");
        QFont font;
        font.setBold(true);
        btnCriarBD->setFont(font);

        gridLayout->addWidget(btnCriarBD, 0, 0, 1, 1);

        btnImprimir = new QPushButton(centralwidget);
        btnImprimir->setObjectName("btnImprimir");
        btnImprimir->setFont(font);

        gridLayout->addWidget(btnImprimir, 0, 1, 1, 1);

        btnTabela = new QPushButton(centralwidget);
        btnTabela->setObjectName("btnTabela");
        btnTabela->setFont(font);

        gridLayout->addWidget(btnTabela, 1, 0, 1, 2);

        btnJson = new QPushButton(centralwidget);
        btnJson->setObjectName("btnJson");
        btnJson->setFont(font);

        gridLayout->addWidget(btnJson, 2, 0, 1, 1);

        btnShowJson = new QPushButton(centralwidget);
        btnShowJson->setObjectName("btnShowJson");
        btnShowJson->setFont(font);

        gridLayout->addWidget(btnShowJson, 2, 1, 1, 1);

        lblResultado = new QLabel(centralwidget);
        lblResultado->setObjectName("lblResultado");
        lblResultado->setFont(font);

        gridLayout->addWidget(lblResultado, 3, 0, 1, 1);

        tbvTabela = new QTableView(centralwidget);
        tbvTabela->setObjectName("tbvTabela");
        tbvTabela->setFont(font);

        gridLayout->addWidget(tbvTabela, 4, 0, 1, 1);

        textEdit = new QPlainTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setFont(font);

        gridLayout->addWidget(textEdit, 4, 1, 1, 1);

        SecondWindow->setCentralWidget(centralwidget);

        retranslateUi(SecondWindow);

        QMetaObject::connectSlotsByName(SecondWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SecondWindow)
    {
        SecondWindow->setWindowTitle(QCoreApplication::translate("SecondWindow", "SEGUNDA JANELA", nullptr));
        btnCriarBD->setText(QCoreApplication::translate("SecondWindow", "CRIAR BASE DE DADOS", nullptr));
        btnImprimir->setText(QCoreApplication::translate("SecondWindow", "MOSTRAR NO TERMINAL", nullptr));
        btnTabela->setText(QCoreApplication::translate("SecondWindow", "MOSTRAR BASE DE DADOS NA TABELA", nullptr));
        btnJson->setText(QCoreApplication::translate("SecondWindow", "CRIAR JSON", nullptr));
        btnShowJson->setText(QCoreApplication::translate("SecondWindow", "MOSTRAR JSON", nullptr));
        lblResultado->setText(QCoreApplication::translate("SecondWindow", "Resultado", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SecondWindow: public Ui_SecondWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECONDWINDOW_H
