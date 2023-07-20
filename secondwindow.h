#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include "qsqliteclass.h"
#include "secondwindow.h"
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


namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

private slots:
    void on_btnCriarBD_clicked();

    void on_btnImprimir_clicked();

    void on_btnTabela_clicked();

    void on_btnJson_clicked();

    void on_btnShowJson_clicked();

private:
    Ui::SecondWindow *ui;

    void printModelData(QStandardItemModel* model);

    // Modelo para exibir a tabela na QTableView
    QStandardItemModel* model;

    QSQLiteClass* db;
};

#endif // SECONDWINDOW_H
