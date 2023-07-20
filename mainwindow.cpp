#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qsqlcipherclass.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Configura a interface de utilizador definida no arquivo .ui
    ui->setupUi(this);

    // Conectando o clique do botão ao slot on_btnShowJson_clicked
    connect(ui->btnShowJson, &QPushButton::clicked, this, &MainWindow::on_btnShowJson_clicked);

    //connect(ui->btnNovaJanela, &QPushButton::clicked, this, &MainWindow::on_btnNovaJanela_clicked);
}

MainWindow::~MainWindow()
{
    // Libera a memória alocada para a interface de usuário
    delete ui;
}

void MainWindow::on_btnCriarBD_clicked()
{
    // Configuração básica para abertura da base de dados com a classe
    QString filename = "database.db";
    QString password = "senha";

    // Cria uma instância da classe QSQLCipherClass para interagir com a base de dados
    QSQLCipherClass db(filename, password);

    // Execução da query para criar a base de dados e inserir dados
    db.executeQuery("CREATE TABLE IF NOT EXISTS Heroi (id INTEGER PRIMARY KEY, nome TEXT, sobrenome TEXT)");

    // Insere dados na tabela Heroi
    db.executeQuery("INSERT INTO Heroi VALUES(1, 'Luke', 'Skywalker')");
    db.executeQuery("INSERT INTO Heroi VALUES(2, 'Leia', 'Organa')");
    db.executeQuery("INSERT INTO Heroi VALUES(3, 'Han', 'Solo')");
    db.executeQuery("INSERT INTO Heroi VALUES(4, 'Obiwan', 'Kenobi')");

    // Exibe uma mensagem de sucesso na interface do usuário
    ui->lblResultado->setText("Base de dados criada com sucesso!");

    // Fechar a base de dados
    db.closeDb();
}

// Para remover as aspas
void removeQuotes(QString& str)
{
    if (str.startsWith('"') && str.endsWith('"')) {
        str.remove(0, 1);
        str.chop(1);
    }
}

// Para imprimir as linhas
void printRow(const QStringList& row, const QList<int>& columnWidths)
{
    QDebug dbg = qDebug().nospace();
    dbg << "|";
    for (int i = 0; i < row.size(); i++) {
        dbg << qSetFieldWidth(columnWidths[i]) << row[i];
        dbg << "|";
    }
    qDebug();
}

void MainWindow::on_btnImprimir_clicked()
{
    // Criação de uma instância da classe QSQLCipherClass para interagir com a base de dados
    QSQLCipherClass db("database.db", "senha");

    // Necessário para buscar os resultados da execução da query
    QPair<QStringList, QList<QList<QVariant>>> queryResult = db.executeQuery("SELECT * FROM Heroi");
    const QStringList& columnNames = queryResult.first;
    const QList<QList<QVariant>>& results = queryResult.second;

    // Pega os nomes das colunas já limpos (removendo as aspas, se houver)
    QStringList cleanedColumnNames = columnNames;
    for (QString& columnName : cleanedColumnNames) {
        removeQuotes(columnName);
    }

    // Dimensiona o tamanho/espaçamento das/entre as colunas para uma apresentação tabular
    QList<int> columnWidths;
    for (int i = 0; i < cleanedColumnNames.size(); i++) {
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
    // Configuração básica para abertura da base de dados com a classe
    QString filename = "database.db";
    QString password = "senha";
    QString query = "SELECT * FROM Heroi";

    // Prepara e exibe a tabela na QTableView da interface
    model = tabela->prepareAndShowTable(filename, password, query);

    // Exibe o modelo na QTableView
    ui->tbvTabela->setModel(model);

    // Apresenta a QTableView na interface
    ui->tbvTabela->show();
}

void MainWindow::on_btnJson_clicked()
{
    // Configuração básica para abertura da base de dados com a classe
    QString filename = "database.db";
    QString password = "senha";
    QString query = "SELECT * FROM Heroi";

    // Prepara o modelo e converte-o em JSON
    QStandardItemModel* model = tabela->prepareAndShowTable(filename, password, query);
    QJsonDocument jsonDoc = tabela->convertModelToJson(model);

    // Agora você pode usar o JSON conforme necessário:
    QByteArray jsonData = jsonDoc.toJson();

    // Salvar num ficheiro, enviar pela rede, etc.
    QString fileName = "database.json";
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonData);
        file.close();
    }
}

void MainWindow::on_btnShowJson_clicked()
{
    // Configuração básica para abertura da base de dados com a classe
    QString filename = "database.db";
    QString password = "senha";
    QString query = "SELECT * FROM Heroi";

    // Prepara o modelo e converte-o em JSON
    QStandardItemModel* model = tabela->prepareAndShowTable(filename, password, query);
    QJsonDocument jsonDoc = tabela->convertModelToJson(model);

    // Convertendo o JSON para uma string formatada
    QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Indented);
    QString jsonString = QString::fromUtf8(jsonData);

    // Exibindo o JSON no QTextEdit da interface
    ui->textEdit->setPlainText(jsonString);
}

void MainWindow::on_btnNovaJanela_clicked()
{
    // Crie e mostre uma instância da segunda janela
    SecondWindow *secondWindow = new SecondWindow(this);
    secondWindow->show();
}

