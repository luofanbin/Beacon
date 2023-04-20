/****************************************************************************
** Meta object code from reading C++ file 'mvmethodvidport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mnt/hgfs/OSD_Widget/src/MC/mvmethodvidport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mvmethodvidport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mvMethodVidPort_t {
    QByteArrayData data[8];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mvMethodVidPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mvMethodVidPort_t qt_meta_stringdata_mvMethodVidPort = {
    {
QT_MOC_LITERAL(0, 0, 15), // "mvMethodVidPort"
QT_MOC_LITERAL(1, 16, 22), // "emitSigOutPortSetOnoff"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 10), // "PortStatus"
QT_MOC_LITERAL(4, 51, 24), // "emitSigOutPortSetSDIType"
QT_MOC_LITERAL(5, 76, 13), // "stOutSig_INFO"
QT_MOC_LITERAL(6, 90, 22), // "slotSigOutPortSetOnoff"
QT_MOC_LITERAL(7, 113, 24) // "slotSigOutPortSetSDIType"

    },
    "mvMethodVidPort\0emitSigOutPortSetOnoff\0"
    "\0PortStatus\0emitSigOutPortSetSDIType\0"
    "stOutSig_INFO\0slotSigOutPortSetOnoff\0"
    "slotSigOutPortSetSDIType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mvMethodVidPort[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   40,    2, 0x0a /* Public */,
       7,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

       0        // eod
};

void mvMethodVidPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mvMethodVidPort *_t = static_cast<mvMethodVidPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->emitSigOutPortSetOnoff((*reinterpret_cast< PortStatus(*)>(_a[1]))); break;
        case 1: _t->emitSigOutPortSetSDIType((*reinterpret_cast< stOutSig_INFO(*)>(_a[1]))); break;
        case 2: _t->slotSigOutPortSetOnoff((*reinterpret_cast< PortStatus(*)>(_a[1]))); break;
        case 3: _t->slotSigOutPortSetSDIType((*reinterpret_cast< stOutSig_INFO(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PortStatus >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stOutSig_INFO >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PortStatus >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stOutSig_INFO >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (mvMethodVidPort::*_t)(PortStatus );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mvMethodVidPort::emitSigOutPortSetOnoff)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (mvMethodVidPort::*_t)(stOutSig_INFO );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mvMethodVidPort::emitSigOutPortSetSDIType)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject mvMethodVidPort::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_mvMethodVidPort.data,
      qt_meta_data_mvMethodVidPort,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *mvMethodVidPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mvMethodVidPort::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_mvMethodVidPort.stringdata0))
        return static_cast<void*>(const_cast< mvMethodVidPort*>(this));
    return QObject::qt_metacast(_clname);
}

int mvMethodVidPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void mvMethodVidPort::emitSigOutPortSetOnoff(PortStatus _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void mvMethodVidPort::emitSigOutPortSetSDIType(stOutSig_INFO _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
