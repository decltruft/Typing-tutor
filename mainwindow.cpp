#pragma once

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    d(new Dialog()),
    index(0),
    random_index(0),
    count_of_mistakes(0),
    local_mistakes(0),
    exp(0),
    count_of_words(0)
{
    ui->setupUi(this);

    tl = new TimerLoop();
    thread = new QThread();

    connect(tl, SIGNAL(send_clock(int)), this, SLOT(get_clock(int)), Qt::QueuedConnection);
    connect(tl, SIGNAL(start_game()), this, SLOT(begin_game()), Qt::QueuedConnection);
    connect(tl, SIGNAL(stop_game()), this, SLOT(finish_game()), Qt::QueuedConnection);

    connect(this, SIGNAL(start_loop()), tl, SLOT(begin_loop()), Qt::QueuedConnection);


    tl->moveToThread(thread);
    thread->start();

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint); // установка флагов главного окна для фиксации его изначального размера
    setFixedSize(QSize(width(), height()));

    std::string str;                     // создание строки для ввода из файла
    std::ifstream fin("wordseng.txt");   // создаём объект ifstream для того чтобы вывести наши строки из файла с названием
    while(fin >> str)                    // пока есть строки, то записываем их в наш вектор
    {
        words.push_back(QString::fromStdString(str));  // преобразование std::string в QString с помощью статического метода класса QString
    }

    simbols.insert( {Qt::Key_Q, QChar ('q')});
    simbols.insert( {Qt::Key_W, QChar ('w')});
    simbols.insert( {Qt::Key_E, QChar ('e')});
    simbols.insert( {Qt::Key_R, QChar ('r')});
    simbols.insert( {Qt::Key_T, QChar ('t')});
    simbols.insert( {Qt::Key_Y, QChar ('y')});
    simbols.insert( {Qt::Key_U, QChar ('u')});
    simbols.insert( {Qt::Key_I, QChar ('i')});
    simbols.insert( {Qt::Key_O, QChar ('o')});
    simbols.insert( {Qt::Key_P, QChar ('p')});
//  simbols.insert( {Qt::Key_BraceLeft, QChar ('х')});
//  simbols.insert( {Qt::Key_BraceRight, QChar ('ъ')});
    simbols.insert( {Qt::Key_A, QChar ('a')});
    simbols.insert( {Qt::Key_S, QChar ('s')});
    simbols.insert( {Qt::Key_D, QChar ('d')});
    simbols.insert( {Qt::Key_F, QChar ('f')});
    simbols.insert( {Qt::Key_G, QChar ('g')});
    simbols.insert( {Qt::Key_H, QChar ('h')});
    simbols.insert( {Qt::Key_J, QChar ('j')});
    simbols.insert( {Qt::Key_K, QChar ('k')});
    simbols.insert( {Qt::Key_L, QChar ('l')});
//  simbols.insert( {Qt::Key_Colon, QChar ('ж')});
//  simbols.insert( {Qt::Key_Apostrophe, QChar ('э')});
    simbols.insert( {Qt::Key_Z, QChar ('z')});
    simbols.insert( {Qt::Key_X, QChar ('x')});
    simbols.insert( {Qt::Key_C, QChar ('c')});
    simbols.insert( {Qt::Key_V, QChar ('v')});
    simbols.insert( {Qt::Key_B, QChar ('b')});
    simbols.insert( {Qt::Key_N, QChar ('n')});
    simbols.insert( {Qt::Key_M, QChar ('m')});
//  simbols.insert( {Qt::Key_Comma, QChar ('б')});
//  simbols.insert( {Qt::Key_. QChar ('ю')});
}



void MainWindow::keyPressEvent(QKeyEvent *event)
{
     if(ui->push_start_button->isEnabled())
         return;
     QString text = ui->label_input_word->text();

     int KeyPressed = event->key();

     auto itr = simbols.find(KeyPressed);

     if((itr->second) == (words[random_index])[index])
     {
         text += (words[random_index])[index];
         ui->label_input_word->setText(text);
         ++index;
     }
     else
     {
         ++count_of_mistakes;
         ++local_mistakes;
         ui->label_mistakes->clear();
         ui->label_mistakes->setText(QString::number(count_of_mistakes));
     }

     if(words[random_index] == ui->label_input_word->text())
     {
         if(local_mistakes == 0)
         {
             exp += words[random_index].size();
         }
         else if(local_mistakes == 1)
         {
             exp += words[random_index].size() - 2;
         }
         else
         {
             exp += (words[random_index].size() / local_mistakes + 1);
         }
         ui->label_exp->clear();
         ui->label_exp->setText(QString::number(exp));

         ui->label_input_word->clear();
         srand(time(0));
         random_index = rand() % (words.size() - 1);
         ui->label_random_word->clear();
         ui->label_random_word->setText(words[random_index]);

         ++count_of_words;
         ui->label_count_words->clear();
         ui->label_count_words->setText(QString::number(count_of_words));


         index = 0;
         local_mistakes = 0;
         return;
     }
}

void MainWindow::on_push_start_button_clicked()
{
    index = 0;
    random_index = 0;
    count_of_mistakes = 0;
    local_mistakes = 0;
    exp = 0;
    count_of_words = 0;

    ui->label_input_word->clear();
    ui->label_random_word->clear();

    ui->label_mistakes->clear();
    ui->label_mistakes->setText(QString::number(0));
    ui->label_exp->clear();
    ui->label_exp->setText(QString::number(0));
    ui->label_count_words->clear();
    ui->label_count_words->setText(QString::number(0));

    emit start_loop();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::get_clock(int count)
{
    ui->label_timer->clear();
    ui->label_timer->setText(QString::number(count));
}

void MainWindow::begin_game()
{
    srand(time(0));
    ui->label_random_word->clear();
    random_index = rand() % (words.size() - 1);
    ui->label_random_word->setText(words[random_index]);

    ui->push_start_button->setEnabled(false);
}

void MainWindow::finish_game()
{
    ui->push_start_button->setEnabled(true);

    ui->label_input_word->clear();
    ui->label_random_word->clear();
}










