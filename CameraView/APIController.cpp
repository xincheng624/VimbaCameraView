#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
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
#include "miniball.hpp"


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

void APIController::ParamReady()
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
	}

	/*else
	{
		VmbErrorType res = VmbErrorNotFound;
		std::cout<<"No Camera for getting picture."<<std::endl;
		return;
	}*/

}


VmbErrorType APIController::StartContinousGettingImage()
{
	if( m_pCamera != NULL )
	{
	
		//m_pFrameObserver = new FrameObserver(m_pCamera);
		m_pFrameObserver.reset(new FrameObserver(m_pCamera));
		
		//const int count = 3;
		if ( !m_pFrames.empty() )
		{
			m_pFrames.swap( FramePtrVector() );
		}
		VmbErrorType res = m_pCamera->StartContinuousImageAcquisition(m_ImgNum, m_pFrameObserver );//IFrameObserverPtr(m_pFrameObserver)
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
	//dynamic_cast是因为父类ICameraListObserverPtr需要向下转换到子类FrameObserver
	//从而子类能够向上转换为QObject*
	return SP_DYN_CAST(m_pFrameObserver,FrameObserver).get();
}

void APIController::ClearObserverFrames()
{
	SP_DYN_CAST(m_pFrameObserver,FrameObserver)->ClearFrames();
}

void APIController::QueueFrame( FramePtr frame )
{
	SP_ACCESS( m_pCamera )->QueueFrame( frame );
}

cv::Point2d APIController::LaserPoint( cv::Mat &tmp)
{
	/*VmbUchar_t* Imagebuffer;
	std::vector<cv::Mat> image;

	for(FramePtrVector::iterator iter=m_pFrames.begin();iter != m_pFrames.end();++iter)
	{
		VmbErrorType res = (*iter)->GetImage(Imagebuffer);
		if(res == VmbErrorSuccess)
		{
			VmbUint32_t nSize;
			res = (*iter)->GetImageSize(nSize);
			if(res == VmbErrorSuccess)
			{
				image.push_back(cv::Mat((int)m_Width,(int)m_Height,CV_8UC1,Imagebuffer));
			}
			
		}
	}*/
	//int i=0;
	
	//std::string winname;
	//int delay = 1000;//画面每帧间隔ms数
	ImageProcess Pro;
	
	cv::Point2d cen;
	cen = Pro.center(tmp);
	Center.push_back(cen);
	
	//Pro.DrawCross(tmp,cen);//将圆心以十字标出


	//Pro.CirclePoint(Center);

	/*for (std::vector<cv::Mat>::iterator iter1=image.begin();iter1 !=image.end();++iter1)
	{	
		//std::stringstream in;
		//in<< ++i;
		//winname = in.str();
		cv::Point2f cen;
		cen = Pro.center(*iter1);
		Center.push_back(cen);
		Pro.DrawCross(*iter1,cen);

		//winname = "Display";
		//cv::namedWindow(winname,CV_WINDOW_NORMAL);
		//cv::imshow(winname,(*iter1));
		//std::cout<<"Opencv Image showed."<<std::endl;
		//if(cv::waitKey(delay)>=0)
		//	continue;
	}*/

	//cv::waitKey();
	return cen;
}

std::vector<double>& APIController::CirclePoint( std::vector<cv::Point2d>& point  )
{
	typedef double mytype;            // coordinate type
	
	int             d = 2;            // dimension
	int             n = point.size();      // number of points
	
	//std::ifstream in("2.txt");
		
	/*mytype** ap = new mytype*[n];
	for (int i=0; i<n; ++i) {
		mytype* p = new mytype[d];
		for (int j=0; j<d; ++j) {
			double temp;
			in>>temp;
			p[j] = temp;
		}
		ap[i]=p;
	}	*/

	mytype** ap = new mytype*[n];
	for (int i=0; i<n; ++i) {
		mytype* p = new mytype[d];
		p[0] = point[i].x;
		p[1] = point[i].y;
		ap[i]=p;
	}


	
	// define the types of iterators through the points and their coordinates
	// ---------------------------------------------------------------------
	typedef mytype* const* PointIterator; 
	typedef const mytype* CoordIterator;
	
	// create an instance of Miniball
	// ------------------------------
	typedef Miniball::
		Miniball <Miniball::CoordAccessor<PointIterator, CoordIterator> > 
		MB;
	MB mb (d, ap, ap+n);

	//求取中心点
	const mytype* center = mb.center(); 
	
	//using namespace cv;
	std::vector<double> r;

  /*const int width = 3384;
  const int height = 2710;
  cv::Mat mat(width,height,CV_8UC1);*/

	
	for(int i=0; i<n; ++i)
	{
		//cv::circle(mat,cv::Point(ap[i][0],ap[i][1]),10,Scalar(0,0,0),-1,8);
		r.push_back(sqrt((ap[i][0]-center[0])*(ap[i][0]-center[0])+(ap[i][1]-center[1])*(ap[i][1]-center[1])));
	}
	std::sort(r.begin(),r.end());
	double rmax = r.back();
	double rmin = *r.begin();

	/*circle(mat,Point2d(center[0],center[1]),rmax,Scalar(0,0,0),1,8);
	circle(mat,Point2d(center[0],center[1]),rmin,Scalar(0,0,0),1,8);
	std::cout<<"rmax:"<<rmax<<std::endl;
	std::cout<<"rmin:"<<rmin<<std::endl;
	std::cout<<"r distance :"<<rmax-rmin<<std::endl;
	std::cout<<"____________________________________"<<std::endl;
	namedWindow("1",0);
	imshow("1",mat);
	*/
  
	std::vector<double>* data = new std::vector<double>();
	data->push_back(center[0]);
	data->push_back(center[1]);
	data->push_back(rmax);
	data->push_back(rmin);

  // output results
	// --------------
	// center
  /*std::cout << "Center:\n  ";
  for(int i=0; i<d; ++i, ++center)
    std::cout << *center << " ";
  std::cout << std::endl;
  */
  
  /*
  // squared radius
  std::cout << "Squared radius:\n  ";
  std::cout << mb.squared_radius() <<  std::endl;

  // number of support points
  std::cout << "Number of support points:\n  ";
  std::cout << mb.nr_support_points() << std::endl;

  // support points on the boundary determine the smallest enclosing ball
  std::cout << "Support point indices (numbers refer to the input order):\n  ";
  MB::SupportPointIterator it = mb.support_points_begin();
  for (; it != mb.support_points_end(); ++it) {
    std::cout << (*it)-ap << " "; // 0 = first point
  }
  std::cout << std::endl;
  
  // relative error: by how much does the ball fail to contain all points? 
  //                 tiny positive numbers come from roundoff and are ok
  std::cout << "Relative error:\n  ";
  mytype suboptimality;
  std::cout << mb.relative_error (suboptimality) <<  std::endl;
  
  // suboptimality: by how much does the ball fail to be the smallest
  //                enclosing ball of its support points? should be 0 
  //                in most cases, but tiny positive numbers are again ok
  std::cout << "Suboptimality:\n  ";
  std::cout << suboptimality <<  std::endl;

  // validity: the ball is considered valid if the relative error is tiny
  //           (<= 10 times the machine epsilon) and the suboptimality is zero
  std::cout << "Validity:\n  ";
  std::cout << (mb.is_valid() ? "ok" : "possibly invalid") << std::endl;

  // computation time
  std::cout << "Computation time was "<< mb.get_time() << " seconds\n";
  */

  // clean up
	for (int i=0; i<n; ++i)
		delete[] ap[i];
	delete[] ap;
	
	return *data;
}

std::vector<double>& APIController::CirclePoint()
{
	//ImageProcess Pro;	
	if ( !Center.empty() )
		CircleData = CirclePoint( Center );
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


cv::Mat APIController::cvQImage2Mat( const QImage& image )
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

QImage APIController::cvMat2QImage( const cv::Mat& mat )
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

void APIController::imgNumberChange(int imgNumber)
{
	m_ImgNum = imgNumber;
}

void APIController::ExposureTimeChange( int exposureTime )
{
	//std::cout<<exposureTime<<std::endl;
	FeaturePtr pFeature;
	if(NULL != m_pCamera)
	{
		m_pCamera->GetFeatureByName("ExposureTimeAbs",pFeature);
		VmbErrorType res1;
		res1 = pFeature->SetValue(exposureTime);
		std::string str;
		pFeature->GetName(str);
		if (res1==VmbErrorSuccess)
		{
			std::cout<<str<<"set to"<<" value("<<exposureTime<< ") successfully."<<std::endl;
		}
	}
}


}}