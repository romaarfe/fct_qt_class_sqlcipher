#ifndef QSQLCIPHERCLASS_H
#define QSQLCIPHERCLASS_H

// Inclui as bibliotecas necessárias para o funcionamento da classe
#define SQLITE_HAS_CODEC

#include <iostream>
#include <sqlcipher/sqlite3.h>
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

// Inclui a classe no namespace std para evitar ter que escrever std::
using namespace std;

class QSQLCipherClass
{
public:
    // Construtor padrão vazio
    QSQLCipherClass();

    // Construtor que abre a base de dados (com parâmetros)
    QSQLCipherClass(const QString& filename, const QString& password);

    void closeDb();

    // Função para executar uma consulta SQL e obter os resultados
    QPair<QStringList, QList<QList<QVariant>>> executeQuery(const QString& query);

    // Função para executar uma consulta e mostrar o resultado numa tabela
    QStandardItemModel* prepareAndShowTable(const QString& databasePath, const QString& password, const QString& query);

    // Função para converter um modelo de dados em formato JSON
    QJsonDocument convertModelToJson(QStandardItemModel* model);

private:
    // Apontador para a base de dados SQLite/SQLCipher
    sqlite3* dbHandle;

    // Nome do ficheiro da base de dados SQLite/SQLCipher
    QString db;

    // Modelo de dados para armazenar os resultados da consulta
    QStandardItemModel* model;

    // Função para obter o apontador para a base de dados
    sqlite3* getDbHandle() const;

    // Função para preparar um modelo de dados a partir dos resultados da consulta
    QStandardItemModel* prepareModel(const QStringList& columnNames, const QList<QList<QVariant>>& results);
};

#endif // QSQLCIPHERCLASS_H

