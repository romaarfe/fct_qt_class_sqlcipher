#ifndef QSQLCIPHERCLASS_H
#define QSQLCIPHERCLASS_H

#define SQLITE_HAS_CODEC

#include <iostream>
#include <sqlcipher/sqlite3.h>
#include <string>
#include <QDebug>

using namespace std;

class QSQLCipherClass
{
public:
    QSQLCipherClass(const string& filename, const string& password);
    ~QSQLCipherClass();

    bool executeQuery(const string& query);


private:
    sqlite3* db;
};

#endif // QSQLCIPHERCLASS_H

