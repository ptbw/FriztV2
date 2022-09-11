#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "configwindow.h"
#include "aboutbox.h"
#include "robot.h"
#include "speak.h"
#include "i.h"

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
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
}

MainWindow::~MainWindow()
{
    if(animationRunning)
    {
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
    ConfigWindow w;
    w.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutBox w;
    w.exec();
}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionQuit_triggered()
{
    Robot robot;
    robot.ResetServo();

    if(animationRunning)
    {
        ui->btnAnimate->setText("Animate");
        animationRunning = false;
        animate->abort();
    }
    QApplication::quit();
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    Robot robot;
    robot.SetExpression(arg1);
    I::msleep(5000); 
}

void MainWindow::SpeakMessage(QString msg)
{
    Robot robot;
    robot.SpeakMessage(msg);
}

void MainWindow::on_btnHello_clicked()
{
    QString msg = "Hello,  My Name is Fritz";
    SpeakMessage(msg);
}

void MainWindow::on_btnAsk_clicked()
{
    QString msg = "May I tell your fortune?";
    SpeakMessage(msg);
}

void MainWindow::on_btnFortune_clicked()
{
    QString command("speakme");

    QProcess process;
    process.start(command);
    process.waitForFinished();

    QString output(process.readAllStandardOutput());
    printf("%s \n",output.toStdString().c_str());
    SpeakMessage(output);
}

void MainWindow::on_btnOkBye_clicked()
{
    QString msg = "Ok. Goodbye";
    SpeakMessage(msg);
}

void MainWindow::on_btnThanks_clicked()
{
    QString msg = "Thankyou. Goodbye";
    SpeakMessage(msg);
}

void MainWindow::on_btnLeft_clicked()
{
    //SetState(int n_leftHorizontalEye, int n_leftVerticalEye, int n_rightHorizontalEye, int n_rightVerticalEye, int n_leftEyebrow, int n_rightEyebrow, int n_rightEyelid, int n_leftEyelid, int n_leftLip, int n_rightLip, int n_jaw, int n_neckTilt, int n_neckTwist);
    Robot robot;
    //robot.SetState(40, -1, 40, -1, 30, 70, 100, 100, 50, 50, 50, -1, 10);
    robot.SetLeft();
}

void MainWindow::on_btnCentre_clicked()
{
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
         ui->btnAnimate->setText("Animate");
         animationRunning = false;
         animate->abort();
     }
     else
     {
         ui->btnAnimate->setText("Stop Animate");
         animationRunning = true;
         animate->doWork();
     }
}

void MainWindow::ValueChanged(const int val)
{

}
