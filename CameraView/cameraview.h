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
	Ui::CameraViewClass ui;

	void createConnects( void );

	bool getCamOpenStatus (void);
	//VmbError_t getOpenError (void);
	QString GetCameraID (void);
	//QString getCameraSystemInfo (void);
	//QString getCameraName (void);

	void setBasicInfo( CameraPtr cam );


private:
	APIController *m_pcontroller;
	VmbErrorType m_OpenError;
	bool bIsCamOpen;
	bool bIsCamRun;
	bool bIsStreaming;//判断是否可以进行拍照

	QString m_sAccessMode;
	CameraPtr m_pCam;
	std::string strID;

	QImage m_image;
	QPixmap m_pixmap;

	int imgCount;
	TimeRecord timeRecord;

	//QGraphicsPixmapItem *m_pPixmapItem;
	QSharedPointer<QGraphicsScene> m_pscene;
	//Viewer *m_pviewer;
	QGraphicsView *m_pviewer;

signals:
	void FrameCountChange( int );
	void CenterChange( cv::Point2f );

private slots:
	void CamStart( void );
	void CamStop ( void );
	void CamOpen( void );
	void CamInfoDisplay( const CameraPtr m_pCam );
	//void onAcquisitionStartToStop( void );
	void InfoWindowDisplay( const QString str );
	void ErrorWindowDisplay( const QString str );
	
	void PictureWindowDisplay ( QImage image );//,const QString sHeight,const QString sWidth
	//void ProcessDataWindowDiaplay();
	//void CameraFeatureDisplay ( void );
	//void ProcessDataWindowDiaplay ( void );
	void setPushButtonStartEnabled( bool );
	void setPushButtonStopEnabled ( bool );
	
	//void setPushButtonEndEnabled ( void );
	//void setPushButtonSaveEnabled ( void );
	bool isStreamingAvailable( void );
	void onFrameReady ( int status );
	bool CopyToImage( VmbUchar_t* pbuffer,VmbPixelFormatType ePixel, QImage &image );
	void SaveImageToFile();

	void onCamChange( int reason);
	
	void onImgCountChange( int );
	void onCenterChange( cv::Point2f );

	void testStart();
	void About();

};

#endif // CAMERAVIEW_H
