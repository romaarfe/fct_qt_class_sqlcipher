#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qsqlcipherclass.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnCriarBD_clicked()
{
    // Config basica para abertura da base de dados com a classe
    QString filename = "database.db";
    QString password = "senha";

    QSQLCipherClass db(filename, password);

    // Execução da query para criar a base de dados e inserir dados
    db.executeQuery("CREATE TABLE IF NOT EXISTS Heroi (id INTEGER PRIMARY KEY, nome TEXT, sobrenome TEXT)");

    db.executeQuery("INSERT INTO Heroi VALUES(1, 'Luke', 'Skywalker')");
    db.executeQuery("INSERT INTO Heroi VALUES(2, 'Leia', 'Organa')");
    db.executeQuery("INSERT INTO Heroi VALUES(3, 'Han', 'Solo')");
    db.executeQuery("INSERT INTO Heroi VALUES(4, 'Obiwan', 'Kenobi')");

    ui->lblResultado->setText("Base de dados criada com sucesso!");

    // Fechar a base de dados
    db.closeDb();
}

// Para remover as aspas
void removeQuotes(QString& str) {
    if (str.startsWith('"') && str.endsWith('"')) {
        str.remove(0, 1);
        str.chop(1);
    }
}

// Para imprimir as linhas
void printRow(const QStringList& row, const QList<int>& columnWidths) {
    QDebug dbg = qDebug().nospace();
    dbg << "|";
    for (int i = 0; i < row.size(); ++i) {
        dbg << qSetFieldWidth(columnWidths[i]) << row[i];
        dbg << "|";
    }
    qDebug();
}

void MainWindow::on_btnImprimir_clicked()
{
    // Construtor básico
    QSQLCipherClass db("database.db", "senha");

    // Necessário para buscar os resultados da execução da query
    QPair<QStringList, QList<QList<QVariant>>> queryResult = db.executeQuery("SELECT * FROM Heroi");
    const QStringList& columnNames = queryResult.first;
    const QList<QList<QVariant>>& results = queryResult.second;

    // Pega os nomes das colunas já limpos
    QStringList cleanedColumnNames = columnNames;
    for (QString& columnName : cleanedColumnNames) {
        removeQuotes(columnName);
    }

    // Dimensiona o tamanho/espaçamento das/entre as colunas
    QList<int> columnWidths;
    for (int i = 0; i < cleanedColumnNames.size(); ++i) {
        int maxWidth = cleanedColumnNames.at(i).length();
        for (const QList<QVariant>& row : results) {
            QString cellValue = row.at(i).toString();
            maxWidth = qMax(maxWidth, cellValue.length());
        }
        columnWidths.append(maxWidth);
    }

    // Apresenta os nomes originais das colunas no terminal através do qDebug()
    qDebug() << "Nomes das Colunas:";
    printRow(cleanedColumnNames, columnWidths);

    // Apresenta os dados de forma tabular no terminal através do qDebug()
    qDebug() << "Dados Inseridos:";
    for (const QList<QVariant>& row : results) {
        QStringList rowData;
        for (const QVariant& columnData : row) {
            rowData.append(columnData.toString());
        }
        printRow(rowData, columnWidths);
    }
}

void MainWindow::on_btnTabela_clicked()
{
    QString filename = "database.db";
    QString password = "senha";
    QString query = "SELECT * FROM Heroi";

    model = tabela->prepareAndShowTable(filename, password, query);

    // Cria efetivamente apresentação na QTableView
    ui->tbvTabela->setModel(model);

    // Apresenta na QTableView
    ui->tbvTabela->show();
}

void MainWindow::on_btnJson_clicked()
{
    QString filename = "database.db";
    QString password = "senha";
    QString query = "SELECT * FROM Heroi";

    QStandardItemModel* model = tabela->prepareAndShowTable(filename, password, query);
    QJsonDocument jsonDoc = tabela->convertModelToJson(model);

    // Agora você pode usar o JSON conforme necessário:
    QByteArray jsonData = jsonDoc.toJson();

    // Salvar em um arquivo, enviar pela rede, etc.
    QString fileName = "database.json";
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonData);
        file.close();
    }
}

