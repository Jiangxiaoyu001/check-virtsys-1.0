/****************************************************************************
** Meta object code from reading C++ file 'check_virtsys_xml.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/check_virtsys_xml.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'check_virtsys_xml.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CHECK_VIRTSYS_XML_t {
    QByteArrayData data[10];
    char stringdata0[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CHECK_VIRTSYS_XML_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CHECK_VIRTSYS_XML_t qt_meta_stringdata_CHECK_VIRTSYS_XML = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CHECK_VIRTSYS_XML"
QT_MOC_LITERAL(1, 18, 37), // "check_virt_emitSignal_saveNet..."
QT_MOC_LITERAL(2, 56, 0), // ""
QT_MOC_LITERAL(3, 57, 11), // "std::string"
QT_MOC_LITERAL(4, 69, 25), // "_virDomainInterfaceStats&"
QT_MOC_LITERAL(5, 95, 30), // "Check_Virtsys_VirtSysDataInfo*"
QT_MOC_LITERAL(6, 126, 31), // "check_virt_parseXml_NetWorkInfo"
QT_MOC_LITERAL(7, 158, 12), // "virDomainPtr"
QT_MOC_LITERAL(8, 171, 25), // "_virDomainInterfaceStats*"
QT_MOC_LITERAL(9, 197, 8) // "statsPtr"

    },
    "CHECK_VIRTSYS_XML\0"
    "check_virt_emitSignal_saveNetWorkData\0"
    "\0std::string\0_virDomainInterfaceStats&\0"
    "Check_Virtsys_VirtSysDataInfo*\0"
    "check_virt_parseXml_NetWorkInfo\0"
    "virDomainPtr\0_virDomainInterfaceStats*\0"
    "statsPtr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CHECK_VIRTSYS_XML[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    3,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 3, 0x80000000 | 4, 0x80000000 | 5,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 7, 0x80000000 | 8,    2,    2,    9,

       0        // eod
};

void CHECK_VIRTSYS_XML::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CHECK_VIRTSYS_XML *_t = static_cast<CHECK_VIRTSYS_XML *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->check_virt_emitSignal_saveNetWorkData((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])),(*reinterpret_cast< _virDomainInterfaceStats(*)>(_a[3])),(*reinterpret_cast< Check_Virtsys_VirtSysDataInfo*(*)>(_a[4]))); break;
        case 1: _t->check_virt_parseXml_NetWorkInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< virDomainPtr(*)>(_a[2])),(*reinterpret_cast< _virDomainInterfaceStats*(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (CHECK_VIRTSYS_XML::*_t)(unsigned int , std::string , _virDomainInterfaceStats & , Check_Virtsys_VirtSysDataInfo * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CHECK_VIRTSYS_XML::check_virt_emitSignal_saveNetWorkData)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CHECK_VIRTSYS_XML::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CHECK_VIRTSYS_XML.data,
      qt_meta_data_CHECK_VIRTSYS_XML,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CHECK_VIRTSYS_XML::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CHECK_VIRTSYS_XML::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CHECK_VIRTSYS_XML.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CHECK_VIRTSYS_XML::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CHECK_VIRTSYS_XML::check_virt_emitSignal_saveNetWorkData(unsigned int _t1, std::string _t2, _virDomainInterfaceStats & _t3, Check_Virtsys_VirtSysDataInfo * _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
