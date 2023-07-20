#include "qsqliteclass.h"

QSQLiteClass::QSQLiteClass(const QString& filename, const QString& password)
{
    // Configura o tipo de base de dados para SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");

    // Define o caminho do ficheiro da base de dados
    db.setDatabaseName(filename);
    db.setPassword(password);
}

// Função para fechar a conexão com a base de dados
void QSQLiteClass::closeDb()
{
    if (db.isOpen())
    {
        db.close();
    }
}

QPair<QStringList, QList<QList<QVariant>>> QSQLiteClass::executeQuery(const QString& query)
{
    // Abre a conexão com o banco de dados
    if (!db.isOpen())
    {
        db.open();
    }

    QStringList columnNames;
    QList<QList<QVariant>> results;

    QSqlQuery queryObj(db);
    if (!queryObj.exec(query))
    {
        // Trate o erro, se necessário
        // ...
        return qMakePair(columnNames, results);
    }

    QSqlRecord record = queryObj.record();

    // Obtém os nomes das colunas do resultado da consulta
    for (int i = 0; i < record.count(); ++i)
    {
        columnNames.append(record.fieldName(i));
    }

    // Obtém os dados do resultado da consulta
    while (queryObj.next())
    {
        QList<QVariant> row;
        for (int i = 0; i < record.count(); ++i)
        {
            row.append(queryObj.value(i));
        }
        results.append(row);
    }

    // Retorna uma estrutura QPair com os nomes das colunas e os resultados da consulta
    return qMakePair(columnNames, results);
}

QStandardItemModel* QSQLiteClass::prepareModel(const QStringList& columnNames, const QList<QList<QVariant>>& results)
{
    // Criação de um novo modelo
    QStandardItemModel* model = new QStandardItemModel();

    // Configura os nomes das colunas no modelo
    model->setHorizontalHeaderLabels(columnNames);

    // Preenche o modelo com os dados vindos do resultado da query
    for (const QList<QVariant>& row : results)
    {
        QList<QStandardItem*> items;
        for (const QVariant& columnData : row)
        {
            // Cria um novo item do modelo e adiciona à lista de itens
            QStandardItem* item = new QStandardItem(columnData.toString());
            items.append(item);
        }

        // Adiciona uma nova linha ao modelo com os itens criados acima
        model->appendRow(items);
    }

    // Retorna o modelo preenchido com os dados da consulta
    return model;
}

QStandardItemModel* QSQLiteClass::prepareAndShowTable(const QString& filename, const QString& password, const QString& query)
{
    // Configuração da conexão com o banco de dados
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    db.setPassword(password);

    // Verifica se a conexão foi aberta corretamente
    if (!db.open())
    {
        // Trate o erro, se necessário
        qDebug() << "Erro ao abrir a base de dados.";
        return nullptr;
    }

    // Executa a consulta e obtém os resultados
    QSqlQuery queryObj(query);
    if (!queryObj.exec())
    {
        // Trate o erro, se necessário
        qDebug() << "Erro ao executar a consulta:" << queryObj.lastError().text();
        db.close();
        return nullptr;
    }

    // Obtém os nomes das colunas do resultado da consulta
    QStringList columnNames;
    QSqlRecord record = queryObj.record();
    for (int i = 0; i < record.count(); ++i)
    {
        columnNames.append(record.fieldName(i));
    }

    // Obtém os dados do resultado da consulta
    QList<QList<QVariant>> results;
    while (queryObj.next())
    {
        QList<QVariant> row;
        for (int i = 0; i < record.count(); ++i)
        {
            row.append(queryObj.value(i));
        }
        results.append(row);
    }

    // Prepara o modelo a partir dos resultados da consulta
    QStandardItemModel* model = prepareModel(columnNames, results);

    // Feche a conexão com o banco de dados
    db.close();

    // Retorna o modelo preenchido com os dados da consulta
    return model;
}

QJsonDocument QSQLiteClass::convertModelToJson(QStandardItemModel* model)
{
    // Criação de um QJsonArray para armazenar os objetos JSON das linhas do modelo
    QJsonArray jsonArray;

    // Obtém o número de linhas e colunas do modelo
    const int rowCount = model->rowCount();
    const int columnCount = model->columnCount();

    // Ciclo pelas linhas do modelo
    for (int row = 0; row < rowCount; row++)
    {
        // Cria um objeto JSON para representar uma linha do modelo
        QJsonObject jsonObject;

        // Ciclo pelas colunas do modelo
        for (int col = 0; col < columnCount; col++)
        {
            // Obtém o índice do modelo para o campo atual (linha e coluna)
            QModelIndex index = model->index(row, col);

            // Obtém o nome do campo usando o cabeçalho da coluna
            QString fieldName = model->headerData(col, Qt::Horizontal).toString();

            // Obtém o valor do campo atual
            QVariant fieldValue = model->data(index);

            // Adiciona o campo e seu valor como uma propriedade no objeto JSON
            jsonObject[fieldName] = QJsonValue::fromVariant(fieldValue);
        }

        // Adiciona o objeto JSON da linha ao array JSON
        jsonArray.append(jsonObject);
    }

    // Cria um documento JSON a partir do array JSON
    QJsonDocument jsonDoc(jsonArray);

    // Retorna o documento JSON que contém os dados do modelo em formato JSON
    return jsonDoc;
}
