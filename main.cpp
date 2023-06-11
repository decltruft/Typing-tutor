#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");

    QApplication a(argc, argv);
    MainWindow w;                // объект главного окна
    w.show();                   // отображение главного
    w.show_Instruction();

    return a.exec();            // возврат результата выполнения программы
}
