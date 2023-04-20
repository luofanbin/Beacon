/****************************************************************************
** Meta object code from reading C++ file 'mvmethodvidsig.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mnt/hgfs/OSD_Widget/src/MC/mvmethodvidsig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mvmethodvidsig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mvMethodVidSig_t {
    QByteArrayData data[19];
    char stringdata0[379];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mvMethodVidSig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mvMethodVidSig_t qt_meta_stringdata_mvMethodVidSig = {
    {
QT_MOC_LITERAL(0, 0, 14), // "mvMethodVidSig"
QT_MOC_LITERAL(1, 15, 14), // "emitSigVinScan"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 17), // "stVIDSIGIN_STATUS"
QT_MOC_LITERAL(4, 49, 19), // "emitSigVinScanAbort"
QT_MOC_LITERAL(5, 69, 17), // "emitSigVoutFormat"
QT_MOC_LITERAL(6, 87, 12), // "stVALUE_INFO"
QT_MOC_LITERAL(7, 100, 20), // "emitSigVoutSmartLock"
QT_MOC_LITERAL(8, 121, 17), // "slotSigVinSigScan"
QT_MOC_LITERAL(9, 139, 22), // "slotSigVinSigScanAbort"
QT_MOC_LITERAL(10, 162, 26), // "slotSigVoutSigGetSigFormat"
QT_MOC_LITERAL(11, 189, 26), // "slotSigVoutSigGetSmartLock"
QT_MOC_LITERAL(12, 216, 28), // "slotSetSigParamsTodbusServer"
QT_MOC_LITERAL(13, 245, 27), // "slotSetSigCTempTodbusServer"
QT_MOC_LITERAL(14, 273, 16), // "stDISP_COLORTEMP"
QT_MOC_LITERAL(15, 290, 29), // "slotSetSigSClaingTodbusServer"
QT_MOC_LITERAL(16, 320, 14), // "stVIDGOUT_SCAL"
QT_MOC_LITERAL(17, 335, 31), // "slotSetSigAutoSteupTodbusServer"
QT_MOC_LITERAL(18, 367, 11) // "stAuto_INFO"

    },
    "mvMethodVidSig\0emitSigVinScan\0\0"
    "stVIDSIGIN_STATUS\0emitSigVinScanAbort\0"
    "emitSigVoutFormat\0stVALUE_INFO\0"
    "emitSigVoutSmartLock\0slotSigVinSigScan\0"
    "slotSigVinSigScanAbort\0"
    "slotSigVoutSigGetSigFormat\0"
    "slotSigVoutSigGetSmartLock\0"
    "slotSetSigParamsTodbusServer\0"
    "slotSetSigCTempTodbusServer\0"
    "stDISP_COLORTEMP\0slotSetSigSClaingTodbusServer\0"
    "stVIDGOUT_SCAL\0slotSetSigAutoSteupTodbusServer\0"
    "stAuto_INFO"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mvMethodVidSig[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,
       5,    1,   80,    2, 0x06 /* Public */,
       7,    1,   83,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   86,    2, 0x0a /* Public */,
       9,    1,   89,    2, 0x0a /* Public */,
      10,    1,   92,    2, 0x0a /* Public */,
      11,    1,   95,    2, 0x0a /* Public */,
      12,    2,   98,    2, 0x0a /* Public */,
      13,    1,  103,    2, 0x0a /* Public */,
      15,    1,  106,    2, 0x0a /* Public */,
      17,    1,  109,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::UChar,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 6,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::UChar,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,    2,    2,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, 0x80000000 | 18,    2,

       0        // eod
};

void mvMethodVidSig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mvMethodVidSig *_t = static_cast<mvMethodVidSig *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->emitSigVinScan((*reinterpret_cast< stVIDSIGIN_STATUS(*)>(_a[1]))); break;
        case 1: _t->emitSigVinScanAbort((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 2: _t->emitSigVoutFormat((*reinterpret_cast< stVALUE_INFO(*)>(_a[1]))); break;
        case 3: _t->emitSigVoutSmartLock((*reinterpret_cast< stVALUE_INFO(*)>(_a[1]))); break;
        case 4: _t->slotSigVinSigScan((*reinterpret_cast< stVIDSIGIN_STATUS(*)>(_a[1]))); break;
        case 5: _t->slotSigVinSigScanAbort((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 6: _t->slotSigVoutSigGetSigFormat((*reinterpret_cast< stVALUE_INFO(*)>(_a[1]))); break;
        case 7: _t->slotSigVoutSigGetSmartLock((*reinterpret_cast< stVALUE_INFO(*)>(_a[1]))); break;
        case 8: _t->slotSetSigParamsTodbusServer((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< stVALUE_INFO(*)>(_a[2]))); break;
        case 9: _t->slotSetSigCTempTodbusServer((*reinterpret_cast< stDISP_COLORTEMP(*)>(_a[1]))); break;
        case 10: _t->slotSetSigSClaingTodbusServer((*reinterpret_cast< stVIDGOUT_SCAL(*)>(_a[1]))); break;
        case 11: _t->slotSetSigAutoSteupTodbusServer((*reinterpret_cast< stAuto_INFO(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stVIDSIGIN_STATUS >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stVALUE_INFO >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stVALUE_INFO >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stVIDSIGIN_STATUS >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stVALUE_INFO >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stVALUE_INFO >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stVALUE_INFO >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stDISP_COLORTEMP >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stVIDGOUT_SCAL >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stAuto_INFO >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (mvMethodVidSig::*_t)(stVIDSIGIN_STATUS );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mvMethodVidSig::emitSigVinScan)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (mvMethodVidSig::*_t)(uchar );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mvMethodVidSig::emitSigVinScanAbort)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (mvMethodVidSig::*_t)(stVALUE_INFO );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mvMethodVidSig::emitSigVoutFormat)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (mvMethodVidSig::*_t)(stVALUE_INFO );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mvMethodVidSig::emitSigVoutSmartLock)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject mvMethodVidSig::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_mvMethodVidSig.data,
      qt_meta_data_mvMethodVidSig,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *mvMethodVidSig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mvMethodVidSig::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_mvMethodVidSig.stringdata0))
        return static_cast<void*>(const_cast< mvMethodVidSig*>(this));
    return QObject::qt_metacast(_clname);
}

int mvMethodVidSig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void mvMethodVidSig::emitSigVinScan(stVIDSIGIN_STATUS _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void mvMethodVidSig::emitSigVinScanAbort(uchar _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void mvMethodVidSig::emitSigVoutFormat(stVALUE_INFO _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void mvMethodVidSig::emitSigVoutSmartLock(stVALUE_INFO _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
