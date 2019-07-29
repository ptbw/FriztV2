#include "distance.h"
#include "i.h"

Distance::Distance(QObject *parent) :
    QObject(parent)
{
    _working = false;
    _abort = false;

     ranger = new vl53l0x();
}

void Distance::getDistance()
{
    int dist = 0;
    int prev = 9999;

    return;

    printf("Start distance thread\n");
    bool running = true;
    while(running)
    {
        mutex.lock();
        bool abort = _abort;
        mutex.unlock();

        if (abort)
        {
            running = false;
            break;
        }

        dist = ranger->GetDistance();
        if(dist != prev)
        {
            emit valueChanged(dist);
            printf("Distance %d \n",dist);
            prev = dist;
        }
        I::msleep(100);
    }
    mutex.lock();
    _working = false;
    mutex.unlock();

    emit finished();
}

void Distance::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    mutex.unlock();

    emit workRequested();
}

void Distance::abort()
{
    if (_working) {
        mutex.lock();
        _working = false;
        _abort = true;
        mutex.unlock();
        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
}
