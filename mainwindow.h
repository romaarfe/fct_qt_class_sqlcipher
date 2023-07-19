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

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnCriarBD_clicked();

    void on_btnImprimir_clicked();

    void on_btnTabela_clicked();

    void on_btnJson_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel* model;
    QSQLCipherClass* tabela;
};
#endif // MAINWINDOW_H
