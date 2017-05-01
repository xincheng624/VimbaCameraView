#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include "APIController.h"
#include "VimbaCPP\Include\IFrameObserver.h"
#include "VimbaCPP\Include\VimbaSystem.h"

#include "Common/StreamSystemInfo.h"
#include "Common/ErrorCodeToMessage.h"

#include "InfoPrint.h"
#include "FeaturePrint.h"
#include "Bitmap.h"
#include "CameraObserver.h"

#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "ImageProcess.h"

namespace AVT{
namespace VmbAPI{

APIController::APIController():m_system(VimbaSystem::GetInstance())
	,m_PixelFormat( VmbPixelFormatMono8 )
	,m_ImgNum(1)
{
}

APIController::~APIController()
{
}

VmbErrorType APIController::StartUp()
{
	VmbErrorType res = m_system.Startup();
	if( VmbErrorSuccess == res)
	{
		//std::cout<<"System Started!"<<std::endl;
		m_Cameras = GetCameraList();

		m_pCameraObserver.reset( new CameraObserver() );

		res = m_system.RegisterCameraListObserver( m_pCameraObserver );

	}
	return res;
}

void APIController::ShutDown()
{
	VmbErrorType res = m_system.Shutdown();
	std::cout<< "System closed."<<std::endl;
}



VmbErrorType APIController::OpenCamera()
{
	VmbErrorType res;
	if(m_pCamera != NULL)
	{
		res = m_pCamera->Open(VmbAccessModeFull);
		if(VmbErrorSuccess == res)
		{
			std::cout<<"Camera ModeFull Opened!"<<std::endl;
			GetCameraID();
		}
		else
			std::cout<<"OpenCamera Failed!"<<std::endl;
	}
	else
		std::cout<<"No Camera to Open."<<std::endl;

	return res;
}

void APIController::CloseCamera()
{
	if(m_pCamera != NULL)
	{
		VmbErrorType res = m_pCamera->Close();
		if(VmbErrorSuccess == res)
		{
			std::cout<<"Camera Closed!"<<std::endl;
		}
		else
			std::cout<<"CloseCamera Failed!"<<std::endl;
	}
	else
		std::cout<<"No Camera to Close."<<std::endl;
}

CameraPtr APIController::GetCamera()
{
	return m_pCamera;
}

void APIController::FeaturePrintStart()
{
	FeaturePrint p;
	p.GetCamera(m_pCamera);
	//p.Print(m_CameraID);
	FeaturesList.push_back("ExposureTimeAbs");
	p.Print(FeaturesList);

}

CameraPtrVector APIController::GetCameraList()
{
	VmbErrorType res = m_system.GetCameras(m_Cameras);
	if( VmbErrorSuccess == res )
	{
		if(m_Cameras.size() != 0)
		{
			std::cout<<"Camera Found:" <<m_Cameras.size()<<std::endl;
			m_pCamera = m_Cameras[0];
			return m_Cameras;
		}
		else
		{
			std::cout<<"Camera Found: 0"<<std::endl;
			return CameraPtrVector();
		}
	}
	else
	{
		std::cout<<"[Error in getting cameras list.Error code:"<<res<<"-";
		std::wcout<<ErrorCodeToMessage(res);
		std::cout<<"]"<<std::endl;//wcout输出wstring;
		return CameraPtrVector();
	}
	
}

FramePtr APIController::GetFrame()
{
	return SP_DYN_CAST(m_pFrameObserver,FrameObserver)->GetFrames();
}

void APIController::SaveFrame( FramePtr p )
{
	m_pFrames.push_back(p);
}

VmbPixelFormatType APIController::GetPixelFormat() const
{
	return static_cast<VmbPixelFormatType>( m_PixelFormat );
}

std::string  APIController::GetVersion() const
{
	std::ostringstream o;
	o<<m_system;
	return o.str();
}

std::string APIController::GetCameraID()
{
	if( NULL != m_pCamera )
	{
		VmbErrorType res = m_pCamera->GetID(m_CameraID);//只获取第一个相机
		//if(VmbErrorSuccess == res)
			//std::cout<<"The first CameraID has got."<<std::endl;
	}
	//else
	//{
	//	std::cout<<"No Camera for getting camera ID."<<std::endl;
	//}
	return m_CameraID;
}


int APIController::GetHeight() const
{
	return static_cast<int>( m_Height );
}

int APIController::GetWidth() const
{
	return static_cast<int>( m_Width );
}

int APIController::GetImgNum() const
{
	return m_ImgNum;
}

double APIController::GetExposureTime()
{
	FeaturePtr p;
	m_pCamera->GetFeatureByName("ExposureTimeAbs",p);
	p->GetValue(m_exposureTime);

	std::cout<<"Exposure Time:"<<m_exposureTime <<"us"<<std::endl;
	return m_exposureTime;
}


void APIController::LoadSettings()
{
	FeaturePtr pFeature;
	if(NULL != m_pCamera)
	{
		m_pCamera->GetFeatureByName("ExposureTimeAbs",pFeature);
		VmbErrorType res1;
		const double ExposureTimeAbs = 2000;
		res1 = pFeature->SetValue(ExposureTimeAbs);
		std::string str;
		pFeature->GetName(str);
		if (res1==VmbErrorSuccess)
		{
			std::cout<<str<<"set to"<<" value("<<ExposureTimeAbs<< ") successfully."<<std::endl;
		}
	}


	//for(std::vector<const char*>::const_iterator iter=FeaturesList.begin();iter!=FeaturesList.end();iter++)
		
	/*std::stringstream filenameIn;
	filenameIn.str("1");
	filenameIn <<".xml";//<< m_CameraID
	std::string filename = filenameIn.str();
	if(m_pCamera != NULL)
	{
		//m_pCamera->Open(VmbAccessModeFull);

		VmbFeaturePersistSettings_t settingsStruct;
        settingsStruct.loggingLevel = 4;
        settingsStruct.maxIterations = 5;
        settingsStruct.persistType = VmbFeaturePersistNoLUT;

		VmbErrorType res = m_pCamera->LoadCameraSettings(filename,&settingsStruct);
		if(VmbErrorSuccess == res)
		{
			std::cout<<"Loading Settings succeed."<<std::endl;
		}
		else
			std::cout<<"Loading Settings failed."<<std::endl;

	}*/

}

VmbErrorType APIController::GetAsyPic()
{
	FeaturePtr pfeature;

	if(m_pCamera != NULL)
	{		
		if ( VmbErrorSuccess == m_pCamera->GetFeatureByName( "GVSPAdjustPacketSize", pfeature ))
        {
            if ( VmbErrorSuccess == pfeature->RunCommand() )
            {
                bool bIsCommandDone = false;
                do
                {
                    if ( VmbErrorSuccess != pfeature->IsCommandDone( bIsCommandDone ))
                    {
                        break;
                    }
                } while ( false == bIsCommandDone );
            }
        }//Set the maximum possible Ethernet packet size
		// Set the GeV packet size to the highest possible value


		/*** helper function to set image size to a value that is dividable by modulo 2.
		\note this is needed because VimbaImageTransform does not support odd values 
		for some input formats*/
		VmbInt64_t Value_min,Value_max;
		VmbErrorType res = m_pCamera->GetFeatureByName("Width",pfeature);
		res = pfeature->GetRange(Value_min,Value_max);
		Value_max = (Value_max>>1)<<1;
		m_Width = Value_max;
		res = pfeature->SetValue(m_Width);

		res = m_pCamera->GetFeatureByName("Height",pfeature);
		res = pfeature->GetRange(Value_min,Value_max);
		Value_max = (Value_max>>1)<<1;
		m_Height = Value_max;
		res = pfeature->SetValue(m_Height);



		//m_pFrameObserver = new FrameObserver(m_pCamera);
		m_pFrameObserver.reset(new FrameObserver(m_pCamera));

		//const int count = 3;
		if ( !m_pFrames.empty() )
		{
			m_pFrames.swap( FramePtrVector() );
		}
		res = m_pCamera->StartContinuousImageAcquisition(m_ImgNum, m_pFrameObserver );//IFrameObserverPtr(m_pFrameObserver)
		//std::cout<<"ImageAcquisition."<<std::endl;
		if(VmbErrorSuccess == res)
		{
			std::cout<<"ImageAcquisition Started."<<std::endl;
		}
		else
		{
			std::cout<<"ImageAcquisition Failed."<<std::endl;
		}

		return res;
	}

	else
	{
		VmbErrorType res = VmbErrorNotFound;
		std::cout<<"No Camera for getting picture."<<std::endl;
		return res;
	}

}


VmbErrorType APIController::StopContinousGettingImage()
{
	VmbErrorType res = m_pCamera->StopContinuousImageAcquisition();

	if(VmbErrorSuccess == res)
	{
		std::cout<<"ImageAcquisition Stopped."<<std::endl;
	}
	else
	{
		std::cout<<"ImageAcquisitionStop Failed."<<std::endl;
	}
	return res;
}

QObject* APIController::GetObserverCamera()
{
	return SP_DYN_CAST(m_pCameraObserver,CameraObserver).get();
}


QObject* APIController::GetObserverFrames()
{
	return SP_DYN_CAST(m_pFrameObserver,FrameObserver).get();//dynamic_cast是因为需要从子类FrameObserver到基类QObject转换
}

void APIController::ClearObserverFrames()
{
	SP_DYN_CAST(m_pFrameObserver,FrameObserver)->ClearFrames();
}

void APIController::QueueFrame( FramePtr frame )
{
	SP_ACCESS( m_pCamera )->QueueFrame( frame );
}

cv::Point2f APIController::LaserPoint( cv::Mat &tmp)
{
	
	ImageProcess Pro;

	cv::Point2f cen;
	cen = Pro.center(tmp);
	Center.push_back(cen);
	Pro.DrawCross(tmp,cen);//将圆心以十字标出
	//Pro.CirclePoint(Center);


	//cv::waitKey();
	return cen;
}

std::vector<double> APIController::CirclePoint()
{
	ImageProcess Pro;
	if ( !Center.empty() )
		Pro.CirclePoint( Center );
	CircleData = Pro.GetCircleData();
	return CircleData;
}

void APIController::WriteToFile()
{
	VmbUchar_t * pImage = NULL;
	VmbUint32_t ImageSize = 0;
	static int i = 0;
	std::cout<<"Img Write. m_pFrames size:"<< m_pFrames.size() <<std::endl;
	for(FramePtrVector::iterator iter=m_pFrames.begin();iter != m_pFrames.end();++iter)
	{
		
		VmbErrorType res = (*iter)->GetImage(pImage);
		res = (*iter)->GetBufferSize(ImageSize);
		if(res == VmbErrorSuccess)
		{
			AVTBitmap bitmap;
			bitmap.colorCode = ColorCodeMono8;
			bitmap.bufferSize = ImageSize;
			bitmap.height = (unsigned long)m_Height;
			bitmap.width = (unsigned long)m_Width;

			if( 0 == AVTCreateBitmap(&bitmap,pImage) )
			{
				std::cout<<"Can not create bitmap."<<std::endl;
				res = VmbErrorResources;
			}

			else 
			{
				char pFileName[20] = "image\\";
				char tmpfile[10] = "";
				_itoa_s(++i,tmpfile,10);//itoa 10进制
				char name[5]=".bmp";
				strcat_s(tmpfile,8,name);
				strcat_s(pFileName,19,tmpfile);//文件名总长小于19
				const char* s =pFileName;
				if( 0 == AVTWriteBitmapToFile(&bitmap,s))
				{
					std::cout<<"Can not write bitmap to file."<<std::endl;
					res = VmbErrorOther;
				}
				else
				{
					std::cout<<"bitmap has written to file."<<std::endl;
					if( 0 == AVTReleaseBitmap(&bitmap))
					{
						std::cout<<"Can not release the bitmap."<<std::endl;
					}
				}
			}

		}
	}
}


cv::Mat APIController::cvQImage2Mat( QImage image )
{
	cv::Mat tmp;
	QImage::Format format = image.format();
	if ( format == QImage::Format_Indexed8 )
		tmp = cv::Mat(image.height(),image.width(),CV_8UC1, (void*)image.constBits(),
		image.bytesPerLine() );
	else if ( format == QImage::Format_RGB888 )
	{
		tmp = cv::Mat(image.height(),image.width(),CV_8UC3, (void*)image.constBits(),
		image.bytesPerLine() );
		cv::cvtColor( tmp, tmp, CV_BGR2RGB );
	}
	return tmp;
}

QImage APIController::cvMat2QImage( cv::Mat mat )
{
	
	if ( mat.type() == CV_8UC1 )
	{
		QImage image( mat.cols, mat.rows, QImage::Format_Indexed8 );
		image.setColorCount(256);
		for( int i = 0; i < 256; ++i )
		{
			image.setColor(i,qRgb(i,i,i));
		}

		uchar* pSrc = mat.data;
		for( int row = 0; row < mat.rows; ++row )
		{
			uchar* pDest = image.scanLine( row );
			memcpy( pDest, pSrc, mat.cols );
			pSrc += mat.step;
		}

		return image;
	}

	else if( mat.type() == CV_8UC3 )
	{

		const uchar* pSrc = mat.data;
		QImage image( pSrc,mat.cols, mat.rows, mat.step, QImage::Format_RGB888 );
		return image.rgbSwapped();
	}
	return QImage();
}

}}