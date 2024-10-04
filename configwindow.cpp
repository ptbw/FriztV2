#include "configwindow.h"
#include "ui_configwindow.h"

#include "i.h"
#include "speak.h"
#include "robot.h"

#include <QMessageBox>
#include <QThread>
#include <QImageReader>
#include <QMap>
#include <QDebug>

CalibrationData::CalibrationData()
{

}

ConfigWindow::ConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigWindow)
    //cd(new CalibrationData),
    //ss(new RobotState)
{
    ui->setupUi(this);

    main = parent;

    worker = NULL;

    robot = new Robot();

//    arduino = new QSerialPort;
//    arduino_is_available = true;

//    arduino_port_name = "/dev/ttyUSB0";

    speed = 10;
    tickCount = 0;
    
    ui->leftHorizontalEyeMin->setText(QString::number(robot->leftHorizontalEyeMin));
    ui->leftHorizontalEyeMax->setText(QString::number(robot->leftHorizontalEyeMax));
    //ui->leftHorizontalEyeTrim->setText(QString::number(robot->leftHorizontalEyeMid));
    //ui->leftHorizontalEyePin->setText(QString::number(robot->leftHorizontalEyePin));
    ui->leftVerticalEyeMin->setText(QString::number(robot->leftVerticalEyeMin));
    ui->leftVerticalEyeMax->setText(QString::number(robot->leftVerticalEyeMax));
    //ui->leftVerticalEyeTrim->setText(QString::number(robot->leftVerticalEyeMid));
    //ui->leftVerticalEyePin->setText(QString::number(robot->leftVerticalEyePin));
    ui->rightHorizontalEyeMin->setText(QString::number(robot->rightHorizontalEyeMin));
    ui->rightHorizontalEyeMax->setText(QString::number(robot->rightHorizontalEyeMax));
    //ui->rightHorizontalEyeTrim->setText(QString::number(robot->rightHorizontalEyeMid));
    //ui->rightHorizontalEyePin->setText(QString::number(robot->rightHorizontalEyePin));
    ui->rightVerticalEyeMin->setText(QString::number(robot->leftVerticalEyeMin));
    ui->rightVerticalEyeMax->setText(QString::number(robot->rightVerticalEyeMax));
    //ui->rightVerticalEyeTrim->setText(QString::number(robot->rightVerticalEyeMid));
    //ui->rightVerticalEyePin->setText(QString::number(robot->rightVerticalEyePin));
    ui->leftLipMin->setText(QString::number(robot->leftLipMin));
    ui->leftLipMax->setText(QString::number(robot->leftLipMax));
    //ui->leftLipTrim->setText(QString::number(robot->leftLipMid));
    //ui->leftLipPin->setText(QString::number(robot->leftLipPin));
    ui->rightLipMin->setText(QString::number(robot->rightLipMin));
    ui->rightLipMax->setText(QString::number(robot->rightLipMax));
    //ui->rightLipTrim->setText(QString::number(robot->rightLipMid));
    //ui->rightLipPin->setText(QString::number(robot->rightLipPin));
    ui->jawMin->setText(QString::number(robot->jawMin));
    ui->jawMax->setText(QString::number(robot->jawMax));
    //ui->jawTrim->setText(QString::number(robot->jawMid));
    //ui->jawPin->setText(QString::number(robot->jawPin));
    ui->raiseNeckMin->setText(QString::number(robot->neckTiltMin));
    ui->raiseNeckMax->setText(QString::number(robot->neckTiltMax));
    //ui->neckTiltTrim->setText(QString::number(robot->neckTiltMid));
    //ui->neckTiltPin->setText(QString::number(robot->neckTiltPin));
    ui->twistNeckMin->setText(QString::number(robot->neckTwistMin));
    ui->twistNeckMax->setText(QString::number(robot->neckTwistMax));
    //ui->neckTwistTrim->setText(QString::number(robot->neckTwistMid));
    //ui->neckTwistPin->setText(QString::number(robot->neckTwistPin));
    ui->leftEyebrowMin->setText(QString::number(robot->leftEyebrowMin));
    ui->leftEyebrowMax->setText(QString::number(robot->leftEyebrowMax));
    ui->leftEyebrowTrim->setText(QString::number(robot->leftEyebrowMid));
    //ui->leftEyebrowPin->setText(QString::number(robot->leftEyebrowMin));
    ui->rightEyebrowMin->setText(QString::number(robot->rightEyebrowMin));
    ui->rightEyebrowMax->setText(QString::number(robot->rightEyebrowMax));
    //ui->rightEyebrowTrim->setText(QString::number(robot->rightEyebrowMid));
    //ui->rightEyebrowPin->setText(QString::number(robot->rightEyebrowPin));
    ui->leftEyelidMin->setText(QString::number(robot->leftEyelidMin));
    ui->leftEyelidMax->setText(QString::number(robot->leftEyelidMax));
    //ui->leftEyelidTrim->setText(QString::number(robot->leftEyelidMid));
    //ui->leftEyelidPin->setText(QString::number(robot->leftEyelidPin));
    ui->rightEyelidMin->setText(QString::number(robot->rightEyelidMin));
    ui->rightEyelidMax->setText(QString::number(robot->rightEyelidMax));
    //ui->rightEyelidTrim->setText(QString::number(robot->rightEyelidMid));
    //ui->rightEyelidPin->setText(QString::number(robot->rightEyelidPin));


    int i;
    for (i = 0; i < 16; i++)
       currentActive[i] = false;

    fetchImage("aaah");
    fetchImage("aa");
    fetchImage("eee");
    fetchImage("fuh");
    fetchImage("i");
    fetchImage("laa");
    fetchImage("m");
    fetchImage("oh");
    fetchImage("oooh");
    fetchImage("s");

    thread = new QThread();
    worker = new Worker();

    key = new keyEnterReceiver();
    this->installEventFilter(key);

    worker->moveToThread(thread);
    connect(worker, SIGNAL(valueChanged(int)), this, SLOT(ActivateTest(int)));
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    connect(thread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);

    robot->ResetServo();
}

void ConfigWindow::fetchImage(QString filename)
{
    QImageReader reader("images/" + filename + ".png");
    const QImage newImage = reader.read();
    if (!newImage.isNull())
    {
        QPixmap pix = QPixmap::fromImage(newImage);
        imageMap.insert(filename,pix);
        ui->lblPicture->setPixmap(pix);
    }
}

ConfigWindow::~ConfigWindow()
{


    if( thread->isRunning())
    {
        worker->abort();
        thread->wait();
    }
    //delete ss;
    //delete cd;
    //delete serial;
    delete robot;
    delete ui;
    delete key;
}

void ConfigWindow::ActivateTest(const int val)
{
    robot->SetServo(ui->leftEyebrowTest->checkState(),ui->leftEyebrowMin->text().toInt(), ui->leftEyebrowMax->text().toInt(),ui->leftEyebrowPin->text().toInt(), val );
    robot->SetServo(ui->rightEyebrowTest->checkState(), ui->rightEyebrowMin->text().toInt(), ui->rightEyebrowMax->text().toInt(), ui->rightEyebrowPin->text().toInt(), (SERVO_MAX - val) + SERVO_MIN );

    robot->SetServo(ui->leftEyelidTest->checkState(), ui->leftEyelidMin->text().toInt(), ui->leftEyelidMax->text().toInt(), ui->leftEyelidPin->text().toInt(), val );
    robot->SetServo(ui->rightEyelidTest->checkState(), ui->rightEyelidMin->text().toInt(), ui->rightEyelidMax->text().toInt(), ui->rightEyelidPin->text().toInt(), val );

    robot->SetServo(ui->leftHorizontalEyeTest->checkState(), ui->leftHorizontalEyeMin->text().toInt(), ui->leftHorizontalEyeMax->text().toInt(), ui->leftHorizontalEyePin->text().toInt(), val );
    robot->SetServo(ui->rightHorizontalEyeTest->checkState(), ui->rightHorizontalEyeMin->text().toInt(), ui->rightHorizontalEyeMax->text().toInt(), ui->rightHorizontalEyePin->text().toInt(), val );

    robot->SetServo(ui->leftVerticalEyeTest->checkState(), ui->leftVerticalEyeMin->text().toInt(), ui->leftVerticalEyeMax->text().toInt(), ui->leftVerticalEyePin->text().toInt(), val );
    robot->SetServo(ui->rightVerticalEyeTest->checkState(), ui->rightVerticalEyeMin->text().toInt(), ui->rightVerticalEyeMax->text().toInt(), ui->rightVerticalEyePin->text().toInt(), (SERVO_MAX - val) + SERVO_MIN );

    robot->SetServo(ui->leftLipTest->checkState(), ui->leftLipMin->text().toInt(), ui->leftLipMax->text().toInt(), ui->leftLipPin->text().toInt(), val );
    robot->SetServo(ui->rightLipTest->checkState(), ui->rightLipMin->text().toInt(), ui->rightLipMax->text().toInt(), ui->rightLipPin->text().toInt(), (SERVO_MAX - val) + SERVO_MIN );

    robot->SetServo(ui->jawTest->checkState(), ui->jawMin->text().toInt(), ui->jawMax->text().toInt(), ui->jawPin->text().toInt(), val );
    robot->SetServo(ui->twistNeckTest->checkState(), ui->twistNeckMin->text().toInt(), ui->twistNeckMax->text().toInt(), ui->twistNeckPin->text().toInt(), val );
    robot->SetServo(ui->raiseNeckTest->checkState(), ui->raiseNeckMin->text().toInt(), ui->raiseNeckMax->text().toInt(), ui->raiseNeckPin->text().toInt(), val );

    QString msg = QString::number(val) + "/" + QString::number((SERVO_MAX - val) + SERVO_MIN);
    ui->textTest->setText(msg);
}


void ConfigWindow::DeactivateTest()
{
    worker->abort();
    thread->wait(); // If the thread is not running, this will immediately return.
    ui->btnRunTests->setText("Run Tests");
    robot->ResetServo();
}

void ConfigWindow::on_btnCancelSave_accepted()
{

}

void ConfigWindow::on_btnCancelSave_rejected()
{

}

void ConfigWindow::on_pushButton_clicked()
{   
    //int version = TestSerial();

    int version = 0; //serial->GetVersion();

    if(version == -1)
        QMessageBox::warning(this, "Port error","Couldn't find the Arduino!");
    else if(version == -2)
        QMessageBox::warning(this, "Port error","Fritz not found");
    else if(version < 4 )
        QMessageBox::warning(this, "Port error","Fritz found but firmware version is too old!");
    else
        QMessageBox::information(this, "Serial Port","Fritz found");


}

int ConfigWindow::GetVersion()
{
    int version = 0; //serial->TestSerial();
    return version;
}


void ConfigWindow::SetServo(int pin, float value, int max, int min, int trim /* = 0 */, bool inverted /*= false*/)
{
    int val;
//    if (inverted)
//        val = (short)(((1.0f - value) * (max - min)) + min + trim);
//    else
//        val = (short)((value * (max - min)) + min + trim);

    if(inverted)
        val = (180 - value) + trim;
    else
        val = value + trim;

    if (val > max) val = max;
    if (val < min) val = min;

    SetServo(pin, val);

}

void ConfigWindow::SetServo(int pin, int value)
{
    robot->SetServo(pin, value);
}

void ConfigWindow::on_btnRunTests_clicked()
{
    if( thread->isRunning())
    {
        worker->abort();
        thread->wait();
        ui->btnRunTests->setText("Run Tests");
        robot->ResetServo();
    }
    else
    {
        worker->requestWork();
        ui->btnRunTests->setText("Stop");
     }
}


void ConfigWindow::on_btnTestSpeech_clicked()
{
    Speak speak;
    speak.TextToSpeech("Your reasoning is excellent. It's only your basic assumptions that are wrong.");
}

void ConfigWindow::on_btnTestSpeech_2_clicked()
{
    Speak speak;
    speak.TextToWave("Your reasoning is excellent -- it's only your basic assumptions that are wrong.",1);
    speak.PlayWave(1);
}


void ConfigWindow::on_btnTestSpeech_3_clicked()
{
    Speak speak;
    speak.PlayWave(1);
}

void ConfigWindow::on_btnTestSpeech_4_clicked()
{

    int counter = 1;
    QString msg = "Your reasoning is excellent. It's only your basic assumptions that are wrong.";
    if( ui->textToSay->text() != "" )
        msg = ui->textToSay->text();

    Speak speak;
    QStringList words = msg.split(QLatin1Char(' '),Qt::KeepEmptyParts);
    QStringListIterator wordit(words);
    while (wordit.hasNext())
    {
        QString word = wordit.next();
        speak.TextToWave(word, counter++ );
    }

    counter = 1;
    QStringListIterator wordit2(words);
    while (wordit2.hasNext())
    {
        QString word = wordit2.next();
        QStringList phons = speak.TextToPhon(word);
        speak.PlayWave(counter++);

        qDebug() << "Word: " << word;
        QStringListIterator phonit(phons);
        while (phonit.hasNext())
        {
            QString phon = phonit.next();
            if(phon != " ")
            {
                qDebug() << "Phonme: " << phon;
                QString shape = speak.GetMouthShape(phon);
                QPixmap pix = imageMap[shape];
                ui->lblPicture->setPixmap(pix);
                ui->lblPicture->repaint();
                I::msleep(90);
            }            
        }
        I::msleep(4 * phons.count());
    }
    QPixmap pix = imageMap["s"];
    ui->lblPicture->setPixmap(pix);
}

void ConfigWindow::on_btnTestSpeech_5_clicked()
{    
    QString msg = "Your reasoning is excellent. It's only your basic assumptions that are wrong.";
    if( ui->textToSay->text() != "" )
        msg = ui->textToSay->text();


    Speak speak;
    QStringList words= msg.split(" ",QString::SplitBehavior::KeepEmptyParts);
    QStringListIterator wordit(words);
    while (wordit.hasNext())
    {
        QString word = wordit.next();
        QStringList phons = speak.TextToPhon(word);
        speak.TextToSpeech(word);

        qDebug() << word << " " << phons << Qt::endl;
        QStringListIterator iterator(phons);
        while (iterator.hasNext())
        {
            QString phon = iterator.next();
            if(phon != " ")
            {
                QString shape = speak.GetMouthShape(phon);
                QPixmap pix = imageMap[shape];
                ui->lblPicture->setPixmap(pix);
                ui->lblPicture->repaint();
                robot->SetMouth(shape);
                I::msleep(90);
            }
        }
        I::msleep(4 * phons.count());

    }
    QPixmap pix = imageMap["sss"];
    ui->lblPicture->setPixmap(pix);

}

void ConfigWindow::SpeakMessage(QString msg)
{
    robot->SpeakMessage(msg);
}


void ConfigWindow::on_btnTestSonar_clicked()
{
    int distance = robot->GetDistance();
    QString msg = QString::number(distance);
    qDebug() << "Dist: " << msg;
    ui->textSonar->setText(msg);
}

void ConfigWindow::ShowLips(QString shape)
{
    QPixmap pix = imageMap[shape];
    ui->lblPicture->setPixmap(pix);
    ui->lblPicture->repaint();
}

void ConfigWindow::SpeakPhoneme(QString shape, QString phoneme)
{
    ShowLips(shape);
    robot->SpeakPhoneme(shape,phoneme);
}

void ConfigWindow::on_btnaaah_clicked()
{
    SpeakPhoneme("aaah","[['a]]");
}

void ConfigWindow::on_btnaa_clicked()
{
    SpeakPhoneme("aa","[['A:]]");
}

void ConfigWindow::on_btni_clicked()
{
    SpeakPhoneme("i","[['E]]");
}

void ConfigWindow::on_btnlaa_clicked()
{
    SpeakPhoneme("laa","[['eI]]");
}

void ConfigWindow::on_btnsss_clicked()
{
    SpeakPhoneme("s","[['3:]]");
}

void ConfigWindow::on_btneee_clicked()
{
    SpeakPhoneme("eee","[['i:]]");
}

void ConfigWindow::on_btnoh_clicked()
{
    SpeakPhoneme("oh","[['0]]");
}

void ConfigWindow::on_btnoooh_clicked()
{
    SpeakPhoneme("oooh","[['O]]");
}

void ConfigWindow::on_btnfuh_clicked()
{
    SpeakPhoneme("fuh","[[f']]");
}

void ConfigWindow::on_btnmmm_clicked()
{
    SpeakPhoneme("m","[[m'V]]");
}



void ConfigWindow::on_btnSetPosition_clicked()
{
   int pinNumber = ui->pinNumber->toPlainText().toInt();
   robot->SetServo(pinNumber,ui->servoPosition->value());
}

void ConfigWindow::on_servoPosition_valueChanged(int value)
{
    ui->lbServoPosition->setText(QString::number(value));
}

void ConfigWindow::on_btnSetExpression_clicked()
{
    // leftHorizontalEye leftVerticalEye rightHorizontalEye rightVerticalEye leftEyebrow rightEyebrow rightEyelid leftEyelid leftLip rightLip jaw neckTilt neckTwist
    // Check each "center" text box and set the servo position
    robot->SetServo(7,(ui->leftHorizontalEyeTrim->text().toInt()));
    robot->SetServo(5,(ui->leftVerticalEyeTrim->text().toInt()));

    robot->SetServo(8,(ui->rightHorizontalEyeTrim->text().toInt()));
    robot->SetServo(6,(ui->rightVerticalEyeTrim->text().toInt()));

    robot->SetServo(4,(ui->leftLipTrim->text().toInt()));
    robot->SetServo(3,(ui->rightLipTrim->text().toInt()));

    robot->SetServo(2,(ui->jawTrim->text().toInt()));

    //robot->SetServo(8,(ui->raiseNeckTrim->text().toInt()));
    robot->SetServo(0,(ui->twistNeckTrim->text().toInt()));

    robot->SetServo(11,(ui->leftEyebrowTrim->text().toInt()));
    robot->SetServo(12,(ui->rightEyebrowTrim->text().toInt()));

    robot->SetServo(9,(ui->leftEyelidTrim->text().toInt()));
    robot->SetServo(10,(ui->rightEyelidTrim->text().toInt()));
    I::msleep(2000);
    robot->ResetServo();
}
