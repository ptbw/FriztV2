#include "speak.h"

#include <QProcess>
#include <QList>
#include <QDebug>

 Speak::Speak()
{
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
    a.lips = "aa";
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

     return "sss";
 }

 QStringList Speak::TextToPhon(QString text)
 {
     QString command = "espeak -s160 -k20 -ven-uk-rp -q --ipa=1 ";  // Was ipa=3 but stopped working at some point and was replaced with _
     command.append('"').append(text).append('"');

     QStringList args;

     QProcess process;
     process.start(command,args);
     process.waitForFinished();
     QString result(process.readAllStandardOutput());
     result.remove("\n");
     result.replace("ˈ"," ");
     result.replace(" ","_ _");     
     QStringList results = result.split("_",QString::SkipEmptyParts);
     return results;
 }


int Speak::TextToSpeech(QString text)
{    
    qDebug() << text;
    TextToWave(text);
    PlayWave();
    return 0;

//    QString command = "espeak -s130 -k20 -ven-uk-rp --stdout  ";
//    command.append('"').append(teGetMouthShapext).append('"').append(" | aplay");

//    QProcess process;
//    process.startDetached(command);
//    return 0;
}

int Speak::TextToWave(QString text)
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
    // /bin/sh -c 'echo Fritz | /home/philw/piper/piper/piper --model /home/philw/piper/piper/en_GB-alan-medium.onnx --output_file /tmp/out.wav'
    QString command = "/bin/sh";
    QString arg1;
    arg1 = arg1.append("-c");
    QString arg2;
    arg2 = arg2
            .append("echo ")
            .append(text)
            .append(" | /home/philw/piper/piper/piper ")
            .append("--model /home/philw/piper/piper/en_GB-alan-medium.onnx --output_file /tmp/out.wav");

    QStringList args = {arg1, arg2};

    qDebug() << "Command" << command << " " << arg1 << " "<< arg2;

    QProcess process;
    process.setStandardOutputFile(QProcess::nullDevice());
    process.setStandardErrorFile(QProcess::nullDevice());
    process.start(command,args);
    process.waitForFinished();


    return 0;
}

int Speak::PlayWave()
{
    doWork();
    return 0;
}

void Speak::doWork()
{
    QString command = "aplay";
    QProcess process;
    QStringList args = {"-q","/tmp/out.wav"};
    process.setStandardOutputFile(QProcess::nullDevice());
    process.setStandardErrorFile(QProcess::nullDevice());
    process.start(command,args);
    process.waitForFinished();
}
