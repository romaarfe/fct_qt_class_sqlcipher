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

    string filename = "database.db";
    string password = "senha";

    QSQLCipherClass db(filename, password);

    if (db.executeQuery("CREATE TABLE Heroi (id INTEGER PRIMARY KEY, nome TEXT, sobrenome TEXT)"))
    {
        db.executeQuery("INSERT INTO Heroi VALUES(1, 'Luke', 'Skywalker');"
                        "INSERT INTO Heroi VALUES(2, 'Leia', 'Organa');"
                        "INSERT INTO Heroi VALUES(3, 'Han', 'Solo');"
                        "INSERT INTO Heroi VALUES(4, 'Obiwan', 'Kenobi');");

        ui->lblResultado->setText("Base de dados criada com sucesso!");
    }
    else
    {
        ui->lblResultado->setText("Base de dados já existe!");
    }

    db.~QSQLCipherClass();
}


void MainWindow::on_btnImprimir_clicked()
{
//    QSQLCipherClass db("database.db", "senha");
//    qDebug() << db.executeQuery("SELECT * FROM Heroi");

    sqlite3* db;

    sqlite3_open("database.db", &db);
    sqlite3_key(db, "senha", 5);

    const char* query = "SELECT * FROM Heroi";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int column1Value = sqlite3_column_int(stmt, 0);
        const char* column2Value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* column3Value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        qDebug() << "ID:" << column1Value;
        qDebug() << "NOME:" << column2Value;
        qDebug() << "SOBRENOME:" << column3Value;
        qDebug() << "----------------------------";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

}


void MainWindow::on_btnTabela_clicked()
{
    sqlite3* db;

    sqlite3_open("database.db", &db);
    sqlite3_key(db, "senha", 5);

    // Execute sua consulta SQL usando o SQLCipher API (por exemplo, SELECT * FROM sua_tabela;)
    const char* selectQuery = "SELECT * FROM Heroi";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, selectQuery, -1, &stmt, nullptr);

    // Criar o modelo de itens para a QTableView
    QStandardItemModel model;

    // Carregar os dados do cabeçalho da tabela
    int columnCount = sqlite3_column_count(stmt);
    for (int i = 0; i < columnCount; ++i) {
        const char* columnName = sqlite3_column_name(stmt, i);
        model.setHorizontalHeaderItem(i, new QStandardItem(QString::fromUtf8(columnName)));
    }

    // Carregar os dados das linhas
    while ((sqlite3_step(stmt)) == SQLITE_ROW) {
        QList<QStandardItem*> rowData;
        for (int i = 0; i < columnCount; ++i) {
            const char* columnValue = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            rowData.append(new QStandardItem(QString::fromUtf8(columnValue)));
        }
        model.appendRow(rowData);
    }

    // Fechar o banco de dados SQLCipher
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // Exibir a QTableView
    ui->tbvTabela->setModel(&model);

}

