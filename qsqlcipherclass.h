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
#include <QTableView>

using namespace std;

class QSQLCipherClass
{
public:
    QSQLCipherClass();
    QSQLCipherClass(const QString& filename, const QString& password);

    void createDB(const QString& query);
    void closeDB();

    sqlite3* getDbHandle() const;

    QPair<QStringList, QList<QList<QVariant>>> executeQuery(const QString& query);

    QStandardItemModel* prepareModel(const QStringList& columnNames, const QList<QList<QVariant>>& results);
    QStandardItemModel* prepareAndShowTable(const QString& databasePath, const QString& password, const QString& query);

private:
    sqlite3* dbHandle;
    QString db;
    QStandardItemModel* model;
};

#endif // QSQLCIPHERCLASS_H

