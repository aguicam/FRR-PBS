/****************************************************************************
** Meta object code from reading C++ file 'glwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../glwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GLWidget_t {
    QByteArrayData data[14];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GLWidget_t qt_meta_stringdata_GLWidget = {
    {
QT_MOC_LITERAL(0, 0, 8), // "GLWidget"
QT_MOC_LITERAL(1, 9, 8), // "SetFaces"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 11), // "SetVertices"
QT_MOC_LITERAL(4, 31, 12), // "SetFramerate"
QT_MOC_LITERAL(5, 44, 7), // "paintGL"
QT_MOC_LITERAL(6, 52, 13), // "SetReflection"
QT_MOC_LITERAL(7, 66, 3), // "set"
QT_MOC_LITERAL(8, 70, 7), // "SetBRDF"
QT_MOC_LITERAL(9, 78, 11), // "SetFresnelR"
QT_MOC_LITERAL(10, 90, 11), // "SetFresnelB"
QT_MOC_LITERAL(11, 102, 11), // "SetFresnelG"
QT_MOC_LITERAL(12, 114, 12), // "SetRoughness"
QT_MOC_LITERAL(13, 127, 11) // "SetMetallic"

    },
    "GLWidget\0SetFaces\0\0SetVertices\0"
    "SetFramerate\0paintGL\0SetReflection\0"
    "set\0SetBRDF\0SetFresnelR\0SetFresnelB\0"
    "SetFresnelG\0SetRoughness\0SetMetallic"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GLWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       3,    1,   72,    2, 0x06 /* Public */,
       4,    1,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   78,    2, 0x09 /* Protected */,
       6,    1,   79,    2, 0x09 /* Protected */,
       8,    1,   82,    2, 0x09 /* Protected */,
       9,    1,   85,    2, 0x09 /* Protected */,
      10,    1,   88,    2, 0x09 /* Protected */,
      11,    1,   91,    2, 0x09 /* Protected */,
      12,    1,   94,    2, 0x09 /* Protected */,
      13,    1,   97,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,

       0        // eod
};

void GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GLWidget *_t = static_cast<GLWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SetFaces((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->SetVertices((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->SetFramerate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->paintGL(); break;
        case 4: _t->SetReflection((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->SetBRDF((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->SetFresnelR((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->SetFresnelB((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->SetFresnelG((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->SetRoughness((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->SetMetallic((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (GLWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::SetFaces)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GLWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::SetVertices)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (GLWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::SetFramerate)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GLWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLWidget.data,
      qt_meta_data_GLWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GLWidget.stringdata0))
        return static_cast<void*>(this);
    return QGLWidget::qt_metacast(_clname);
}

int GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void GLWidget::SetFaces(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GLWidget::SetVertices(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GLWidget::SetFramerate(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
