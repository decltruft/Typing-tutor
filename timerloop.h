#ifndef TIMERLOOP_H
#define TIMERLOOP_H

#include <QObject>
#include <QThread>
#include "mainwindow.h"

class MainWindow;

class TimerLoop : public QObject
{
    Q_OBJECT
public:
    explicit TimerLoop(QObject *parent = 0);
    ~TimerLoop() = default;

signals:
    void send_clock(int count);
    void start_game();
    void stop_game();

public slots:
    void begin_loop();

private:
    unsigned int count;
};

#endif // TIMERLOOP_H
