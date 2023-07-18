#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define SQLITE_HAS_CODEC

#include <iostream>
#include <sqlcipher/sqlite3.h>
#include <QDebug>
#include <QApplication>
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlTableModel>
#include <QMessageBox>
#include <QApplication>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QStandardItemModel>
#include <QTableView>
#include <QDialog>

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

    static int imprimir(void* dados, int qt, char** linha, char** coluna);

private slots:
    void on_btnCriarBD_clicked();

    void on_btnImprimir_clicked();

    void on_btnTabela_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
