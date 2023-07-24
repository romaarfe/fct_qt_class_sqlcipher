#include "mainwindow.h" // Inclui o ficheiro de cabeçalho "mainwindow.h", que provavelmente define a classe MainWindow.

#include <QApplication> // Inclui o ficheiro de cabeçalho da classe QApplication, necessária para criar o aplicativo Qt.

int main(int argc, char *argv[])
{
    // Cria uma instância da classe QApplication para gerenciar o aplicativo.
    QApplication a(argc, argv);

    // Cria uma instância da classe MainWindow. Provavelmente, essa é a janela principal do aplicativo.
    MainWindow w;

    // Mostra a janela principal.
    w.show();

    // Inicia o loop de eventos do aplicativo e aguarda até que o aplicativo seja encerrado.
    return a.exec();
}
