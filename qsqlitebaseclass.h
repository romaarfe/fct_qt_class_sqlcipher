#ifndef QSQLITEBASECLASS_H
#define QSQLITEBASECLASS_H

// Inclui as bibliotecas necessárias para o funcionamento da classe
#define SQLITE_HAS_CODEC

#include "qsqlcipherclass.h"
#include "qsqliteclass.h"
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
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QSqlError>


class QSQLiteBaseClass
{
public:
    QSQLiteBaseClass() {}

    virtual void closeDb() = 0;

    virtual QPair<QStringList, QList<QList<QVariant>>> executeQuery(const QString& query) = 0;

    virtual QStandardItemModel* prepareAndShowTable(const QString& databasePath, const QString& password, const QString& query) = 0;

    virtual QJsonDocument convertModelToJson(QStandardItemModel* model) = 0;
};

#endif // QSQLITEBASECLASS_H
