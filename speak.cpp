#include "speak.h"

#include <QProcess>
#include <QList>
#include <QDebug>

 Speak::Speak()
{

     // See https://en.wikipedia.org/wiki/Help:Pronunciation_respelling_key

    speaking = false;
    /* ' = pause */

    /* Vowel sounds */
    phono ah;              // ash
    ah.ipa = "æ";
    ah.lips = "aaah";
    phonos.append(ah);

    phono a;               // all
    a.ipa = "ɔː";
    a.lips = "oh";
    phonos.append(a);

    phono aa;              // father
    aa.ipa = "ɑː";
    aa.lips = "aa";
    phonos.append(aa);

    phono e;               // better
    e.ipa = "ɛ";
    e.lips = "i";
    phonos.append(e);

    phono ay;              // day
    ay.ipa = "eɪ";
    ay.lips = "laa";
    phonos.append(ay);

    phono ea;              // earth
    ea.ipa = "ɜː";
    ea.lips = "sss";
    phonos.append(ea);

    phono i;               // drink
    i.ipa = "ɪ";
    i.lips = "i";
    phonos.append(i);

    phono ee;              // eat
    ee.ipa = "iː";
    ee.lips = "eee";
    phonos.append(ee);

    phono o;
    o.ipa = "ɒ";          // top
    o.lips = "oh";
    phonos.append(o);

    phono ou;
    ou.ipa = "ɔː";         // four
    ou.lips = "oooh";
    phonos.append(ou);

    phono oo;
    oo.ipa = "ʊ";         // foot
    oo.lips = "oh";
    phonos.append(oo);

    phono ooo;
    ooo.ipa = "uː";        // goose
    ooo.lips = "oooh";
    phonos.append(ooo);

    phono od;
    od.ipa = "ʌ";         // blood
    od.lips = "oh";
    phonos.append(od);

    phono on;
    on.ipa = "əʊ";         // bone
    on.lips = "fuh";
    phonos.append(on);

    phono ow;
    ow.ipa = "aʊ";        // cow
    ow.lips = "laa";
    phonos.append(ow);

    phono ai;
    ai.ipa = "eɪ";         // nail
    ai.lips = "fuh";
    phonos.append(ai);

    phono ii;
    ii.ipa = "aɪ";         // bite
    ii.lips = "i";
    phonos.append(ii);

    phono er;
    er.ipa = "iə";         // ear
    er.lips = "eee";
    phonos.append(er);

    phono b;
    b.ipa = "b";         // b
    b.lips = "mmm";
    phonos.append(b);

    phono p;
    p.ipa = "p";         // pee
    p.lips = "mmm";
    phonos.append(p);

    phono m;
    m.ipa = "m";         // mmm
    m.lips = "mmm";
    phonos.append(m);

    phono f;
    f.ipa = "f";         // fuh
    f.lips = "fuh";
    phonos.append(f);

    phono v;
    v.ipa = "v";         // vuh
    v.lips = "fuh";
    phonos.append(v);

    phono sh;
    v.ipa = "ʃ";         // vuh
    v.lips = "fuh";
    phonos.append(v);


}

 QString Speak::GetMouthShape(QString phon)
 {
     //qDebug() << "Check" << phon;
     QVectorIterator<phono> i(phonos);
     while( i.hasNext())
     {
        phono p = i.next();
        if( phon == p.ipa )
        {
            if(p.lips == "")
            {
                qDebug() << phon << " Bad Mapping" << Qt::endl;
                return "aa";
            }
            return p.lips;
        }
     }

     return "s";
 }

 QStringList Speak::TextToPhon(QString text)
 {
     QString command = "espeak -s160 -k20 -ven-uk-rp -q --sep=_ --ipa ";
     command = command.append(text);
     //qDebug() << "Command: " << command << Qt::endl;

     /*
     QString command = "espeak";
     QStringList args = {"-s160" ," -k20" ,"-ven-uk-rp", "-q", "--ipa", text};

     qDebug() << "Command: " << command << args << Qt::endl;

     QProcess process;
     process.start(command,args);     
     process.waitForFinished();     
     */
     QProcess process;
     process.start(command);
     process.waitForFinished();

     QString result(process.readAllStandardOutput());

     //qDebug() << "Result before: " << result;
     result.remove("\n");
     result.replace("ˈ"," ");
     result.replace(" ","_ _");
     //qDebug() << "Result after: " << result;

     QStringList results = result.split("_",Qt::SkipEmptyParts);
     return results;
 }

int Speak::TextToSpeech(QString text)
{        
    TextToWave(text,1);
    PlayWave(1);
    return 0;

//    QString command = "espeak -s130 -k20 -ven-uk-rp --stdout  ";
//    command.append('"').append(text).append('"').append(" | aplay");

//    QProcess process;
//    process.startDetached(command);
//    return 0;
}


int Speak::TextToWave(QString text, int counter)
{
// rev 1
//    QString command = "espeak -s150 -k20 -ven-uk-rp -w /tmp/out.wav ";
//    command.append('"').append(text).append('"');

// rev 2
//      QString command = "espeak";
//      QString arg;
//      arg = arg.append('"').append(text).append('"');
//      QStringList args = {"-s150","-k20","-ven-uk-rp","-w /tmp/out.wav", arg };

// rev 3
//    QProcess process;
//    process.setStandardOutputFile(QProcess::nullDevice());
//    process.setStandardErrorFile(QProcess::nullDevice());
//    process.start(command,args);
//    process.waitForFinished();

//    QProcess process1;
//    QProcess process2;

//    QString command1 = "echo";
//    QString arg1;
//    arg1 = arg1.append('"').append(text).append('"');
//    QStringList args1 = {arg1};

//    QString command2 = "/home/philw/piper/piper/piper";
//    QStringList args2 = {"--model /home/philw/piper/piper/en_GB-alan-medium.onnx", "--output_file /tmp/out.wav"};
//    process1.setStandardOutputProcess(&process2);

//    process1.start(command1, args1);
//    process2.start(command2, args2);
//    process2.setProcessChannelMode(QProcess::ForwardedChannels);

//    // Wait for it to start
//    if(!process1.waitForStarted())
//        return 0;

//    bool retval = false;
//    QByteArray buffer;
//    while ((retval = process2.waitForFinished()))
//        buffer.append(process2.readAll());

// rev 4
//    // /bin/sh -c 'echo Fritz | /home/philw/piper/piper/piper --model /home/philw/piper/piper/en_GB-alan-medium.onnx --output_file /tmp/out.wav'
//    QString command = "/bin/sh";
//    QString arg1;
//    arg1 = arg1.append("-c");
//    QString arg2;
//    arg2 = arg2
//            .append("echo ")
//            .append(text)
//            .append(" | /home/philw/piper/piper/piper ")
//            .append("--model /home/philw/piper/piper/en_GB-alan-medium.onnx --output_file /tmp/out.wav");

//    QStringList args = {arg1, arg2};

//    qDebug() << "Command" << command << " " << arg1 << " "<< arg2;

//    QProcess process;
//    process.setStandardOutputFile(QProcess::nullDevice());
//    process.setStandardErrorFile(QProcess::nullDevice());
//    process.start(command,args);
//    process.waitForFinished();

// rev5
//  curl -G --data-urlencode 'text=This is a test.' -o /tmp/out.wav 'localhost:5000'
        text = text.append(' ');
        QString command = "curl";
        QString arg1 ="-G";
        QString arg2 ="--data-urlencode";
        QString arg3;
        arg3 = arg3.append("text=").append(text);
        QString arg4 = "-o";
        QString arg5 = QString("/tmp/out%1.wav").arg(counter, 2, 10, QLatin1Char('0'));
        QString arg6 = "localhost:5000";

        QStringList args = {arg1,arg2,arg3,arg4,arg5,arg6};

        // qDebug() << "Command" << command << " " << arg1 << " "<< arg2 << " " << arg3 << " " << arg4 << " "<< arg5;

        QProcess process;
        process.setStandardOutputFile(QProcess::nullDevice());
        process.setStandardErrorFile(QProcess::nullDevice());
        process.start(command,args);
        process.waitForFinished();
    return 0;
}

int Speak::PlayWave(int counter)
{     
    QString command = "aplay";
    QProcess process;
    QString arg1 = QString("/tmp/out%1.wav").arg(counter, 2, 10, QLatin1Char('0'));
    QStringList args = {"-q",arg1};
    process.setStandardOutputFile(QProcess::nullDevice());
    process.setStandardErrorFile(QProcess::nullDevice());
    //process.start(command,args);
    //process.waitForFinished();
    process.startDetached(command,args);
    return 0;
}
