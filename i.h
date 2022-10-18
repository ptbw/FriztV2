#ifndef I_H
#define I_H

#include <QThread>
#include <QEventLoop>
#include <QTimer>

#define SERVO_MAX 140
#define SERVO_MIN 30

class I : public QThread
{
public:
    static void sleep(unsigned long secs){
        //QThread::sleep(secs);
        QEventLoop loop;
        QTimer::singleShot(secs * 1000 , &loop, SLOT(quit()));
        loop.exec();
    }
    static void msleep(unsigned long msecs){
        //QThread::msleep(msecs);
        QEventLoop loop;
        QTimer::singleShot(msecs, &loop, SLOT(quit()));
        loop.exec();
    }
    static void usleep(unsigned long usecs){
        //QThread::usleep(usecs);
        QEventLoop loop;
        QTimer::singleShot(usecs, &loop, SLOT(quit()));
        loop.exec();
    }
};

#endif // I_H
