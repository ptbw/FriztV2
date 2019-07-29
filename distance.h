#ifndef DISTANCE_H
#define DISTANCE_H

#include <QThread>
#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QTimer>

#include "vl53l0x.h"

class Distance : public QObject
{
    Q_OBJECT
public:
    explicit Distance(QObject *parent = 0);
    void requestWork();
    void abort();

private:
    bool _working;
    bool _abort;
    QMutex mutex;

    vl53l0x * ranger;

signals:
    void workRequested();
    void valueChanged(int);
    void finished();

public slots:
    void getDistance();
};

#endif // DISTANCE_H
