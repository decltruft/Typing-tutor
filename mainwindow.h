#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QThread>
#include <QString>
#include <fstream>
#include <random>
#include <ctime>
#include <QKeyEvent>
#include "timerloop.h"
#include "dialog.h"

namespace Ui
{
    class MainWindow;
}

class TimerLoop;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0); // конструктор главного окна
    void show_Instruction() { d->show(); };
    ~MainWindow();                            // деструктор главного окна

private slots:
    void on_push_start_button_clicked();      // слот обработки нажатия кнопки на главном окне

public slots:
    void get_clock(int count);
    void begin_game();
    void finish_game();

signals:
    void start_loop();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    unsigned int index;                     // индекс текущего элемента случайного слова в векторе
    unsigned int random_index;              // сгенерированный рандомный индекс случайного слова в векторе

    unsigned int count_of_mistakes;         // кол-во ошибок , которое будет записываться в главное окно в соответсвующее поле
    unsigned int count_of_words;
    unsigned int local_mistakes;

    unsigned int exp;                       // общее кол-во опыта за все введенные слова

    Ui::MainWindow *ui;                     // указатель на главное окно. через него будет происходить обращение ко всем полям формы
    std::vector<QString> words;             // объект вектор (аналог массива), который будет содержать все слова для ввода в тренажёре
    TimerLoop *tl;
    std::multimap<int, QChar> simbols;      // карта соответствия кода нажатой клавиши с символом, который ей соответсвует
    QThread *thread;
    Dialog *d;
};





#endif // MAINWINDOW_H
