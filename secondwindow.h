#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include "qsqlcipherclass.h"
#include "qsqliteclass.h"
#include "qsqlitebaseclass.h"
#include "secondwindow.h"   // Inclui o próprio ficheiro de cabeçalho (pode ser desnecessário).
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
    // Macro que indica que essa classe contém slots (métodos que podem ser conectados a sinais).
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

private slots:
    // Slots para responder a eventos de clique em botões
    void on_btnCriarBD_clicked();

    void on_btnImprimir_clicked();

    void on_btnTabela_clicked();

    void on_btnJson_clicked();

    void on_btnShowJson_clicked();

private:
    // Apontador para o objeto de interface gráfica.
    Ui::SecondWindow *ui;

    // Função auxiliar para imprimir dados do modelo.
    void printModelData(QStandardItemModel* model);

    // Modelo para exibir a tabela na QTableView
    QStandardItemModel* model;

    // Apontador para a classe base para acesso a bases de dados SQLite.
    QSQLiteBaseClass *db;

    // Instância da classe para acesso a bases de dados SQLite.
    QSQLiteClass dbLite;
};

#endif // SECONDWINDOW_H
