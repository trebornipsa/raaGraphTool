/****************************************************************************
** Meta object code from reading C++ file 'raaNetworkClient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../raaNetworkClient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'raaNetworkClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_raaNetworkClient_t {
    QByteArrayData data[7];
    char stringdata0[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_raaNetworkClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_raaNetworkClient_t qt_meta_stringdata_raaNetworkClient = {
    {
QT_MOC_LITERAL(0, 0, 16), // "raaNetworkClient"
QT_MOC_LITERAL(1, 17, 4), // "read"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "raaTcpMsg*"
QT_MOC_LITERAL(4, 34, 6), // "stream"
QT_MOC_LITERAL(5, 41, 13), // "socketStarted"
QT_MOC_LITERAL(6, 55, 14) // "socketFinished"

    },
    "raaNetworkClient\0read\0\0raaTcpMsg*\0"
    "stream\0socketStarted\0socketFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_raaNetworkClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    0,   37,    2, 0x06 /* Public */,
       5,    0,   38,    2, 0x06 /* Public */,
       6,    0,   39,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void raaNetworkClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        raaNetworkClient *_t = static_cast<raaNetworkClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->read((*reinterpret_cast< raaTcpMsg*(*)>(_a[1]))); break;
        case 1: _t->stream(); break;
        case 2: _t->socketStarted(); break;
        case 3: _t->socketFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (raaNetworkClient::*_t)(raaTcpMsg * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&raaNetworkClient::read)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (raaNetworkClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&raaNetworkClient::stream)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (raaNetworkClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&raaNetworkClient::socketStarted)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (raaNetworkClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&raaNetworkClient::socketFinished)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject raaNetworkClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_raaNetworkClient.data,
      qt_meta_data_raaNetworkClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *raaNetworkClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *raaNetworkClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_raaNetworkClient.stringdata0))
        return static_cast<void*>(const_cast< raaNetworkClient*>(this));
    return QObject::qt_metacast(_clname);
}

int raaNetworkClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void raaNetworkClient::read(raaTcpMsg * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void raaNetworkClient::stream()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void raaNetworkClient::socketStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void raaNetworkClient::socketFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
