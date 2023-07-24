#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Inclui as bibliotecas necessárias para o funcionamento da classe
#define SQLITE_HAS_CODEC

#include "qsqlcipherclass.h"
#include "qsqliteclass.h"
#include "qsqlitebaseclass.h"
#include "secondwindow.h"
#include <iostream>
#include <sqlcipher/sqlite3.h>
#include <QDebug>
#include <QApplication>
#include <QMainWindow>
#include <QList>
#include <QVariant>
#include <QFile>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextEdit>
#include <exception>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Construtor e Destrutor da classe MainWindow
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slots para responder a eventos de clique em botões
    void on_btnCriarBD_clicked();

    void on_btnImprimir_clicked();

    void on_btnTabela_clicked();

    void on_btnJson_clicked();

    void on_btnShowJson_clicked();

    void on_btnNovaJanela_clicked();

private:
    // Ponto de acesso para a interface gráfica
    Ui::MainWindow *ui;

    QSQLiteBaseClass *db;

    QSQLCipherClass dbCipher;

    QStandardItemModel *model;
};
#endif // MAINWINDOW_H
