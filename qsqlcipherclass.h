#ifndef QSQLCIPHERCLASS_H
#define QSQLCIPHERCLASS_H

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


using namespace std;

class QSQLCipherClass
{
public:
    QSQLCipherClass();
    QSQLCipherClass(const QString& filename, const QString& password);

    void closeDb();
    sqlite3* getDbHandle() const;

    QPair<QStringList, QList<QList<QVariant>>> executeQuery(const QString& query);
    QStandardItemModel* prepareModel(const QStringList& columnNames, const QList<QList<QVariant>>& results);
    QStandardItemModel* prepareAndShowTable(const QString& databasePath, const QString& password, const QString& query);
    QJsonDocument convertModelToJson(QStandardItemModel* model);

private:
    sqlite3* dbHandle;
    QString db;
    QStandardItemModel* model;
};

#endif // QSQLCIPHERCLASS_H

