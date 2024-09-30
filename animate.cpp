#include "animate.h"
#include "robot.h"
#include "i.h"
#include "speak.h"
#include <QProcess>

#define MINDISTANCE 500
#define MINANGLE 60  // 80, 110, 140
#define MAXANGLE 120
#define STEP 2


enum ConvState {
    Idle,
    Hello,
    WhatsYourName,
    PleaseToMeetYou,
    AskFortune,
    ReplyFortune,
    GoodBye,
    Exit
};

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

    //_working = false;
    _abort = false;

    int sonar = 0;
    ConvState state = Idle;
    bool running = true;
    Robot robot;
    sonar = robot.GetDistance();
    //qDebug() << "Distance: " << sonar;
    MoveNeck(robot,angle,angle);
    I::msleep(500);

    // Neutral expression
    robot.SetExpression("Neutral");

    while(running)
    {

        sonar = robot.GetDistance();
        //qDebug() << "Distance: " << sonar;
        mutex.lock();
        running = !_abort;
        mutex.unlock();
        I::msleep(500);


        if(sonar >= 0 && sonar <= MINDISTANCE && state < GoodBye)
        {

            state = (ConvState)(state + 1);
        }
        else
        {
            if(state > Hello)
            {
               SpeakMessage(robot, "Good bye");
               I::msleep(1000);
            }
            state = Idle;
            int previous = angle;
            angle = angle + (STEP * dir);
            if( angle >= MAXANGLE || angle <= MINANGLE )
            {
               dir = dir * -1;
            }
            MoveNeck(robot,angle,previous);
        }
        if(state == Hello)
        {
            SpeakMessage(robot, "Hello my name is Fritz");
            I::msleep(1000);            
        }
        if(state == WhatsYourName)
        {
            SpeakMessage(robot, "What is your name?");
            I::msleep(2000);
        }
        if(state == PleaseToMeetYou)
        {
            SpeakMessage(robot, "Pleased to meet you");
            I::msleep(2000);
        }
        if(state == AskFortune)
        {
            SpeakMessage(robot, "Can I tell your fortune");
            I::msleep(2000);
        }
        if(state == ReplyFortune)
        {
            SpeakFortune(robot);
            I::msleep(2000);
        }
        if(state == GoodBye)
        {
           SpeakMessage(robot, "Good bye");
           I::msleep(1000);
        }
    }
    robot.SetExpression("Neutral");
    I::msleep(2000);

    emit done();
    emit finished();
}

void Animate::doWorkOld()
{
    int dir = 1;
    int angle = MINANGLE;

    //_working = false;
    _abort = false;

    int sonar = 0;
    ConvState state = Hello;
    bool running = true;
    Robot robot;

    // Neutral expression
    robot.SetExpression("Neutral");

    while(state != Exit)
    {
        if(state == Hello)
        {
            SpeakMessage(robot, "Hello my name is Fritz");
            I::msleep(1000);
        }
        if(state == WhatsYourName)
        {
            SpeakMessage(robot, "What is your name?");
            I::msleep(2000);
        }
        if(state == PleaseToMeetYou)
        {
            SpeakMessage(robot, "Pleased to meet you");
            I::msleep(2000);
        }
        if(state == AskFortune)
        {
            SpeakMessage(robot, "Can I tell your fortune");
            I::msleep(2000);
        }
        if(state == ReplyFortune)
        {
            SpeakFortune(robot);
            I::msleep(2000);
        }
        if(state == GoodBye)
        {
           SpeakMessage(robot, "Good bye");
           I::msleep(1000);
        }
        state = (ConvState)(state + 1);
    }
    robot.SetExpression("Neutral");
    I::msleep(2000);

    emit done();
    emit finished();
}

void Animate::MoveNeck(Robot robot,int angle,int previous)
{

    //qDebug() << "Angle: " << angle << " Prev: " << previous;
    robot.SetNeck(angle);

//    if(angle > previous)
//    {
//        int a = previous;
//        while( a <= angle)
//        {
//            a = a + 1 + ((angle - a)/2);
//            qDebug() << "SetNeck: " << a ;
//            robot.SetNeck(a);
//        }
//     }
//    else
//    {
//        int a = previous;
//        while( a >= angle)
//        {
//            a = a - 1 - ((a - angle)/2);
//            qDebug() << "SetNeck: " << a ;
//            robot.SetNeck(a);
//        }
//    }
}

void Animate::SpeakFortune(Robot robot)
{
    QString command("/usr/games/fortune");

    QProcess process;
    QStringList args = {"/usr/share/games/cookies.txt"};
    process.start(command,args,QIODevice::ReadWrite);
    process.waitForFinished();
    QString output(process.readAllStandardOutput());

    qDebug() << "Fortune: " << output;
    SpeakMessage(robot, output);
}

void Animate::SpeakMessage(Robot robot, QString msg)
{
    Speak speak;
    QStringList words= msg.split(" ",QString::SplitBehavior::KeepEmptyParts);
    QStringListIterator wordit(words);
    while (wordit.hasNext())
    {
        QString word = wordit.next();
        QStringList phons = speak.TextToPhon(word);
        speak.TextToSpeech(word);
        //qDebug() << word << " " << phons << Qt::endl;
        QStringListIterator iterator(phons);
        while (iterator.hasNext())
        {
            QString phon = iterator.next();
            QString shape = speak.GetMouthShape(phon);
            if(phon != " ")
            {
                robot.SetMouth(shape);
                I::msleep(90);
            }
        }
        I::msleep(4 * phons.count());
    }
}

void Animate::requestWork()
{
    mutex.lock();
    //_working = true;
    _abort = false;
    mutex.unlock();

    emit workRequested();
}

void Animate::abort()
{
    qDebug() << "Animation aborting";
    mutex.lock();
    _abort = true;
    mutex.unlock();
    qDebug() << "Animation aborted";
}


