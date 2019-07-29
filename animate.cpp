#include "animate.h"
#include "robot.h"
#include "i.h"
#include "speak.h"
#include <QProcess>

#define MINDISTANCE 300
#define MINANGLE 40
#define MAXANGLE 140

Animate::Animate() :
    QObject(0)
{

    _working = false;
    _abort = false;
    //_serial = serial;

    text << "Good morning! How are you?"
         << "My brain is a Raspberry Pi"
         << "My muscles are an Arduino Microcontroller"
         << "It is a nice day!"
         << "Did you have your coffee yet?"
         << "My name is Fritz!"
         << "I am a robot! Are you a robot?"
         << "I was programmed by Phil"
         << "I have 13 movable parts"
         << "I am nearly 2 years old";
}

void Animate::doWork()
{
    int dir = 1;
    int angle = MINANGLE;

    _working = false;
    _abort = false;

    int sonar = 0;
    bool running = true;
    Robot robot;
    sonar = robot.GetDistance();
    robot.SetCentre();
    I::msleep(500);


    while(running)
    {
        mutex.lock();
        sonar = robot.GetDistance();
        running = !_abort;
        mutex.unlock();
        I::msleep(200);


        if(sonar <= MINDISTANCE)
        {
            mutex.lock();
            robot.SetExpression();
            I::msleep(1000);
            SpeakMessage("Hello my name is Fritz");

            I::msleep(1000);
            QString command = "fortune cookies.txt";
            QProcess process;
            process.start(command);
            process.waitForFinished();
            QString output(process.readAllStandardOutput());
            SpeakMessage(output);
            qWarning() << output;

            mutex.unlock();
            I::msleep(2000);
        }
        else
        {
           angle = angle + (5 * dir);
           if( angle >= MAXANGLE || angle <= MINANGLE )
           {
               dir = dir * -1;
           }
           mutex.lock();
           robot.SetNeck(angle);
           mutex.unlock();
        }
     }
    robot.SetCentre();
    robot.ResetServo();

    emit done();
    emit finished();
}

void Animate::doWorkOld()
{
    Robot robot;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    int dir = 1;
    int angle = 10;
    double previous = 9999;
    //robot.SetCentre();
    //robot.SetNeck(angle);

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

        int value = (int)(qrand() % 10);
        mutex.lock();
        double sonar = 0; //robot.GetSonar();
        //qWarning() << "Sonar: " << sonar << endl;
        mutex.unlock();

        //if( sonar < 9999)
        //{
            if(sonar <= 40.0 && sonar != previous)
            {
                QString msg = text.at(value);
                SpeakMessage(msg);
                I::sleep(10);
                previous = sonar;
            }
            if(sonar > 40)
            {
               angle = angle + (5 * dir);
               if( angle >= 90 || angle <= 10 )
               {
                   dir = dir * -1;
               }
               //robot.SetNeck(angle);
               I::msleep(500);
           //}
        }
    }
    emit done();
    emit finished();
}

void Animate::SpeakMessage(QString msg)
{
    //Speak speak;
    Robot robot;

    robot.SpeakMessage(msg);
    return;
}

void Animate::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    mutex.unlock();

    emit workRequested();
}

void Animate::abort()
{
    mutex.lock();
    _working = false;
    _abort = true;
    mutex.unlock();
}


