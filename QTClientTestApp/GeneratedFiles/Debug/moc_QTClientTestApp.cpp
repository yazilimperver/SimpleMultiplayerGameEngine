/****************************************************************************
** Meta object code from reading C++ file 'QTClientTestApp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QTClientTestApp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QTClientTestApp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QTClientTestApp_t {
    QByteArrayData data[14];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QTClientTestApp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QTClientTestApp_t qt_meta_stringdata_QTClientTestApp = {
    {
QT_MOC_LITERAL(0, 0, 15), // "QTClientTestApp"
QT_MOC_LITERAL(1, 16, 9), // "connected"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "disconnected"
QT_MOC_LITERAL(4, 40, 15), // "dataReadyToRead"
QT_MOC_LITERAL(5, 56, 19), // "socketErrorOccurred"
QT_MOC_LITERAL(6, 76, 9), // "errorCode"
QT_MOC_LITERAL(7, 86, 14), // "connectClicked"
QT_MOC_LITERAL(8, 101, 11), // "sendClicked"
QT_MOC_LITERAL(9, 113, 12), // "clearClicked"
QT_MOC_LITERAL(10, 126, 11), // "saveClicked"
QT_MOC_LITERAL(11, 138, 25), // "dataRepresentationChanged"
QT_MOC_LITERAL(12, 164, 14), // "msgSizeChanged"
QT_MOC_LITERAL(13, 179, 4) // "text"

    },
    "QTClientTestApp\0connected\0\0disconnected\0"
    "dataReadyToRead\0socketErrorOccurred\0"
    "errorCode\0connectClicked\0sendClicked\0"
    "clearClicked\0saveClicked\0"
    "dataRepresentationChanged\0msgSizeChanged\0"
    "text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTClientTestApp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x0a /* Public */,
       5,    1,   67,    2, 0x0a /* Public */,
       7,    0,   70,    2, 0x0a /* Public */,
       8,    0,   71,    2, 0x0a /* Public */,
       9,    0,   72,    2, 0x0a /* Public */,
      10,    0,   73,    2, 0x0a /* Public */,
      11,    1,   74,    2, 0x0a /* Public */,
      12,    1,   77,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,   13,

       0        // eod
};

void QTClientTestApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QTClientTestApp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->dataReadyToRead(); break;
        case 3: _t->socketErrorOccurred((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->connectClicked(); break;
        case 5: _t->sendClicked(); break;
        case 6: _t->clearClicked(); break;
        case 7: _t->saveClicked(); break;
        case 8: _t->dataRepresentationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->msgSizeChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QTClientTestApp::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_QTClientTestApp.data,
    qt_meta_data_QTClientTestApp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QTClientTestApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTClientTestApp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QTClientTestApp.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int QTClientTestApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
