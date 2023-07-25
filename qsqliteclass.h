#ifndef QSQLITECLASS_H
#define QSQLITECLASS_H

// Inclui as bibliotecas necessárias para o funcionamento da classe
#define SQLITE_HAS_CODEC

#include "qsqlcipherclass.h"
#include "qsqlitebaseclass.h"
#include <QString>
#include <QDebug>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QList>
#include <QVariant>
#include <QTableView>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariantMap>
#include <QVariantList>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QSqlError>

// Inclui a classe no namespace std para evitar ter que escrever std::
using namespace std;

// Diretiva de pré-processador que evita inclusões múltiplas do arquivo de cabeçalho.
// Protege contra erros de duplicação de definições.
class QSQLiteClass : public QSQLiteBaseClass
{
public:
    // Construtor padrão.
    QSQLiteClass() {}

    // Construtor sobrecarregado para receber o nome do ficheiro e senha da base de dados.
    QSQLiteClass(const QString& filename, const QString& password);

    ~QSQLiteClass() override {}

    // Método para fechar a conexão com a base de dados.
    void closeDb() override;

    // Método para executar uma consulta SQL na base de dados.
    // Retorna um par contendo uma lista de nomes de colunas e uma lista de linhas com resultados da consulta.
    QPair<QStringList, QList<QList<QVariant>>> executeQuery(const QString& query) override;

    // Método para preparar e exibir uma tabela a partir do caminho da base de dados, senha e consulta SQL.
    // Retorna um modelo de exibição de tabela.
    QStandardItemModel* prepareAndShowTable(const QString& databasePath, const QString& password, const QString& query) override;

    // Método para converter um modelo de exibição de tabela em um documento JSON.
    QJsonDocument convertModelToJson(QStandardItemModel* model) override;

private:
    // Objeto de conexão com a base de dados SQLite.
    QSqlDatabase db;

    // Modelo de exibição de tabela usado internamente na classe.
    QStandardItemModel* model;

    // Método interno para preparar o modelo de exibição de tabela a partir de colunas e resultados.
    QStandardItemModel* prepareModel(const QStringList& columnNames, const QList<QList<QVariant>>& results);
};

#endif // QSQLITECLASS_H
