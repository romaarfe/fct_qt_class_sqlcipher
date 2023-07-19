#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define SQLITE_HAS_CODEC

#include "qsqlcipherclass.h"
#include <iostream>
#include <sqlcipher/sqlite3.h>
#include <QDebug>
#include <QApplication>
#include <QMainWindow>
#include <QList>
#include <QVariant>
#include <QFile>
#include <QObject>
#include <QWebEngineView>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextEdit>


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

private:
    // Ponto de acesso para a interface gráfica
    Ui::MainWindow *ui;

    // Modelo para exibir a tabela na QTableView
    QStandardItemModel* model;

    // Objeto para manipulação da base de dados e conversão para JSON
    QSQLCipherClass* tabela;
};
#endif // MAINWINDOW_H
