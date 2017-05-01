#ifndef AVT_VMBAPI_APICONTROLLER_H
#define AVT_VMBAPI_APICONTROLLER_H

#include "VimbaCPP/Include/VimbaCPP.h"
#include "FrameObserver.h"
#include "CameraObserver.h"
#include <opencv2\core\core.hpp>
#include <QImage.h>

namespace AVT{
namespace VmbAPI{


class APIController
{
public:
	APIController();
	~APIController();

	VmbErrorType            StartUp();
	void                    ShutDown();

	VmbErrorType            OpenCamera();
	void                    CloseCamera();
	CameraPtr               GetCamera();
  
	void                    FeaturePrintStart();

	CameraPtrVector         GetCameraList();
	FramePtr                GetFrame();
	void                    SaveFrame( FramePtr p);
	VmbPixelFormatType      GetPixelFormat() const;

	std::string             GetVersion() const;
	std::string             GetCameraID();
	int                     GetHeight() const;
	int                     GetWidth() const;	
	int                     GetImgNum() const;
	double                  GetExposureTime();

	VmbErrorType            GetAsyPic();
	VmbErrorType            StopContinousGettingImage();
	QObject*                GetObserverCamera();
	QObject*                GetObserverFrames();
	void                    ClearObserverFrames();
	void                    QueueFrame( FramePtr frame );

	cv::Point2f             LaserPoint( cv::Mat &tmp);
	std::vector<double>     CirclePoint();

	void                    WriteToFile();
	//void                    SaveImageToFile();
	//VimbaSystem& GetSys() const;
	cv::Mat                 cvQImage2Mat( QImage image );
	QImage                  cvMat2QImage( cv::Mat mat );

	void LoadSettings();

private:
	VimbaSystem& m_system;
	CameraPtr m_pCamera;

	VmbInt64_t m_PixelFormat;
	VmbInt64_t m_Width;
	VmbInt64_t m_Height;
	double m_exposureTime;
	int m_ImgNum;

	//double m_Fps;
	std::string m_CameraID;
	CameraPtrVector m_Cameras;
	//CameraObserver* m_pCameraObserver;
	ICameraListObserverPtr m_pCameraObserver;
	//FrameObserver* m_pFrameObserver;
	IFrameObserverPtr m_pFrameObserver;
	FramePtrVector m_pFrames;

	std::vector<const char*> FeaturesList;
	
	std::vector<cv::Point2f> Center;
	std::vector<double> CircleData;
};

}}

#endif