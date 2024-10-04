#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "configwindow.h"
#include "aboutbox.h"
#include "robot.h"
#include "speak.h"
#include "i.h"

#include <QMessageBox>
//#include <QtSerialPort/QSerialPort>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //serial = new Serial();

    thread = new QThread();
    animate = new Animate();


//    ranger = new Distance();
//    ranger->moveToThread(thread);

//    connect(ranger, SIGNAL(valueChanged(int)), this, SLOT(ValueChanged(int)));
//    connect(ranger, SIGNAL(workRequested()), thread, SLOT(start()));
//    connect(thread, SIGNAL(started()), ranger, SLOT(getDistance()));
//    connect(ranger, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);
//    ranger->requestWork();
    animationRunning = false;    
    on_volumeSlider_valueChanged(75);
}

MainWindow::~MainWindow()
{
    if(animationRunning)
    {
        qDebug() << "Animation stopping";
        ui->btnAnimate->setText("Animate");
        animationRunning = false;
        animate->abort();
    }    
    //ranger->abort();
    thread->wait();

    delete ui;
}

void MainWindow::on_Stop()
{
    ui->btnAnimate->setText("Animate");
}

void MainWindow::on_actionConfig_triggered()
{
    if(animationRunning) return;

    ConfigWindow w;
    w.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    if(animationRunning) return;

    AboutBox w;
    w.exec();
}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionQuit_triggered()
{    
    if(animationRunning)
    {
        qDebug() << "Animation stopping";
        ui->btnAnimate->setText("Animate");
        animationRunning = false;
        animate->abort();
    }

    Robot robot;
    robot.SetExpression("Neutral");
    robot.ResetServo();
    QApplication::quit();
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    if(animationRunning) return;

    Robot robot;
    robot.SetExpression(arg1);    
}

/*
void MainWindow::OldSpeakMessage(QString msg)
{
    if(animationRunning) return;

    msg = msg.replace("\n","");

    Robot robot;

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
                //I::msleep(90);
            }
        }
        I::msleep(4 * phons.count());
    }
    robot.SetExpression("Normal");
}
*/

void MainWindow::SpeakMessage(QString msg)
{
    if(animationRunning) return;

    msg = msg.replace("\n","");

    Robot robot;
    int counter = 1;

    Speak speak;
    QStringList words= msg.split(QLatin1Char(' '),Qt::KeepEmptyParts);
    QStringListIterator wordit(words);
    while (wordit.hasNext())
    {
        QString word = wordit.next();
        speak.TextToWave(word, counter++ );
    }

    counter = 1;
    //words= msg.split(" ",QString::SplitBehavior::KeepEmptyParts);
    QStringListIterator wordit2(words);
    while (wordit2.hasNext())
    {
        QString word = wordit2.next();
        QStringList phons = speak.TextToPhon(word);
        speak.PlayWave(counter++);
        I::msleep(10);

        //qDebug() << word << " " << phons << Qt::endl;
        QStringListIterator iterator(phons);
        while (iterator.hasNext())
        {
            QString phon = iterator.next();
            QString shape = speak.GetMouthShape(phon);
            if(phon != " ")
            {
                robot.SetMouth(shape);
                I::msleep(80);              // was 90
            }
        }
        I::msleep(7 * phons.count());       // Was 4
    }

    robot.SetExpression("Normal");
}

void MainWindow::on_btnHello_clicked()
{
    if(animationRunning) return;

    QString msg = "Hello My Name is Fritz";
    SpeakMessage(msg);
}

void MainWindow::on_btnAsk_clicked()
{
    if(animationRunning) return;

    QString msg = "May I tell your fortune?";
    SpeakMessage(msg);
}

void MainWindow::on_btnFortune_clicked()
{
    if(animationRunning) return;

    QString command("/usr/games/fortune");

    QProcess process;
    QStringList args = {"/usr/share/games/cookies.txt"};
    process.start(command,args,QIODevice::ReadWrite);
    process.waitForFinished();
    QString output(process.readAllStandardOutput());

    if(ui->cbSaveFortune->checkState()) {
        ui->textToSay->setPlainText(output);
    }

    qDebug() << "Fortune: " << output;
    SpeakMessage(output);
}

void MainWindow::on_btnOkBye_clicked()
{
    if(animationRunning) return;
    QString msg = "Ok. Goodbye";
    SpeakMessage(msg);
}

void MainWindow::on_btnThanks_clicked()
{
    if(animationRunning) return;
    QString msg = "Thank you. Goodbye";
    SpeakMessage(msg);
}

void MainWindow::on_btnLeft_clicked()
{
    if(animationRunning) return;
    //SetState(int n_leftHorizontalEye, int n_leftVerticalEye, int n_rightHorizontalEye, int n_rightVerticalEye, int n_leftEyebrow, int n_rightEyebrow, int n_rightEyelid, int n_leftEyelid, int n_leftLip, int n_rightLip, int n_jaw, int n_neckTilt, int n_neckTwist);
    Robot robot;
    //robot.SetState(40, -1, 40, -1, 30, 70, 100, 100, 50, 50, 50, -1, 10);
    robot.SetLeft();
}

void MainWindow::on_btnCentre_clicked()
{
    if(animationRunning) return;
    Robot robot;
    //robot.SetState(40, -1, 40, -1, 50, 50, 100, 100, 50, 50, 50, -1, 50);
    robot.SetCentre();
}

void MainWindow::on_btnRight_clicked()
{
    Robot robot;
    //robot.SetState(40, -1, 40, -1, 30, 70, 100, 100, 50, 50, 50, -1, 90);
    robot.SetRight();
}

void MainWindow::on_btnAnimate_clicked()
{
     if(animationRunning)
     {
         qDebug() << "Animation stopping";
         ui->btnAnimate->setText("Animate");
         animationRunning = false;
         animate->abort();
     }
     else
     {
         qDebug() << "Animation starting";
         ui->btnAnimate->setText("Stop Animate");
         animationRunning = true;
         animate->doWorkOld();  // Do not move head
         //animate->doWork();
     }   
}


void MainWindow::on_volumeSlider_valueChanged(int value)
{
    QString command = "amixer";
    QStringList args = {"sset","'Speaker'",QString::number(value)};

    QProcess process;
    process.start(command,args);
    process.waitForFinished();

    ui->currentVolume->setText(QString::number(value));
}

void MainWindow::on_btnSpeak_clicked()
{
    if(animationRunning) return;

    QString msg = "Hello. Pleased to meet you!";
    if( ui->textToSay->toPlainText() != "" )
        msg = ui->textToSay->toPlainText();

    SpeakMessage(msg);
}

