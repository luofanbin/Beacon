/****************************************************************************
** Meta object code from reading C++ file 'DpAdjustment.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mnt/hgfs/OSD_Widget/DpAdjustment.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DpAdjustment.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DpAdjustment_t {
    QByteArrayData data[11];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DpAdjustment_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DpAdjustment_t qt_meta_stringdata_DpAdjustment = {
    {
QT_MOC_LITERAL(0, 0, 12), // "DpAdjustment"
QT_MOC_LITERAL(1, 13, 13), // "emitSetDpInfo"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 20), // "stSCAL_INPUT_DP_INFO"
QT_MOC_LITERAL(4, 49, 13), // "emitGetDpInfo"
QT_MOC_LITERAL(5, 63, 21), // "on_toolButton_clicked"
QT_MOC_LITERAL(6, 85, 14), // "checkBox_Click"
QT_MOC_LITERAL(7, 100, 17), // "CommBoxChangIndex"
QT_MOC_LITERAL(8, 118, 5), // "index"
QT_MOC_LITERAL(9, 124, 19), // "SubmitButtonClicked"
QT_MOC_LITERAL(10, 144, 15) // "slot_DpInfoHide"

    },
    "DpAdjustment\0emitSetDpInfo\0\0"
    "stSCAL_INPUT_DP_INFO\0emitGetDpInfo\0"
    "on_toolButton_clicked\0checkBox_Click\0"
    "CommBoxChangIndex\0index\0SubmitButtonClicked\0"
    "slot_DpInfoHide"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DpAdjustment[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   55,    2, 0x0a /* Public */,
       6,    0,   56,    2, 0x0a /* Public */,
       7,    1,   57,    2, 0x0a /* Public */,
       9,    0,   60,    2, 0x0a /* Public */,
      10,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DpAdjustment::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DpAdjustment *_t = static_cast<DpAdjustment *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->emitSetDpInfo((*reinterpret_cast< stSCAL_INPUT_DP_INFO(*)>(_a[1]))); break;
        case 1: _t->emitGetDpInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_toolButton_clicked(); break;
        case 3: _t->checkBox_Click(); break;
        case 4: _t->CommBoxChangIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->SubmitButtonClicked(); break;
        case 6: _t->slot_DpInfoHide(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stSCAL_INPUT_DP_INFO >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DpAdjustment::*_t)(stSCAL_INPUT_DP_INFO );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DpAdjustment::emitSetDpInfo)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DpAdjustment::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DpAdjustment::emitGetDpInfo)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject DpAdjustment::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DpAdjustment.data,
      qt_meta_data_DpAdjustment,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DpAdjustment::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DpAdjustment::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DpAdjustment.stringdata0))
        return static_cast<void*>(const_cast< DpAdjustment*>(this));
    if (!strcmp(_clname, "Ui_DP_Adjustment"))
        return static_cast< Ui_DP_Adjustment*>(const_cast< DpAdjustment*>(this));
    return QDialog::qt_metacast(_clname);
}

int DpAdjustment::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void DpAdjustment::emitSetDpInfo(stSCAL_INPUT_DP_INFO _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DpAdjustment::emitGetDpInfo(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
