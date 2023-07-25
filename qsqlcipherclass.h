#ifndef QSQLCIPHERCLASS_H
#define QSQLCIPHERCLASS_H

// Inclui as bibliotecas necessárias para o funcionamento da classe
#define SQLITE_HAS_CODEC

#include "qsqliteclass.h"   // Inclui a definição da classe QSQLiteClass
#include "qsqlitebaseclass.h"   // Inclui a definição da classe QSQLiteBaseClass
#include <iostream>
#include <sqlcipher/sqlite3.h>  // Inclui a biblioteca SQLite com suporte a SQLCipher
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

class QSQLCipherClass : public QSQLiteBaseClass
{
public:
    // Construtor padrão vazio
    QSQLCipherClass() {}

    // Construtor com parâmetros
    QSQLCipherClass(const QString& filename, const QString& password);

    ~QSQLCipherClass() override {}

    // Método para fechar a base de dados
    void closeDb() override;

    // Método para executar uma consulta SQL e obter os resultados
    QPair<QStringList, QList<QList<QVariant>>> executeQuery(const QString& query) override;

    // Método para executar uma consulta e mostrar o resultado numa tabela
    QStandardItemModel* prepareAndShowTable(const QString& databasePath, const QString& password, const QString& query) override;

    // Método para converter um modelo de dados em formato JSON
    QJsonDocument convertModelToJson(QStandardItemModel* model) override;

private:
    // Apontador para a base de dados SQLite/SQLCipher
    sqlite3* dbHandle;

    // Nome do ficheiro da base de dados SQLite/SQLCipher
    QString dbString;

    // Declaração um objeto da classe QSQLCipherClass
    QSQLCipherClass *dbCipher;

    // Modelo de dados para armazenar os resultados da consulta
    QStandardItemModel* model;

    // Método interno para obter o apontador para a base de dados
    sqlite3* getDbHandle() const;

    // Método interno para preparar um modelo de dados a partir dos resultados da consulta
    QStandardItemModel* prepareModel(const QStringList& columnNames, const QList<QList<QVariant>>& results);
};

#endif // QSQLCIPHERCLASS_H

