/****************************************************************************
** Meta object code from reading C++ file 'mvMeThodOsd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mnt/hgfs/OSD_Widget/mvMeThodOsd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mvMeThodOsd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mvMethodOsd_t {
    QByteArrayData data[20];
    char stringdata0[293];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mvMethodOsd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mvMethodOsd_t qt_meta_stringdata_mvMethodOsd = {
    {
QT_MOC_LITERAL(0, 0, 11), // "mvMethodOsd"
QT_MOC_LITERAL(1, 12, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 28, 20), // "mv.mvosd.osd.disposd"
QT_MOC_LITERAL(3, 49, 17), // "emitSendDispOnOff"
QT_MOC_LITERAL(4, 67, 0), // ""
QT_MOC_LITERAL(5, 68, 14), // "stDispOsd_INFO"
QT_MOC_LITERAL(6, 83, 16), // "emitSendDispSpan"
QT_MOC_LITERAL(7, 100, 11), // "emitSendMsg"
QT_MOC_LITERAL(8, 112, 13), // "stOsdMsg_INFO"
QT_MOC_LITERAL(9, 126, 19), // "emitSigSetSingleSel"
QT_MOC_LITERAL(10, 146, 18), // "emitSigSetItemSpan"
QT_MOC_LITERAL(11, 165, 16), // "emitSigSetOsdMsg"
QT_MOC_LITERAL(12, 182, 16), // "slotGetSingleSel"
QT_MOC_LITERAL(13, 199, 12), // "osddisp_type"
QT_MOC_LITERAL(14, 212, 16), // "slotSetSingleSel"
QT_MOC_LITERAL(15, 229, 8), // "setValue"
QT_MOC_LITERAL(16, 238, 15), // "slotGetItemSpan"
QT_MOC_LITERAL(17, 254, 15), // "slotSetItemSpan"
QT_MOC_LITERAL(18, 270, 13), // "slotSetOsdMsg"
QT_MOC_LITERAL(19, 284, 8) // "stOsdMsg"

    },
    "mvMethodOsd\0D-Bus Interface\0"
    "mv.mvosd.osd.disposd\0emitSendDispOnOff\0"
    "\0stDispOsd_INFO\0emitSendDispSpan\0"
    "emitSendMsg\0stOsdMsg_INFO\0emitSigSetSingleSel\0"
    "emitSigSetItemSpan\0emitSigSetOsdMsg\0"
    "slotGetSingleSel\0osddisp_type\0"
    "slotSetSingleSel\0setValue\0slotGetItemSpan\0"
    "slotSetItemSpan\0slotSetOsdMsg\0stOsdMsg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mvMethodOsd[] = {

 // content:
       7,       // revision
       0,       // classname
       1,   14, // classinfo
      11,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags
       3,    1,   71,    4, 0x06 /* Public */,
       6,    1,   74,    4, 0x06 /* Public */,
       7,    1,   77,    4, 0x06 /* Public */,
       9,    1,   80,    4, 0x06 /* Public */,
      10,    1,   83,    4, 0x06 /* Public */,
      11,    1,   86,    4, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   89,    4, 0x0a /* Public */,
      14,    1,   92,    4, 0x0a /* Public */,
      16,    1,   95,    4, 0x0a /* Public */,
      17,    1,   98,    4, 0x0a /* Public */,
      18,    1,  101,    4, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 5,    4,
    QMetaType::Void, 0x80000000 | 5,    4,
    QMetaType::Void, 0x80000000 | 8,    4,
    QMetaType::Void, 0x80000000 | 5,    4,
    QMetaType::Void, 0x80000000 | 5,    4,
    QMetaType::Void, 0x80000000 | 8,    4,

 // slots: parameters
    0x80000000 | 5, QMetaType::Int,   13,
    QMetaType::Void, 0x80000000 | 5,   15,
    0x80000000 | 5, QMetaType::Int,   13,
    QMetaType::Void, 0x80000000 | 5,   15,
    QMetaType::Void, 0x80000000 | 8,   19,

       0        // eod
};

void mvMethodOsd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mvMethodOsd *_t = static_cast<mvMethodOsd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->emitSendDispOnOff((*reinterpret_cast< stDispOsd_INFO(*)>(_a[1]))); break;
        case 1: _t->emitSendDispSpan((*reinterpret_cast< stDispOsd_INFO(*)>(_a[1]))); break;
        case 2: _t->emitSendMsg((*reinterpret_cast< stOsdMsg_INFO(*)>(_a[1]))); break;
        case 3: _t->emitSigSetSingleSel((*reinterpret_cast< stDispOsd_INFO(*)>(_a[1]))); break;
        case 4: _t->emitSigSetItemSpan((*reinterpret_cast< stDispOsd_INFO(*)>(_a[1]))); break;
        case 5: _t->emitSigSetOsdMsg((*reinterpret_cast< stOsdMsg_INFO(*)>(_a[1]))); break;
        case 6: { stDispOsd_INFO _r = _t->slotGetSingleSel((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< stDispOsd_INFO*>(_a[0]) = _r; }  break;
        case 7: _t->slotSetSingleSel((*reinterpret_cast< stDispOsd_INFO(*)>(_a[1]))); break;
        case 8: { stDispOsd_INFO _r = _t->slotGetItemSpan((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< stDispOsd_INFO*>(_a[0]) = _r; }  break;
        case 9: _t->slotSetItemSpan((*reinterpret_cast< stDispOsd_INFO(*)>(_a[1]))); break;
        case 10: _t->slotSetOsdMsg((*reinterpret_cast< stOsdMsg_INFO(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stDispOsd_INFO >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stDispOsd_INFO >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stOsdMsg_INFO >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stDispOsd_INFO >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stDispOsd_INFO >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stOsdMsg_INFO >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stDispOsd_INFO >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stDispOsd_INFO >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stOsdMsg_INFO >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (mvMethodOsd::*_t)(stDispOsd_INFO );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mvMethodOsd::emitSendDispOnOff)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (mvMethodOsd::*_t)(stDispOsd_INFO );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mvMethodOsd::emitSendDispSpan)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (mvMethodOsd::*_t)(stOsdMsg_INFO );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mvMethodOsd::emitSendMsg)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (mvMethodOsd::*_t)(stDispOsd_INFO );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mvMethodOsd::emitSigSetSingleSel)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (mvMethodOsd::*_t)(stDispOsd_INFO );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mvMethodOsd::emitSigSetItemSpan)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (mvMethodOsd::*_t)(stOsdMsg_INFO );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mvMethodOsd::emitSigSetOsdMsg)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject mvMethodOsd::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_mvMethodOsd.data,
      qt_meta_data_mvMethodOsd,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *mvMethodOsd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mvMethodOsd::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_mvMethodOsd.stringdata0))
        return static_cast<void*>(const_cast< mvMethodOsd*>(this));
    return QThread::qt_metacast(_clname);
}

int mvMethodOsd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void mvMethodOsd::emitSendDispOnOff(stDispOsd_INFO _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void mvMethodOsd::emitSendDispSpan(stDispOsd_INFO _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void mvMethodOsd::emitSendMsg(stOsdMsg_INFO _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void mvMethodOsd::emitSigSetSingleSel(stDispOsd_INFO _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void mvMethodOsd::emitSigSetItemSpan(stDispOsd_INFO _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void mvMethodOsd::emitSigSetOsdMsg(stOsdMsg_INFO _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
