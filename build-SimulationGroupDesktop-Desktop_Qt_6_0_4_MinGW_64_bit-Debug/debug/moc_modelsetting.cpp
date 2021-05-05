/****************************************************************************
** Meta object code from reading C++ file 'modelsetting.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.0.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../SimulationGroupDesktop/modelsetting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modelsetting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.0.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ModelSetting_t {
    const uint offsetsAndSize[26];
    char stringdata0[210];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ModelSetting_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ModelSetting_t qt_meta_stringdata_ModelSetting = {
    {
QT_MOC_LITERAL(0, 12), // "ModelSetting"
QT_MOC_LITERAL(13, 21), // "on_comboBox_activated"
QT_MOC_LITERAL(35, 0), // ""
QT_MOC_LITERAL(36, 5), // "index"
QT_MOC_LITERAL(42, 26), // "on_cellRowNum_valueChanged"
QT_MOC_LITERAL(69, 4), // "arg1"
QT_MOC_LITERAL(74, 26), // "on_cellColNum_valueChanged"
QT_MOC_LITERAL(101, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(123, 26), // "on_addActionButton_clicked"
QT_MOC_LITERAL(150, 21), // "on_buttonBox_rejected"
QT_MOC_LITERAL(172, 26), // "on_actionTable_cellClicked"
QT_MOC_LITERAL(199, 3), // "row"
QT_MOC_LITERAL(203, 6) // "column"

    },
    "ModelSetting\0on_comboBox_activated\0\0"
    "index\0on_cellRowNum_valueChanged\0arg1\0"
    "on_cellColNum_valueChanged\0"
    "on_buttonBox_accepted\0on_addActionButton_clicked\0"
    "on_buttonBox_rejected\0on_actionTable_cellClicked\0"
    "row\0column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModelSetting[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x08,    0 /* Private */,
       4,    1,   59,    2, 0x08,    2 /* Private */,
       6,    1,   62,    2, 0x08,    4 /* Private */,
       7,    0,   65,    2, 0x08,    6 /* Private */,
       8,    0,   66,    2, 0x08,    7 /* Private */,
       9,    0,   67,    2, 0x08,    8 /* Private */,
      10,    2,   68,    2, 0x08,    9 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   12,

       0        // eod
};

void ModelSetting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ModelSetting *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_comboBox_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_cellRowNum_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_cellColNum_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_buttonBox_accepted(); break;
        case 4: _t->on_addActionButton_clicked(); break;
        case 5: _t->on_buttonBox_rejected(); break;
        case 6: _t->on_actionTable_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject ModelSetting::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_ModelSetting.offsetsAndSize,
    qt_meta_data_ModelSetting,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ModelSetting_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


>,
    nullptr
} };


const QMetaObject *ModelSetting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModelSetting::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ModelSetting.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ModelSetting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
