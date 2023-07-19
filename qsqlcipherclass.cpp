#include "qsqlcipherclass.h"

// Construtor para abrir a base de dados e inserir a palavra passe
QSQLCipherClass::QSQLCipherClass(const QString& filename, const QString& password)
{
    model = new QStandardItemModel();
    db = filename;

    sqlite3_open(db.toStdString().c_str(), &dbHandle);
    sqlite3_key(dbHandle, password.toStdString().c_str(), password.length());
}

// Para fechar a base de dados
void QSQLCipherClass::closeDb()
{
    sqlite3_close(dbHandle);
}

// Para manipular o apontador para base de dados
sqlite3* QSQLCipherClass::getDbHandle() const
{
    return dbHandle;
}

// Para de fato executar uma query
QPair<QStringList, QList<QList<QVariant>>> QSQLCipherClass::executeQuery(const QString& query)
{
    QStringList columnNames;
    QList<QList<QVariant>> results;

    // Prepara o statement
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(dbHandle, query.toStdString().c_str(), -1, &stmt, nullptr);

    // Busca os nomes das colunas no statement
    int columnCount = sqlite3_column_count(stmt);
    for (int i = 0; i < columnCount; ++i) {
        const char* columnName = sqlite3_column_name(stmt, i);
        columnNames.append(QString::fromUtf8(columnName));
    }

    // Executa a query e faz fetch dos resultados
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        QList<QVariant> row;
        for (int i = 0; i < columnCount; ++i) {
            int columnType = sqlite3_column_type(stmt, i);

            switch (columnType) {
            case SQLITE_INTEGER:
                row.append(sqlite3_column_int(stmt, i));
                break;
            case SQLITE_TEXT: {
                const char* text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
                row.append(QString::fromUtf8(text));
                break;
            }
            case SQLITE_FLOAT:
                row.append(sqlite3_column_double(stmt, i));
                break;
            case SQLITE_BLOB: {
                int dataSize = sqlite3_column_bytes(stmt, i);
                const void* blobData = sqlite3_column_blob(stmt, i);
                row.append(QByteArray(static_cast<const char*>(blobData), dataSize));
                break;
            }
            case SQLITE_NULL:
                row.append(QVariant());
                break;
            default:
                // Caso precise
                row.append(QVariant());
                break;
            }
        }

        results.append(row);
    }

    // Finaliza o statement preparado
    sqlite3_finalize(stmt);

    return qMakePair(columnNames, results);
}

QStandardItemModel* QSQLCipherClass::prepareModel(const QStringList& columnNames, const QList<QList<QVariant>>& results)
{
    QStandardItemModel* model = new QStandardItemModel();

    // Configura os nomes das colunas no modelo
    model->setHorizontalHeaderLabels(columnNames);

    // Preenche o modelo com os dados vindos do resultado da query
    for (const QList<QVariant>& row : results) {
        QList<QStandardItem*> items;
        for (const QVariant& columnData : row) {
            QStandardItem* item = new QStandardItem(columnData.toString());
            items.append(item);
        }
        model->appendRow(items);
    }

    return model;
}

QStandardItemModel* QSQLCipherClass::prepareAndShowTable(const QString& filename, const QString& password, const QString& query)
{
     // Necessário para buscar os resultados da execução da query
    QSQLCipherClass db(filename, password);

    // Necessário para buscar os resultados da execução da query
    QPair<QStringList, QList<QList<QVariant>>> queryResult = db.executeQuery(query);
    const QStringList& columnNames = queryResult.first;
    const QList<QList<QVariant>>& results = queryResult.second;

    // Prepara o modelo a partir dos resultados da query
    QStandardItemModel* model = prepareModel(columnNames, results);

    // Retorna o modelo, se desejar usá-lo em outras partes do código
    return model;
}


QJsonDocument QSQLCipherClass::convertModelToJson(QStandardItemModel* model)
{
    QJsonArray jsonArray;
    const int rowCount = model->rowCount();
    const int columnCount = model->columnCount();

    for (int row = 0; row < rowCount; ++row) {
        QJsonObject jsonObject;
        for (int col = 0; col < columnCount; ++col) {
            QModelIndex index = model->index(row, col);
            QString fieldName = model->headerData(col, Qt::Horizontal).toString();
            QVariant fieldValue = model->data(index);
            jsonObject[fieldName] = QJsonValue::fromVariant(fieldValue);
        }
        jsonArray.append(jsonObject);
    }

    QJsonDocument jsonDoc(jsonArray);
    return jsonDoc;
}
