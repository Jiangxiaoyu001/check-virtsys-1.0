/****************************************************************************
** Meta object code from reading C++ file 'check_virtsys_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/check_virtsys_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'check_virtsys_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Check_Virtsys_Window_t {
    QByteArrayData data[7];
    char stringdata0[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Check_Virtsys_Window_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Check_Virtsys_Window_t qt_meta_stringdata_Check_Virtsys_Window = {
    {
QT_MOC_LITERAL(0, 0, 20), // "Check_Virtsys_Window"
QT_MOC_LITERAL(1, 21, 29), // "Check_Virtsys_changedListItem"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 25), // "check_virtsys_SwitchPages"
QT_MOC_LITERAL(4, 78, 26), // "Check_Virtsys_updataWidget"
QT_MOC_LITERAL(5, 105, 37), // "Check_Virtsys_tabWidDomain_up..."
QT_MOC_LITERAL(6, 143, 38) // "Check_Virtsys_tabWidNetWork_u..."

    },
    "Check_Virtsys_Window\0Check_Virtsys_changedListItem\0"
    "\0check_virtsys_SwitchPages\0"
    "Check_Virtsys_updataWidget\0"
    "Check_Virtsys_tabWidDomain_updataItem\0"
    "Check_Virtsys_tabWidNetWork_updataItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Check_Virtsys_Window[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Check_Virtsys_Window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Check_Virtsys_Window *_t = static_cast<Check_Virtsys_Window *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Check_Virtsys_changedListItem(); break;
        case 1: _t->check_virtsys_SwitchPages(); break;
        case 2: _t->Check_Virtsys_updataWidget(); break;
        case 3: _t->Check_Virtsys_tabWidDomain_updataItem(); break;
        case 4: _t->Check_Virtsys_tabWidNetWork_updataItem(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Check_Virtsys_Window::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Check_Virtsys_Window.data,
      qt_meta_data_Check_Virtsys_Window,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Check_Virtsys_Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Check_Virtsys_Window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Check_Virtsys_Window.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Check_Virtsys_Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
