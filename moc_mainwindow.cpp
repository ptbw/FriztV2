/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[384];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 7), // "on_Stop"
QT_MOC_LITERAL(4, 45, 25), // "on_actionConfig_triggered"
QT_MOC_LITERAL(5, 71, 23), // "on_actionSave_triggered"
QT_MOC_LITERAL(6, 95, 23), // "on_actionQuit_triggered"
QT_MOC_LITERAL(7, 119, 21), // "on_comboBox_activated"
QT_MOC_LITERAL(8, 141, 4), // "arg1"
QT_MOC_LITERAL(9, 146, 18), // "on_btnLeft_clicked"
QT_MOC_LITERAL(10, 165, 19), // "on_btnHello_clicked"
QT_MOC_LITERAL(11, 185, 17), // "on_btnAsk_clicked"
QT_MOC_LITERAL(12, 203, 21), // "on_btnFortune_clicked"
QT_MOC_LITERAL(13, 225, 19), // "on_btnOkBye_clicked"
QT_MOC_LITERAL(14, 245, 20), // "on_btnThanks_clicked"
QT_MOC_LITERAL(15, 266, 20), // "on_btnCentre_clicked"
QT_MOC_LITERAL(16, 287, 19), // "on_btnRight_clicked"
QT_MOC_LITERAL(17, 307, 21), // "on_btnAnimate_clicked"
QT_MOC_LITERAL(18, 329, 28), // "on_volumeSlider_valueChanged"
QT_MOC_LITERAL(19, 358, 5), // "value"
QT_MOC_LITERAL(20, 364, 19) // "on_btnSpeak_clicked"

    },
    "MainWindow\0on_actionAbout_triggered\0"
    "\0on_Stop\0on_actionConfig_triggered\0"
    "on_actionSave_triggered\0on_actionQuit_triggered\0"
    "on_comboBox_activated\0arg1\0"
    "on_btnLeft_clicked\0on_btnHello_clicked\0"
    "on_btnAsk_clicked\0on_btnFortune_clicked\0"
    "on_btnOkBye_clicked\0on_btnThanks_clicked\0"
    "on_btnCentre_clicked\0on_btnRight_clicked\0"
    "on_btnAnimate_clicked\0"
    "on_volumeSlider_valueChanged\0value\0"
    "on_btnSpeak_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    0,  103,    2, 0x08 /* Private */,
       7,    1,  104,    2, 0x08 /* Private */,
       9,    0,  107,    2, 0x08 /* Private */,
      10,    0,  108,    2, 0x08 /* Private */,
      11,    0,  109,    2, 0x08 /* Private */,
      12,    0,  110,    2, 0x08 /* Private */,
      13,    0,  111,    2, 0x08 /* Private */,
      14,    0,  112,    2, 0x08 /* Private */,
      15,    0,  113,    2, 0x08 /* Private */,
      16,    0,  114,    2, 0x08 /* Private */,
      17,    0,  115,    2, 0x08 /* Private */,
      18,    1,  116,    2, 0x08 /* Private */,
      20,    0,  119,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_actionAbout_triggered(); break;
        case 1: _t->on_Stop(); break;
        case 2: _t->on_actionConfig_triggered(); break;
        case 3: _t->on_actionSave_triggered(); break;
        case 4: _t->on_actionQuit_triggered(); break;
        case 5: _t->on_comboBox_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_btnLeft_clicked(); break;
        case 7: _t->on_btnHello_clicked(); break;
        case 8: _t->on_btnAsk_clicked(); break;
        case 9: _t->on_btnFortune_clicked(); break;
        case 10: _t->on_btnOkBye_clicked(); break;
        case 11: _t->on_btnThanks_clicked(); break;
        case 12: _t->on_btnCentre_clicked(); break;
        case 13: _t->on_btnRight_clicked(); break;
        case 14: _t->on_btnAnimate_clicked(); break;
        case 15: _t->on_volumeSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_btnSpeak_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
