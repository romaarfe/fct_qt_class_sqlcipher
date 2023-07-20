#include "secondwindow.h"
#include "ui_secondwindow.h"

SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::on_btnCriarBD_clicked()
{
    // Cria uma instância da classe QSQLCipherClass para interagir com a base de dados
    QSQLiteClass db("baseDeDados.db", "");

    // Execução da query para criar a base de dados e inserir dados
    db.executeQuery("CREATE TABLE IF NOT EXISTS Vilao (id INTEGER PRIMARY KEY, nome TEXT, sobrenome TEXT)");

    // Insere dados na tabela Heroi
    db.executeQuery("INSERT INTO Vilao VALUES(5, 'Imperador', 'Palpatine')");
    db.executeQuery("INSERT INTO Vilao VALUES(6, 'Jabba', 'The Hutt')");
    db.executeQuery("INSERT INTO Vilao VALUES(7, 'Anakin', 'Skywalker')");
    db.executeQuery("INSERT INTO Vilao VALUES(8, 'Boba', 'Fett')");

    // Exibe uma mensagem de sucesso na interface do usuário
    ui->lblResultado->setText("Base de dados criada com sucesso!");

    // Fechar a base de dados
    db.closeDb();
}

void SecondWindow::printModelData(QStandardItemModel* model)
{
    if (!model)
    {
        qDebug() << "Modelo não existe ou está vazio.";
        return;
    }

    qDebug() << "Nomes das Colunas:";
    for (int i = 0; i < model->columnCount(); ++i)
    {
        qDebug() << model->headerData(i, Qt::Horizontal).toString();
    }

    qDebug() << "Dados Inseridos:";
    for (int row = 0; row < model->rowCount(); ++row)
    {
        QStringList rowData;
        for (int col = 0; col < model->columnCount(); ++col)
        {
            rowData.append(model->data(model->index(row, col)).toString());
        }
        qDebug() << rowData.join(", ");
    }
}

void SecondWindow::on_btnImprimir_clicked()
{

    // Executa a consulta e obtém o modelo com os resultados
    QStandardItemModel* model = db->prepareAndShowTable("baseDeDados.db", "", "SELECT * FROM Vilao");

    // Use a função auxiliar para imprimir os dados no terminal
    printModelData(model);
}


void SecondWindow::on_btnTabela_clicked()
{
    // Configuração básica para abertura da base de dados com a classe
    QString filename = "baseDeDados.db";
    QString password = "";
    QString query = "SELECT * FROM Vilao";

    // Prepara e exibe a tabela na QTableView da interface
    model = db->prepareAndShowTable(filename, password, query);

    // Exibe o modelo na QTableView
    ui->tbvTabela->setModel(model);

    // Apresenta a QTableView na interface
    ui->tbvTabela->show();
}


void SecondWindow::on_btnJson_clicked()
{
    // Configuração básica para abertura da base de dados com a classe
    QString filename = "baseDeDados.db";
    QString password = "";
    QString query = "SELECT * FROM Vilao";

    // Prepara o modelo e converte-o em JSON
    QStandardItemModel* model = db->prepareAndShowTable(filename, password, query);
    QJsonDocument jsonDoc = db->convertModelToJson(model);

    // Agora você pode usar o JSON conforme necessário:
    QByteArray jsonData = jsonDoc.toJson();

    // Salvar num ficheiro, enviar pela rede, etc.
    QString fileName = "baseDeDados.json";
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonData);
        file.close();
    }
}

void SecondWindow::on_btnShowJson_clicked()
{
    // Configuração básica para abertura da base de dados com a classe
    QString filename = "baseDeDados.db";
    QString password = "";
    QString query = "SELECT * FROM Vilao";

    // Prepara o modelo e converte-o em JSON
    QStandardItemModel* model = db->prepareAndShowTable(filename, password, query);
    QJsonDocument jsonDoc = db->convertModelToJson(model);

    // Convertendo o JSON para uma string formatada
    QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Indented);
    QString jsonString = QString::fromUtf8(jsonData);

    // Exibindo o JSON no QTextEdit da interface
    ui->textEdit->setPlainText(jsonString);
}

