/****************************************************************************
** Meta object code from reading C++ file 'mvmethodcomm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mnt/hgfs/OSD_Widget/src/MC/mvmethodcomm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mvmethodcomm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mvMethodComm_t {
    QByteArrayData data[9];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mvMethodComm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mvMethodComm_t qt_meta_stringdata_mvMethodComm = {
    {
QT_MOC_LITERAL(0, 0, 12), // "mvMethodComm"
QT_MOC_LITERAL(1, 13, 19), // "emitGetDevcommNetIP"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 13), // "stDEVCOMM_NET"
QT_MOC_LITERAL(4, 48, 21), // "emitGetDevcommNetPort"
QT_MOC_LITERAL(5, 70, 23), // "emitGetDevcommNetSelect"
QT_MOC_LITERAL(6, 94, 12), // "slotGetNetIp"
QT_MOC_LITERAL(7, 107, 14), // "slotGetNetPort"
QT_MOC_LITERAL(8, 122, 16) // "slotGetNetSelect"

    },
    "mvMethodComm\0emitGetDevcommNetIP\0\0"
    "stDEVCOMM_NET\0emitGetDevcommNetPort\0"
    "emitGetDevcommNetSelect\0slotGetNetIp\0"
    "slotGetNetPort\0slotGetNetSelect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mvMethodComm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       5,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   53,    2, 0x0a /* Public */,
       7,    1,   56,    2, 0x0a /* Public */,
       8,    1,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void mvMethodComm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mvMethodComm *_t = static_cast<mvMethodComm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->emitGetDevcommNetIP((*reinterpret_cast< stDEVCOMM_NET(*)>(_a[1]))); break;
        case 1: _t->emitGetDevcommNetPort((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->emitGetDevcommNetSelect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slotGetNetIp((*reinterpret_cast< stDEVCOMM_NET(*)>(_a[1]))); break;
        case 4: _t->slotGetNetPort((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slotGetNetSelect((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stDEVCOMM_NET >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stDEVCOMM_NET >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (mvMethodComm::*_t)(stDEVCOMM_NET );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mvMethodComm::emitGetDevcommNetIP)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (mvMethodComm::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mvMethodComm::emitGetDevcommNetPort)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (mvMethodComm::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mvMethodComm::emitGetDevcommNetSelect)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject mvMethodComm::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_mvMethodComm.data,
      qt_meta_data_mvMethodComm,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *mvMethodComm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mvMethodComm::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_mvMethodComm.stringdata0))
        return static_cast<void*>(const_cast< mvMethodComm*>(this));
    return QObject::qt_metacast(_clname);
}

int mvMethodComm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void mvMethodComm::emitGetDevcommNetIP(stDEVCOMM_NET _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void mvMethodComm::emitGetDevcommNetPort(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void mvMethodComm::emitGetDevcommNetSelect(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
