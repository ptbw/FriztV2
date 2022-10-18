#-------------------------------------------------
#
# Project created by QtCreator 2016-08-25T14:28:44
#
#-------------------------------------------------

QT       += core gui #serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fritz
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    configwindow.cpp \
    aboutbox.cpp \
    robot.cpp \
    speak.cpp \
    worker.cpp \
    keyenterreceiver.cpp \
    animate.cpp \
    BCM2835.c \
    Adafruit_ServoHAT.c \
    PCA9685.c \
    vl53l0x.cpp \
    distance.cpp

HEADERS  += mainwindow.h \
    configwindow.h \
    aboutbox.h \
    i.h \
    robot.h \
    speak.h \
    worker.h \
    keyenterreceiver.h \
    animate.h \
    BCM2835.h \
    Adafruit_ServoHAT.h \
    PCA9685.h \
    Standard_Library.h \
    System_Library.h \
    vl53l0x.h \
    distance.h

FORMS    += mainwindow.ui \
    aboutbox.ui \
    configwindow.ui

OTHER_FILES += \
    speech/consonantphons.txt \
    speech/consonants.txt \
    speech/vowels.txt \
    speech/vowelsphons.txt \
    images/aaah.png \
    images/eee.png \
    images/fuh.png \
    images/i.png \
    images/laa.png \
    images/mmm.png \
    images/oh.png \
    images/oooh.png \
    images/phoneme mouth chart.png \
    images/sss.png \
    speech/cookies.txt

unix:!macx: LIBS += -L$$PWD/../../../usr/local/lib/ -lVL53L0X_Rasp

INCLUDEPATH += $$PWD/../../../usr/local/include
DEPENDPATH += $$PWD/../../../usr/local/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/libVL53L0X_Rasp.a
