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
	APIController(int imgNumber);
	~APIController();
	
	//相机操作
	VmbErrorType            StartUp();
	void                    ShutDown();
	void                    ParamReady();
	VmbErrorType            OpenCamera();
	void                    CloseCamera();
	CameraPtr               GetCamera();
  
	void                    FeaturePrintStart();

	CameraPtrVector         GetCameraList();
	FramePtr                GetFrame();
	void                    SaveFrame( FramePtr p);
	VmbPixelFormatType      GetPixelFormat() const;

	//相机基本信息接口
	std::string             GetVersion() const;
	std::string             GetCameraID();
	int                     GetHeight() const;
	int                     GetWidth() const;	
	int                     GetImgNum() const;
	double                  GetExposureTime();

	//相机帧获取
	VmbErrorType            StartContinousGettingImage();
	VmbErrorType            StopContinousGettingImage();
	QObject*                GetObserverCamera();
	QObject*                GetObserverFrames();
	void                    ClearObserverFrames();
	void                    QueueFrame( FramePtr frame );

	//图像处理接口
	cv::Point2d             LaserPoint( cv::Mat &tmp);
	//散点包络圆求解
	std::vector<double>&     CirclePoint( std::vector<cv::Point2d>& point );
	std::vector<double>&     CirclePoint();

	void                    WriteToFile();
	
	cv::Mat                 cvQImage2Mat( const QImage& image );
	QImage                  cvMat2QImage( const cv::Mat& mat );

	void                    LoadSettings();
	void                    imgNumberChange(int imgNumber);
	void                    ExposureTimeChange( int exposureTime );

	//void                  SaveImageToFile();
	//VimbaSystem& GetSys() const;
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
	
	std::vector<cv::Point2d> Center;
	std::vector<double> CircleData;
};

}}

#endif