/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.0.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../SimulationGroupDesktop/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.0.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[42];
    char stringdata0[474];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 26), // "on_startPushButton_clicked"
QT_MOC_LITERAL(38, 0), // ""
QT_MOC_LITERAL(39, 26), // "on_nextFrameButton_clicked"
QT_MOC_LITERAL(66, 26), // "on_lastFrameButton_clicked"
QT_MOC_LITERAL(93, 30), // "on_progressSlider_valueChanged"
QT_MOC_LITERAL(124, 4), // "arg1"
QT_MOC_LITERAL(129, 27), // "on_speedSlider_valueChanged"
QT_MOC_LITERAL(157, 21), // "on_modelset_triggered"
QT_MOC_LITERAL(179, 31), // "on_operationTypeCombo_activated"
QT_MOC_LITERAL(211, 5), // "index"
QT_MOC_LITERAL(217, 34), // "on_operationValueSpin_valueCh..."
QT_MOC_LITERAL(252, 25), // "on_cellXSpin_valueChanged"
QT_MOC_LITERAL(278, 25), // "on_cellYSpin_valueChanged"
QT_MOC_LITERAL(304, 35), // "on_operationValueSpin2_valueC..."
QT_MOC_LITERAL(340, 21), // "on_randButton_clicked"
QT_MOC_LITERAL(362, 7), // "checked"
QT_MOC_LITERAL(370, 25), // "on_curTypeButton1_clicked"
QT_MOC_LITERAL(396, 25), // "on_curTypeButton3_clicked"
QT_MOC_LITERAL(422, 25), // "on_curTypeButton2_clicked"
QT_MOC_LITERAL(448, 25) // "on_curTypeButton4_clicked"

    },
    "MainWindow\0on_startPushButton_clicked\0"
    "\0on_nextFrameButton_clicked\0"
    "on_lastFrameButton_clicked\0"
    "on_progressSlider_valueChanged\0arg1\0"
    "on_speedSlider_valueChanged\0"
    "on_modelset_triggered\0"
    "on_operationTypeCombo_activated\0index\0"
    "on_operationValueSpin_valueChanged\0"
    "on_cellXSpin_valueChanged\0"
    "on_cellYSpin_valueChanged\0"
    "on_operationValueSpin2_valueChanged\0"
    "on_randButton_clicked\0checked\0"
    "on_curTypeButton1_clicked\0"
    "on_curTypeButton3_clicked\0"
    "on_curTypeButton2_clicked\0"
    "on_curTypeButton4_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  110,    2, 0x08,    0 /* Private */,
       3,    0,  111,    2, 0x08,    1 /* Private */,
       4,    0,  112,    2, 0x08,    2 /* Private */,
       5,    1,  113,    2, 0x08,    3 /* Private */,
       7,    1,  116,    2, 0x08,    5 /* Private */,
       8,    0,  119,    2, 0x08,    7 /* Private */,
       9,    1,  120,    2, 0x08,    8 /* Private */,
      11,    1,  123,    2, 0x08,   10 /* Private */,
      12,    1,  126,    2, 0x08,   12 /* Private */,
      13,    1,  129,    2, 0x08,   14 /* Private */,
      14,    1,  132,    2, 0x08,   16 /* Private */,
      15,    1,  135,    2, 0x08,   18 /* Private */,
      17,    1,  138,    2, 0x08,   20 /* Private */,
      18,    1,  141,    2, 0x08,   22 /* Private */,
      19,    1,  144,    2, 0x08,   24 /* Private */,
      20,    1,  147,    2, 0x08,   26 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::Bool,   16,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_startPushButton_clicked(); break;
        case 1: _t->on_nextFrameButton_clicked(); break;
        case 2: _t->on_lastFrameButton_clicked(); break;
        case 3: _t->on_progressSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_speedSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_modelset_triggered(); break;
        case 6: _t->on_operationTypeCombo_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_operationValueSpin_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_cellXSpin_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_cellYSpin_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_operationValueSpin2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_randButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_curTypeButton1_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_curTypeButton3_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->on_curTypeButton2_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->on_curTypeButton4_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>


>,
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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
