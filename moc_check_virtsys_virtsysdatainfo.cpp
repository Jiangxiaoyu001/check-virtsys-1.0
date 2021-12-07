/****************************************************************************
** Meta object code from reading C++ file 'check_virtsys_virtsysdatainfo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/check_virtsys_virtsysdatainfo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'check_virtsys_virtsysdatainfo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Check_Virtsys_VirtSysDataInfo_t {
    QByteArrayData data[10];
    char stringdata0[217];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Check_Virtsys_VirtSysDataInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Check_Virtsys_VirtSysDataInfo_t qt_meta_stringdata_Check_Virtsys_VirtSysDataInfo = {
    {
QT_MOC_LITERAL(0, 0, 29), // "Check_Virtsys_VirtSysDataInfo"
QT_MOC_LITERAL(1, 30, 33), // "check_virtsys_emitSignal_pars..."
QT_MOC_LITERAL(2, 64, 0), // ""
QT_MOC_LITERAL(3, 65, 8), // "QString&"
QT_MOC_LITERAL(4, 74, 13), // "virDomainPtr&"
QT_MOC_LITERAL(5, 88, 26), // "_virDomainInterfaceStats*&"
QT_MOC_LITERAL(6, 115, 32), // "check_virtsys_saveVirNetWorkData"
QT_MOC_LITERAL(7, 148, 11), // "std::string"
QT_MOC_LITERAL(8, 160, 25), // "_virDomainInterfaceStats&"
QT_MOC_LITERAL(9, 186, 30) // "Check_Virtsys_VirtSysDataInfo*"

    },
    "Check_Virtsys_VirtSysDataInfo\0"
    "check_virtsys_emitSignal_parseXML\0\0"
    "QString&\0virDomainPtr&\0"
    "_virDomainInterfaceStats*&\0"
    "check_virtsys_saveVirNetWorkData\0"
    "std::string\0_virDomainInterfaceStats&\0"
    "Check_Virtsys_VirtSysDataInfo*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Check_Virtsys_VirtSysDataInfo[] = {

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
       1,    3,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    4,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4, 0x80000000 | 5,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 7, 0x80000000 | 8, 0x80000000 | 9,    2,    2,    2,    2,

       0        // eod
};

void Check_Virtsys_VirtSysDataInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Check_Virtsys_VirtSysDataInfo *_t = static_cast<Check_Virtsys_VirtSysDataInfo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->check_virtsys_emitSignal_parseXML((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< virDomainPtr(*)>(_a[2])),(*reinterpret_cast< _virDomainInterfaceStats*(*)>(_a[3]))); break;
        case 1: _t->check_virtsys_saveVirNetWorkData((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])),(*reinterpret_cast< _virDomainInterfaceStats(*)>(_a[3])),(*reinterpret_cast< Check_Virtsys_VirtSysDataInfo*(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Check_Virtsys_VirtSysDataInfo* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Check_Virtsys_VirtSysDataInfo::*_t)(QString & , virDomainPtr & , _virDomainInterfaceStats * & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Check_Virtsys_VirtSysDataInfo::check_virtsys_emitSignal_parseXML)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Check_Virtsys_VirtSysDataInfo::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Check_Virtsys_VirtSysDataInfo.data,
      qt_meta_data_Check_Virtsys_VirtSysDataInfo,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Check_Virtsys_VirtSysDataInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Check_Virtsys_VirtSysDataInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Check_Virtsys_VirtSysDataInfo.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Check_Virtsys_VirtSysDataInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Check_Virtsys_VirtSysDataInfo::check_virtsys_emitSignal_parseXML(QString & _t1, virDomainPtr & _t2, _virDomainInterfaceStats * & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
