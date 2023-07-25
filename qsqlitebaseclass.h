#ifndef QSQLITEBASECLASS_H
#define QSQLITEBASECLASS_H

// Inclui as bibliotecas necessárias para o funcionamento da classe
#define SQLITE_HAS_CODEC

#include "qsqlcipherclass.h"    // Inclui a definição da classe QSQLCipherClass
#include "qsqliteclass.h"   // Inclui a definição da classe QSQLiteClass
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
#include <QtSql/QSqlDatabase>   // Inclui a biblioteca para suporte a base de dados SQL
#include <QtSql/QSqlQueryModel> // Inclui a biblioteca para suporte a modelos de consulta SQL
#include <QtSql/QSqlQuery>  // Inclui a biblioteca para suporte a consultas SQL
#include <QtSql/QSqlRecord> // Inclui a biblioteca para suporte a registros SQL
#include <QSqlError>    // Inclui a biblioteca para suporte a erros em consultas SQL

/**
 * @brief Classe base para acesso a base de dados SQLite/SQLCipher.
 *
 * Esta classe é abstrata, pois contém pelo menos um método puramente virtual.
 * As classes derivadas devem implementar os métodos virtuais para serem instanciadas.
 */
class QSQLiteBaseClass
{
public:
    QSQLiteBaseClass() {}

    virtual ~QSQLiteBaseClass() {}

    // Método virtual para fechar a base de dados
    virtual void closeDb() = 0;

    // Método virtual para executar uma consulta SQL e obter os resultados
    virtual QPair<QStringList, QList<QList<QVariant>>> executeQuery(const QString& query) = 0;

    // Método virtual para executar uma consulta e mostrar o resultado numa tabela
    virtual QStandardItemModel* prepareAndShowTable(const QString& databasePath, const QString& password, const QString& query) = 0;

    // Método virtual para converter um modelo de dados em formato JSON
    virtual QJsonDocument convertModelToJson(QStandardItemModel* model) = 0;
};

#endif // QSQLITEBASECLASS_H
