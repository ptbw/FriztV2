#include "i.h"
#include "worker.h"

Worker::Worker(QObject *parent) :
    QObject(parent)
{
    _working = false;
    _abort = false;
}

void Worker::doWork()
{
    bool running = true;
    while(running)
    {
        for (int i = 20; i < 160; i = i + 2)
        {
            mutex.lock();
            bool abort = _abort;
            mutex.unlock();

            if (abort)
            {
                running = false;
                break;
            }

            //QEventLoop loop;
            //QTimer::singleShot(250, &loop, SLOT(quit()));
            //loop.exec();
            I::msleep(100);

            emit valueChanged(i);
        }

        for (int i = 160; i > 20; i = i - 2)
        {
            mutex.lock();
            bool abort = _abort;
            mutex.unlock();

            if (abort)
            {
                running = false;
                break;
            }

            //QEventLoop loop;
            //QTimer::singleShot(250, &loop, SLOT(quit()));
            //loop.exec();
            I::msleep(100);


            emit valueChanged(i);
        }

    }
    mutex.lock();
    _working = false;
    mutex.unlock();

    emit finished();
}

void Worker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    mutex.unlock();

    emit workRequested();
}

void Worker::abort()
{
    if (_working) {
        mutex.lock();
        _working = false;
        _abort = true;
        mutex.unlock();
        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
}
