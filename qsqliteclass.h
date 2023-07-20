#ifndef QSQLITECLASS_H
#define QSQLITECLASS_H

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

class QSQLiteClass
{
public:
    QSQLiteClass();

    QSQLiteClass(const QString& filename, const QString& password);

    void closeDb();

    QPair<QStringList, QList<QList<QVariant>>> executeQuery(const QString& query);

    QStandardItemModel* prepareAndShowTable(const QString& databasePath, const QString& password, const QString& query);

    QJsonDocument convertModelToJson(QStandardItemModel* model);

private:
    QSqlDatabase db;

    QStandardItemModel* model;
    QStandardItemModel* prepareModel(const QStringList& columnNames, const QList<QList<QVariant>>& results);
};

#endif // QSQLITECLASS_H
