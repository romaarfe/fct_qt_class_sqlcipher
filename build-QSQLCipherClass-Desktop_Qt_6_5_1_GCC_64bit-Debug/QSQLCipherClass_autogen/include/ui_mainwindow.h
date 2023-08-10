/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

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

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPlainTextEdit *textEdit;
    QPushButton *btnImprimir;
    QPushButton *btnCriarBD;
    QLabel *lblResultado;
    QPushButton *btnTabela;
    QTableView *tbvTabela;
    QPushButton *btnJson;
    QPushButton *btnShowJson;
    QPushButton *btnNovaJanela;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(677, 587);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        textEdit = new QPlainTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        QFont font;
        font.setBold(true);
        textEdit->setFont(font);

        gridLayout->addWidget(textEdit, 7, 2, 1, 1);

        btnImprimir = new QPushButton(centralwidget);
        btnImprimir->setObjectName("btnImprimir");
        btnImprimir->setFont(font);

        gridLayout->addWidget(btnImprimir, 1, 2, 1, 1);

        btnCriarBD = new QPushButton(centralwidget);
        btnCriarBD->setObjectName("btnCriarBD");
        btnCriarBD->setFont(font);

        gridLayout->addWidget(btnCriarBD, 1, 1, 1, 1);

        lblResultado = new QLabel(centralwidget);
        lblResultado->setObjectName("lblResultado");
        lblResultado->setFont(font);

        gridLayout->addWidget(lblResultado, 6, 1, 1, 1);

        btnTabela = new QPushButton(centralwidget);
        btnTabela->setObjectName("btnTabela");
        btnTabela->setFont(font);

        gridLayout->addWidget(btnTabela, 2, 1, 1, 2);

        tbvTabela = new QTableView(centralwidget);
        tbvTabela->setObjectName("tbvTabela");
        tbvTabela->setFont(font);

        gridLayout->addWidget(tbvTabela, 7, 1, 1, 1);

        btnJson = new QPushButton(centralwidget);
        btnJson->setObjectName("btnJson");
        btnJson->setFont(font);

        gridLayout->addWidget(btnJson, 5, 1, 1, 1);

        btnShowJson = new QPushButton(centralwidget);
        btnShowJson->setObjectName("btnShowJson");
        btnShowJson->setFont(font);

        gridLayout->addWidget(btnShowJson, 5, 2, 1, 1);

        btnNovaJanela = new QPushButton(centralwidget);
        btnNovaJanela->setObjectName("btnNovaJanela");
        btnNovaJanela->setFont(font);

        gridLayout->addWidget(btnNovaJanela, 6, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "PRIMEIRA JANELA", nullptr));
        btnImprimir->setText(QCoreApplication::translate("MainWindow", "MOSTRAR NO TERMINAL", nullptr));
        btnCriarBD->setText(QCoreApplication::translate("MainWindow", "CRIAR BASE DE DADOS", nullptr));
        lblResultado->setText(QCoreApplication::translate("MainWindow", "Resultado", nullptr));
        btnTabela->setText(QCoreApplication::translate("MainWindow", "MOSTRAR BASE DE DADOS NA TABELA", nullptr));
        btnJson->setText(QCoreApplication::translate("MainWindow", "CRIAR JSON", nullptr));
        btnShowJson->setText(QCoreApplication::translate("MainWindow", "MOSTRAR JSON", nullptr));
        btnNovaJanela->setText(QCoreApplication::translate("MainWindow", "SEGUNDA JANELA", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
