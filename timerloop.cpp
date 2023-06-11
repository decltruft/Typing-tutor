#pragma once

#include "timerloop.h"

TimerLoop::TimerLoop(QObject *parent) : QObject(parent)
{
    count = 5;
}

void TimerLoop::begin_loop()
{
    count = 5;
    for(; count != -1; --count)
    {
        QThread::sleep(1);
        emit send_clock(count);
    }

    count = 60;
    emit start_game();


    for(; count != -1; --count)
    {
        QThread::sleep(1);
        emit send_clock(count);
    }

    emit stop_game();
}

