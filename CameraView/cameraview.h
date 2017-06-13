#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include <QtGui/QMainWindow>
#include <QtGui>
#include <QGraphicsView.h>
#include "ui_cameraview.h"
#include "VimbaCPP\Include\VimbaCPP.h"
#include "APIController.h"
//#include "Viewer.h"
#include "TimeRecord.h"

//#define NDEBUG//是否开启DEBUG模式

using AVT::VmbAPI::CameraPtr;
using AVT::VmbAPI::APIController;

class CameraView : public QMainWindow,public Ui::CameraViewClass
{
	Q_OBJECT

public:
	CameraView(QWidget *parent = 0, Qt::WFlags flags = 0,QString sId = " ",
		QString sAccess = " ",CameraPtr Cam = CameraPtr());

	~CameraView();
private:
	Ui::CameraViewClass  ui;
	//建立连接
	void           createConnects( void );

	//返回cameraID，只有类内部使用
	QString        GetCameraID (void);

	//bool         getCamOpenStatus (void);
	//VmbError_t   getOpenError (void);
	//QString      getCameraSystemInfo (void);
	//QString      getCameraName (void);

signals:
	void           FrameCountChange( int );
	void           CenterChange( const cv::Point2f& );

private slots:
	void           CamStart( void );
	void           CamStop ( void );
	void           CamOpen( void );
	void           CamInfoDisplay( const CameraPtr  m_pCam );
	
	void           InfoWindowDisplay( const QString& str );
	void           ErrorWindowDisplay( const QString& str );
	
	//实时图像显示
	//const QString sHeight,const QString sWidth
	void           PictureWindowDisplay ( QImage& image );
	//绘制散点分布图和环带
	void           PictureWindowDraw(const std::vector<cv::Point2d>& point, const std::vector<double>& data );
	
	void           setPushButtonStartEnabled( bool );
	void           setPushButtonStopEnabled ( bool );
	
	
	bool           isStreamingAvailable( void );
	void           onFrameReady ( int status );
	bool           CopyToImage( VmbUchar_t* pbuffer,VmbPixelFormatType ePixel, QImage &image );
	void           SaveImageToFile();

	void           onCamChange( int reason);
	
	void           onImgNumberChange();
	void           onExposureTimeChange();
	void           onImgCountChange( int );
	void           onCenterChange( const cv::Point2f& );

	//测试求值入口
	//testCenter() 求取选中图片中心值
	void           testCenter();

	//求取选中中心点文件的包络环
	void           testCircle();
	
	void           About();	

	//void setPushButtonEndEnabled ( void );
	//void setPushButtonSaveEnabled ( void );
	//void ProcessDataWindowDiaplay();
	//void CameraFeatureDisplay ( void );
	//void ProcessDataWindowDiaplay ( void );
private:
	APIController  *m_pcontroller;
	VmbErrorType   m_OpenError;

	bool           bIsCamOpen;
	bool           bIsCamRun;

	//判断是否可以进行拍照
	bool           bIsStreaming;

	QString        m_sAccessMode;
	CameraPtr      m_pCam;
	std::string    strID;

	QImage         m_image;
	QPixmap        m_pixmap;

	int            imgCount;
	TimeRecord     timeRecord;

	
	QSharedPointer<QGraphicsScene>    m_pscene;
	
	QGraphicsView                     *m_pviewer;

	//QGraphicsPixmapItem *m_pPixmapItem;
	//Viewer *m_pviewer;
};

#endif // CAMERAVIEW_H
