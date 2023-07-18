#include "qsqlcipherclass.h"

QSQLCipherClass::QSQLCipherClass(const string& filename, const string& password)
    : db(nullptr)
{
    int rc = sqlite3_open(filename.c_str(), &db);
    if (rc == SQLITE_OK)
    {
        // Define a senha para o banco de dados
        sqlite3_key(db, password.c_str(), password.length());
    }
    else
    {
        qDebug("Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        db = nullptr;
    }
}

QSQLCipherClass::~QSQLCipherClass()
{
    if (db)
    {
        sqlite3_close(db);
    }
}

bool QSQLCipherClass::executeQuery(const string& query)
{
    if (!db)
    {
        qDebug("Banco de dados não aberto\n");
            return false;
    }

    char* errorMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMsg);
    if (rc != SQLITE_OK)
    {
        qDebug("Erro ao executar a consulta: %s\n", errorMsg);
        sqlite3_free(errorMsg);
        return false;
    }

    return true;
}


