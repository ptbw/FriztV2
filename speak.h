#ifndef SPEAK_H
#define SPEAK_H

#include <QString>
#include <QVector>

class phono
{
public:
    QString ipa;
    QString lips;
};

class Speak
{
private:
    QVector<phono> phonos;

    bool speaking;

public:
    Speak();

    QString GetMouthShape(QString phon);
    QStringList TextToPhon(QString text);
    int TextToSpeech(QString text);
    int TextToWave(QString text);
    int PlayWave();
    void doWork();
};

#endif // SPEAK_H
