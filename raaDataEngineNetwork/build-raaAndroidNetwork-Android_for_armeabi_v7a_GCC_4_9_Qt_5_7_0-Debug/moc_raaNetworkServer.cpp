/****************************************************************************
** Meta object code from reading C++ file 'raaNetworkServer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../raaNetworkServer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'raaNetworkServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_raaNetworkServer_t {
    QByteArrayData data[6];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_raaNetworkServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_raaNetworkServer_t qt_meta_stringdata_raaNetworkServer = {
    {
QT_MOC_LITERAL(0, 0, 16), // "raaNetworkServer"
QT_MOC_LITERAL(1, 17, 4), // "read"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "raaTcpMsg*"
QT_MOC_LITERAL(4, 34, 14), // "tcpSocketAdded"
QT_MOC_LITERAL(5, 49, 16) // "tcpSocketRemoved"

    },
    "raaNetworkServer\0read\0\0raaTcpMsg*\0"
    "tcpSocketAdded\0tcpSocketRemoved"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_raaNetworkServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,
       5,    1,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void raaNetworkServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        raaNetworkServer *_t = static_cast<raaNetworkServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->read((*reinterpret_cast< raaTcpMsg*(*)>(_a[1]))); break;
        case 1: _t->tcpSocketAdded((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->tcpSocketRemoved((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (raaNetworkServer::*_t)(raaTcpMsg * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&raaNetworkServer::read)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (raaNetworkServer::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&raaNetworkServer::tcpSocketAdded)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (raaNetworkServer::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&raaNetworkServer::tcpSocketRemoved)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject raaNetworkServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_raaNetworkServer.data,
      qt_meta_data_raaNetworkServer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *raaNetworkServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *raaNetworkServer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_raaNetworkServer.stringdata0))
        return static_cast<void*>(const_cast< raaNetworkServer*>(this));
    return QObject::qt_metacast(_clname);
}

int raaNetworkServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void raaNetworkServer::read(raaTcpMsg * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void raaNetworkServer::tcpSocketAdded(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void raaNetworkServer::tcpSocketRemoved(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
