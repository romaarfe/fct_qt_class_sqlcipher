#include "secondwindow.h"   // Inclui o ficheiro de cabeçalho da classe SecondWindow.
#include "ui_secondwindow.h"    // Inclui o ficheiro de cabeçalho gerado automaticamente pelo Qt para a interface gráfica.

// Construtor da classe SecondWindow
SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)    // Inicializa a interface gráfica (ui) da janela.
{
    ui->setupUi(this);  // Configura a interface gráfica da janela (definida no arquivo .ui).
}

// Destrutor da classe SecondWindowS
SecondWindow::~SecondWindow()
{
    delete ui;  // Libera a memória ocupada pela interface gráfica (ui) da janela.
}

void SecondWindow::on_btnCriarBD_clicked()
{
    // Cria uma instância da classe QSQLiteClass para interagir com a base de dados
    QSQLiteClass dbLite("baseDeDados.db", "");
    db = &dbLite;

    // Execução da query para criar a base de dados e inserir dados
    db->executeQuery("CREATE TABLE IF NOT EXISTS Vilao (id INTEGER PRIMARY KEY, nome TEXT, sobrenome TEXT)");

    // Insere dados na tabela Vilao
    db->executeQuery("INSERT INTO Vilao VALUES(5, 'Imperador', 'Palpatine')");
    db->executeQuery("INSERT INTO Vilao VALUES(6, 'Jabba', 'The Hutt')");
    db->executeQuery("INSERT INTO Vilao VALUES(7, 'Anakin', 'Skywalker')");
    db->executeQuery("INSERT INTO Vilao VALUES(8, 'Boba', 'Fett')");

    // Exibe uma mensagem de sucesso na interface do usuário
    ui->lblResultado->setText("Base de dados criada com sucesso!");

    // Fechar a base de dados
    db->closeDb();
}

// Método auxiliar para imprimir dados do modelo na saída de depuração (qDebug)
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
    db = &dbLite;

    // Executa a consulta e obtém o modelo com os resultados
    QStandardItemModel* model = db->prepareAndShowTable("baseDeDados.db", "", "SELECT * FROM Vilao");

    // Use a função auxiliar para imprimir os dados no terminal
    printModelData(model);

    db->closeDb();
}


void SecondWindow::on_btnTabela_clicked()
{
    db = &dbLite;

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

    db->closeDb();
}


void SecondWindow::on_btnJson_clicked()
{
    db = &dbLite;

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

    db->closeDb();
}

void SecondWindow::on_btnShowJson_clicked()
{
    db = &dbLite;

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

    db->closeDb();
}

