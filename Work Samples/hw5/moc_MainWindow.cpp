/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      23,   11,   11,   11, 0x08,
      39,   11,   11,   11, 0x08,
      51,   11,   11,   11, 0x08,
      64,   11,   11,   11, 0x08,
      83,   11,   11,   11, 0x08,
     105,   11,   11,   11, 0x08,
     115,   11,   11,   11, 0x08,
     131,   11,   11,   11, 0x08,
     143,   11,   11,   11, 0x08,
     162,   11,   11,   11, 0x08,
     181,   11,   11,   11, 0x08,
     201,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0viewCart()\0searchClicked()\0"
    "sortAlpha()\0sortRating()\0addToCartClicked()\0"
    "changeCurrentRow(int)\0buyCart()\0"
    "removeProduct()\0closeCart()\0"
    "updateReviews(int)\0addReviewClicked()\0"
    "completeAddReview()\0quitApplication()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->viewCart(); break;
        case 1: _t->searchClicked(); break;
        case 2: _t->sortAlpha(); break;
        case 3: _t->sortRating(); break;
        case 4: _t->addToCartClicked(); break;
        case 5: _t->changeCurrentRow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->buyCart(); break;
        case 7: _t->removeProduct(); break;
        case 8: _t->closeCart(); break;
        case 9: _t->updateReviews((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->addReviewClicked(); break;
        case 11: _t->completeAddReview(); break;
        case 12: _t->quitApplication(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
