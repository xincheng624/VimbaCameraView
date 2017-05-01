/****************************************************************************
** Meta object code from reading C++ file 'cameraview.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../cameraview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cameraview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CameraView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      34,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      60,   11,   11,   11, 0x08,
      71,   11,   11,   11, 0x08,
      81,   11,   11,   11, 0x08,
      98,   91,   11,   11, 0x08,
     128,  124,   11,   11, 0x08,
     155,  124,   11,   11, 0x08,
     189,  183,   11,   11, 0x08,
     218,   11,   11,   11, 0x08,
     250,   11,   11,   11, 0x08,
     286,   11,  281,   11, 0x08,
     316,  309,   11,   11, 0x08,
     355,  334,  281,   11, 0x08,
     407,   11,   11,   11, 0x08,
     432,  425,   11,   11, 0x08,
     449,   11,   11,   11, 0x08,
     471,   11,   11,   11, 0x08,
     499,   11,   11,   11, 0x08,
     511,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CameraView[] = {
    "CameraView\0\0FrameCountChange(int)\0"
    "CenterChange(cv::Point2f)\0CamStart()\0"
    "CamStop()\0CamOpen()\0m_pCam\0"
    "CamInfoDisplay(CameraPtr)\0str\0"
    "InfoWindowDisplay(QString)\0"
    "ErrorWindowDisplay(QString)\0image\0"
    "PictureWindowDisplay(QImage)\0"
    "setPushButtonStartEnabled(bool)\0"
    "setPushButtonStopEnabled(bool)\0bool\0"
    "isStreamingAvailable()\0status\0"
    "onFrameReady(int)\0pbuffer,ePixel,image\0"
    "CopyToImage(VmbUchar_t*,VmbPixelFormatType,QImage&)\0"
    "SaveImageToFile()\0reason\0onCamChange(int)\0"
    "onImgCountChange(int)\0onCenterChange(cv::Point2f)\0"
    "testStart()\0About()\0"
};

void CameraView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CameraView *_t = static_cast<CameraView *>(_o);
        switch (_id) {
        case 0: _t->FrameCountChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->CenterChange((*reinterpret_cast< cv::Point2f(*)>(_a[1]))); break;
        case 2: _t->CamStart(); break;
        case 3: _t->CamStop(); break;
        case 4: _t->CamOpen(); break;
        case 5: _t->CamInfoDisplay((*reinterpret_cast< const CameraPtr(*)>(_a[1]))); break;
        case 6: _t->InfoWindowDisplay((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->ErrorWindowDisplay((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->PictureWindowDisplay((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 9: _t->setPushButtonStartEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->setPushButtonStopEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: { bool _r = _t->isStreamingAvailable();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: _t->onFrameReady((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: { bool _r = _t->CopyToImage((*reinterpret_cast< VmbUchar_t*(*)>(_a[1])),(*reinterpret_cast< VmbPixelFormatType(*)>(_a[2])),(*reinterpret_cast< QImage(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: _t->SaveImageToFile(); break;
        case 15: _t->onCamChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->onImgCountChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->onCenterChange((*reinterpret_cast< cv::Point2f(*)>(_a[1]))); break;
        case 18: _t->testStart(); break;
        case 19: _t->About(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CameraView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CameraView::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CameraView,
      qt_meta_data_CameraView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CameraView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CameraView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CameraView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CameraView))
        return static_cast<void*>(const_cast< CameraView*>(this));
    if (!strcmp(_clname, "Ui::CameraViewClass"))
        return static_cast< Ui::CameraViewClass*>(const_cast< CameraView*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CameraView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void CameraView::FrameCountChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CameraView::CenterChange(cv::Point2f _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
