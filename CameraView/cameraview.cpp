#include "cameraview.h"
#include <iostream>
#include <fstream>
#include "Common\ErrorCodeToMessage.h"
#include "VimbaImageTransform\Include\VmbTransform.h"
#include <qfiledialog.h>

//using namespace std;
using namespace AVT::VmbAPI;


CameraView::CameraView(QWidget *parent, Qt::WFlags flags,QString sId,QString sAccess,CameraPtr Cam)
	: QMainWindow(NULL, flags)
	, m_OpenError ( VmbErrorDeviceNotOpen )
	, bIsCamOpen ( false)
	, bIsCamRun ( false )
	, m_pCam ( Cam )
	, imgCount( 0 ) 
	, m_pcontroller( new APIController() )
	//, m_pviewer(NULL)
{
	ui.setupUi(this);
	
	//lineEditImgNumber正则，限制为3位正整数
	QRegExp regExp("[1-9][0-9]{0,2}");
	ui.lineEditImgNumber->setValidator(new QRegExpValidator(regExp,this));
	//m_pscene = QSharedPointer<QGraphicsScene>( new QGraphicsScene() );
	//m_pviewer = new QGraphicsView();

	createConnects();
	
	if ( m_pcontroller != NULL)
	{
		VmbErrorType err = m_pcontroller->StartUp();
		if ( err == VmbErrorSuccess )
		{
			InfoWindowDisplay( QString::fromLocal8Bit("相机成功启动.") );
			connect(m_pcontroller->GetObserverCamera(),SIGNAL(CameraListChangedSignal(int)),
				this,SLOT(onCamChange(int)));
			CamOpen();
		}
		else
		{
			ErrorWindowDisplay( QString::fromStdWString( ErrorCodeToMessage(err) ) );
		}
	}
	

	/*m_pscene = QSharedPointer<QGraphicsScene>( new QGraphicsScene() );
	m_pPixmapItem = new QGraphicsPixmapItem();
	m_pviewer = new Viewer( Ui::CameraViewClass::widgetPictureWindow );
	m_pviewer->setScene( m_pscene.data() );
	m_pscene->addItem( m_pPixmapItem );
	this->setCentralWidget( m_pviewer );
	QPixmap image("qt.png");
	m_pPixmapItem->setPixmap(image);
	m_pviewer->show();*/ //此方法暂时不考虑


	
}

CameraView::~CameraView()
{
	m_pcontroller->ShutDown();
	delete m_pcontroller;
	m_pcontroller = NULL;
}


void CameraView::CamStart( void )
{
	timeRecord.start();//计时开始

	if ( bIsCamOpen  && bIsStreaming )
	{
		//InfoWindowDisplay( "Frame Observer." );

		imgCount = 0; 
		emit FrameCountChange( imgCount );

		VmbErrorType res = m_pcontroller->StartContinousGettingImage();
		
		if ( res == VmbErrorSuccess )
		{
			int height = m_pcontroller->GetHeight();
			int width = m_pcontroller->GetWidth();
			double exposureTime = m_pcontroller->GetExposureTime();
			
			ui.lineEditHeight->setText( QString::number(height) );
			ui.lineEditWidth->setText( QString::number(width) );
			ui.lineEditExposureTime->setText( QString::number(exposureTime) );
			
			m_image = QImage( width,height,QImage::Format_Indexed8 );//注意宽高的位置，别弄反了


			
			connect(m_pcontroller->GetObserverFrames(),SIGNAL( FrameReceivedSignal(int) ),
				this,SLOT( onFrameReady(int) ));
		}
		
		bIsCamRun =  ( res == VmbErrorSuccess )? true:false;
		
		setPushButtonStopEnabled( bIsCamRun );

	}
}

void CameraView::CamStop()
{
	VmbErrorType res = m_pcontroller->StopContinousGettingImage();

	m_pcontroller->ClearObserverFrames();//清空缓存帧

	timeRecord.end();
	ui.lineEditFramePerSecond->setText( QString::number( imgCount/timeRecord.time() ) );

#ifndef NDEBUG
	std::cout<<"Cost time:"<<timeRecord.time()<<"s"<<std::endl;
#endif

	
	//至少有一张图片,则可以保存图像
	ui.pushButtonSave->setEnabled( imgCount >= 1 );
	

	bIsCamRun =  ( res == VmbErrorSuccess )? false:true;
	setPushButtonStopEnabled( bIsCamRun );

	if( ui.checkBoxProcess->isChecked() )
	{
		std::vector<double> Data;
		Data = m_pcontroller->CirclePoint();
		if ( Data.size() == 4 )//4个参数 x，y，r1， r2
		{
			//std::vector<double>::iterator it = Data.begin();
			ui.lineEditX->setText( QString::number(Data[0], 'f', 1) );
			ui.lineEditY->setText( QString::number(Data[1], 'f', 1) );
			ui.lineEditRadius1->setText( QString::number(Data[2], 'f', 1) );
			ui.lineEditRadius2->setText( QString::number(Data[3], 'f', 1) );
			ui.lineEditRadiusError->setText( QString::number(Data[3] - Data[2], 'f', 1) );
		}
	}
	//m_image = QImage();//可以补充拟合圆的图

}


void CameraView::setPushButtonStartEnabled( bool m)
{
	if ( bIsCamOpen )
	{
		ui.pushButtonStart->setEnabled( m );
		ui.pushButtonStop->setEnabled( !m );
	}

}


void CameraView::setPushButtonStopEnabled( bool m)
{
	//InfoWindowDisplay("pushButton Stop");
	ui.pushButtonStop->setEnabled( m );
	ui.pushButtonStart->setEnabled( !m );

}

bool CameraView::isStreamingAvailable( void )
{
	FeaturePtr feature;
	m_pCam->GetFeatureByName("StreamID", feature);
	return (feature == NULL)? false:true;
}

void CameraView::createConnects( void )
{
	connect(ui.lineEditImgNumber,SIGNAL(editingFinished()),this,SLOT(onImgNumberChange()));
	connect(ui.lineEditExposureTime,SIGNAL(editingFinished()),this,SLOT(onExposureTimeChange()));
	connect(this,SIGNAL(FrameCountChange(int)),this,SLOT(onImgCountChange(int)));//注意信号发送的位置和槽接受的位置
	connect(this,SIGNAL(CenterChange(const cv::Point2f&)),this,SLOT(onCenterChange(const cv::Point2f&)));//圆心位置实时更新显示
	connect(ui.actionTest,SIGNAL(triggered()),this,SLOT(testCenter()));
	connect(ui.actionCircle,SIGNAL(triggered()),this,SLOT(testCircle()));
	connect(ui.actionAbout,SIGNAL(triggered()),this,SLOT(About()));
}

void CameraView::InfoWindowDisplay( const QString& str )
{
	ui.textBrowserInfo->append(str);
}

void CameraView::ErrorWindowDisplay( const QString& str )
{
	ui.textBrowserError->append(str);
}


void CameraView::CamInfoDisplay (const CameraPtr m_pCam )
{
	std::string strID;
	std::string strName;
    std::string strModelName; 
    std::string strInterfaceID;

	std::ostringstream ErrorStream;

	VmbErrorType errID,errName,errModel,errInterfaceID;

	errID = m_pCam->GetID(strID);
	if(VmbErrorSuccess != errID)
	{
		ErrorStream << "[Error in getting camera ID.Error Code:" << errID<<"-";
		std::wcout<<ErrorCodeToMessage(errID)<<std::endl;
		strID = ErrorStream.str();
		ErrorWindowDisplay(  QString::fromStdString(strID) );
	}
	else
		InfoWindowDisplay(  QString::fromStdString("Camera ID:"+ strID) );

	errName = m_pCam->GetName(strName);
	if(VmbErrorSuccess != errName)
	{
		ErrorStream << "[Error in getting camera name.Error Code:" << errName<<"-";
		std::wcout<<ErrorCodeToMessage(errName)<<std::endl;
		strName = ErrorStream.str();
		ErrorWindowDisplay(  QString::fromStdString(strName) );
	}
	else
		InfoWindowDisplay( QString::fromStdString("Camera Name:"+ strName) );

	errModel = m_pCam->GetModel(strModelName);
	if(VmbErrorSuccess != errModel)
	{
		ErrorStream << "[Error in getting camera model name.Error Code:" << errModel<<"-";
		std::wcout<<ErrorCodeToMessage(errModel)<<std::endl;
		strModelName = ErrorStream.str();
		ErrorWindowDisplay(  QString::fromStdString(strModelName) );
	}
	else
		InfoWindowDisplay( QString::fromStdString("Camera Model Name:"+ strModelName) );

	/*errInterfaceID = m_pCam->GetInterfaceID(strInterfaceID);
	if(VmbErrorSuccess != errInterfaceID)
	{
		ErrorStream << "[Error in getting camera interface ID.Error Code:" << errInterfaceID<<"-";
		std::wcout<<ErrorCodeToMessage(errInterfaceID)<<std::endl;
		strInterfaceID = ErrorStream.str();
		ErrorWindowDisplay(  QString::fromStdString(strInterfaceID) );
	}
	else
		InfoWindowDisplay( QString::fromStdString("Camera InterfaceID:" + strInterfaceID ) );*/ //显示"本地连接"，由于中文，未处理好，成乱码，先略去

}

void CameraView::PictureWindowDisplay(QImage& image)
{

	//显示过程急需改进，实时性不好,原因在于图像行列错误导致的问题
	/*m_pscene->setSceneRect(0,0,image.width(),image.height());//Scene和View配合显示图像的方法
	m_pixmap = m_pixmap.fromImage(image);
	m_pscene->addPixmap(m_pixmap);

	m_pviewer->setScene( m_pscene.data() );
	m_pviewer->show();*/
	//Pixmap(0,0,sWidth,sHeight,m_pixmap);*/

	/*QLabel* label = new QLabel();
	//label->resize( image.width(), image.height() );//label显示图像方法
	label->resize( ui.scrollAreaPic->width()-20, ui.scrollAreaPic->height()-20 );
	const QSize s = label->size();
	label->setPixmap( QPixmap::fromImage( image ).scaled(s.width(),s.height(),Qt::KeepAspectRatio ) );
	ui.scrollAreaPic->setWidget(label);
	*/
	ui.scrollAreaPic->setWidget( ui.labelPicShow);
	//ui.labelPicShow->resize( image.width(), image.height() );//label显示图像方法
	ui.labelPicShow->resize( ui.scrollAreaPic->width()-20, ui.scrollAreaPic->height()-20 );
	const QSize s = ui.labelPicShow->size();
	ui.labelPicShow->setPixmap( QPixmap::fromImage( image ).scaled(s.width(),s.height(),Qt::KeepAspectRatio ));
	
#ifndef NDEBUG
	std::cout<<image.width()<<"X"<<image.height()<<std::endl; 
	//std::cout<<s.width()<<"X"<<s.height()<<std::endl; 
#endif

	

}

void CameraView::PictureWindowDraw(const std::vector<cv::Point2d>& point,const std::vector<double>& data )
{
	const int width = 3384;
	const int height = 2710;
	//QImage image(width,height,QImage::Format_Indexed8);
	cv::Mat mat(height,width,CV_8UC1);
	//cv::Mat mat = m_pcontroller->cvQImage2Mat(image);

	std::vector<cv::Point2d>::const_iterator it = point.begin();
	for(; it != point.end(); ++it)
	{
		cv::circle(mat,*it,4,cv::Scalar(0,0,0),-1,8);
	}

	cv::circle(mat,cv::Point2d(data[0],data[1]),data[2],cv::Scalar(0,0,0),2,8);
	cv::circle(mat,cv::Point2d(data[0],data[1]),data[3],cv::Scalar(0,0,0),2,8);
	QImage image = m_pcontroller->cvMat2QImage(mat);
	PictureWindowDisplay(image);
	emit CenterChange(cv::Point2d(data[0],data[1]));
}

void CameraView::onFrameReady(int status)//图像实时处理显示
{

#ifndef NDEBUG
	std::cout<<"onFrameReady\n";
#endif

	 if ( bIsStreaming == true)
	 {
		 FramePtr frame = m_pcontroller->GetFrame();

		 assert( frame.get() != NULL );//

		 
		 if ( status == VmbFrameStatusComplete )
		 {
			 m_pcontroller->SaveFrame( frame );//存储图像到FramePtrVector;

			 VmbUchar_t* Imagebuffer;
			 //std::vector<cv::Mat> image;
			 VmbErrorType res = (frame).get()->GetImage(Imagebuffer);
			 if(res == VmbErrorSuccess)
			 {
				 VmbUint32_t nSize;
				 res = (frame).get()->GetImageSize(nSize);
				 if(res == VmbErrorSuccess)
				 {
					 bool copySuccess = false;
					 VmbPixelFormatType ePixelFormat = m_pcontroller->GetPixelFormat();
					
					// if ( Imagebuffer != NULL )
					//	 std::cout<<"Imagebuffer is not null.\n";

					 copySuccess = CopyToImage(Imagebuffer,ePixelFormat,m_image);
					 if ( copySuccess )
					 {
						 imgCount++;
						 emit FrameCountChange( imgCount );
					 }
				 }
				 
				 if ( ui.checkBoxProcess->isChecked() )//若勾选图像处理，则
				 {
					 cv::Point2d tmpCenter(-1,-1);
					 cv::Mat tmp = m_pcontroller->cvQImage2Mat( m_image );
					 tmpCenter = m_pcontroller->LaserPoint( tmp );   //进行图像处理,获取中心点
					 m_image = m_pcontroller->cvMat2QImage( tmp );

					 std::cout<< imgCount<<"、 坐标："<<tmpCenter.x<<" "<<tmpCenter.y<<std::endl;
					 if ( tmpCenter.x != -1 && tmpCenter.y != -1 )
						 emit CenterChange( tmpCenter );

				 }

				 PictureWindowDisplay( m_image );

				 if ( imgCount >= m_pcontroller->GetImgNum() ) //拍摄m_ImgNum张相片停止，如果注释加上（1）句则实现连续拍摄
					 emit CamStop();				
				
			}
		 }

		 //m_pcontroller->QueueFrame( frame );//(1),连续拍摄功能，将帧重新排队
	 }	
}

bool CameraView::CopyToImage( VmbUchar_t* pbuffer,VmbPixelFormatType ePixel, QImage &image )
{
#ifndef NDEBUG
	std::cout<< "CopyToImage function\n";
#endif
	const int Height = m_pcontroller->GetHeight();
	const int Width = m_pcontroller->GetWidth();
	VmbImage  SourceImage,DestImage;
	//QImage DestImage(Width, Height, QImage::Format_Indexed8 );
	VmbError_t err;

	SourceImage.Size    = sizeof( SourceImage );
    DestImage.Size      = sizeof( DestImage );

	err = VmbSetImageInfoFromPixelFormat(ePixel,Width,Height, &SourceImage );
	if ( err != VmbErrorSuccess )
	{
		
		ErrorWindowDisplay( QString::fromStdWString( ErrorCodeToMessage(err) ) );
		//return;
	}
	
	QString OutputFormat = "Mono8_REC601";
	err = VmbSetImageInfoFromString(OutputFormat.toStdString().c_str(),
		static_cast<VmbUint32_t>( OutputFormat.length() ),
		static_cast<VmbUint32_t> ( Width ),
		static_cast<VmbUint32_t> ( Height ),
		&DestImage);
	SourceImage.Data = pbuffer;
	DestImage.Data = image.bits(); //获取图像的首地址
	                               //byteCount()图像总字节，bytePerLine()图像每行总字节

	if ( VmbErrorSuccess != err )
	{
		ErrorWindowDisplay( tr("could not set info from string :")
			+QString::fromStdWString( ErrorCodeToMessage(err) ) );
		//return;
	}

	//if (SourceImage.Data != NULL)
	//	std::cout<<"SourceImage is not NULL.\n";

	err = VmbImageTransform(&SourceImage, &DestImage,NULL,0 );//图像转换
	//VmbImageTransform( convertedImage, m_pFrame.data(), m_nWidth, m_nHeight, m_Format);用此函数

	if ( VmbErrorSuccess != err )
	{
		ErrorWindowDisplay( tr("could not transform image :")
			+QString::fromStdWString( ErrorCodeToMessage(err) ) );
		return false;
	}
	else
		return true;
}


void CameraView::SaveImageToFile()
{
	std::cout<<"SaveImageToFile ."<<std::endl;
	m_pcontroller->WriteToFile();//保存图像

}

void CameraView::onCamChange(int reason)
{
	InfoWindowDisplay("Camera Changed.");
	if ( UpdateTriggerPluggedIn == reason)
	{
		InfoWindowDisplay("Camera Open.");
		CamOpen();
	}
	else if ( UpdateTriggerPluggedOut == reason )
	{
		//需要补充判断，以处理相机正在运行的过程中松动的情况，3/2
		bIsCamOpen = false;
		setPushButtonStartEnabled(false);
		InfoWindowDisplay("Camera is disconnected.");
	}

}


QString CameraView::GetCameraID( void )
{
	return QString::fromStdString( m_pcontroller->GetCameraID() );
}


void CameraView::CamOpen( void )
{
	m_pCam = m_pcontroller->GetCamera();
	
	if ( m_pCam != NULL )
	{
		InfoWindowDisplay( QString::fromLocal8Bit("相机连接."));
		VmbErrorType err = m_pcontroller->OpenCamera();
		m_OpenError = err;
	}
		
	if ( m_OpenError != VmbErrorSuccess )
	{
		ErrorWindowDisplay( QString::fromStdWString( ErrorCodeToMessage(m_OpenError) ) );
	}
	else
	{
		InfoWindowDisplay( QString::fromLocal8Bit("相机打开.") );
		m_pcontroller->ParamReady();
		CamInfoDisplay( m_pCam );
		bIsCamOpen = true;
		bIsStreaming = isStreamingAvailable();
		setPushButtonStartEnabled( bIsStreaming );
		ui.checkBoxProcess->setEnabled( bIsStreaming );
		ui.checkBoxProcess->click();
		connect( ui.pushButtonStart,SIGNAL(clicked()),this,SLOT( CamStart() ) );
		connect( ui.pushButtonStop,SIGNAL(clicked()),this,SLOT ( CamStop() ) );
		connect(ui.pushButtonSave,SIGNAL(clicked()),this,SLOT(SaveImageToFile()));
	}
}

void CameraView::onImgNumberChange(  )
{
	const QString& imgNumber = ui.lineEditImgNumber->text();
	m_pcontroller->imgNumberChange( imgNumber.toInt() );
	ui.lineEditImgNumber->setText( imgNumber );
}

void CameraView::onExposureTimeChange(  )
{
	const QString& ExposureTime = ui.lineEditExposureTime->text();
	ui.lineEditExposureTime->setText( ExposureTime );
	m_pcontroller->ExposureTimeChange( ExposureTime.toInt() );
}


void CameraView::onImgCountChange( int count)
{
	ui.lineEditFrame->setText( QString::number(count,10) ); //10进制显示
}

void CameraView::onCenterChange(const cv::Point2f& p )
{
	ui.lineEditX->setText( QString::number(p.x, 'f', 1) );//以1位小数显示
	ui.lineEditY->setText( QString::number(p.y, 'f', 1) );
}


void CameraView::testCenter()
{
	QString path = QFileDialog::getOpenFileName(this,
		tr("Open image file"),tr("."),tr("Image files(*.bmp *.jpg)") );
	//没有打开，则退出
	if( path.length() == 0 ) 
		return;

	QImage image(path);

	cv::Point2f tmpCenter(-1,-1);
	
	cv::Mat tmp = m_pcontroller->cvQImage2Mat( image );
	tmpCenter = m_pcontroller->LaserPoint( tmp );   //进行图像处理,获取中心点
	image = m_pcontroller->cvMat2QImage( tmp );


	
	PictureWindowDisplay(image);
	std::cout<< tmpCenter.x<<" "<<tmpCenter.y<<std::endl;

	if ( tmpCenter.x != -1 && tmpCenter.y != -1 )
		emit CenterChange( tmpCenter );

}


void CameraView::testCircle()
{
	QString path = QFileDialog::getOpenFileName(this,
		tr("Get center points file"),tr("."),tr("Text files(*.txt *.csv)") );

	if( path.length() == 0 ) 
		return;

	const int width = 3384;
	const int height = 2710;
	std::vector<cv::Point2d> Point;
	QFile file(path);
	if( !file.open( QIODevice::ReadOnly | QIODevice::Text) )
		return;

	QTextStream ts(&file);
	while( !ts.atEnd() )
	{
		cv::Point2f temp;
		ts>>temp.x>>temp.y;
		if( temp.x >0 && temp.x< width && temp.y > 0 && temp.y < height )
			Point.push_back(temp);
	}

	std::vector<double> data = m_pcontroller->CirclePoint(Point);
	PictureWindowDraw(Point,data);
}



void CameraView::About()
{
	QString sAbout(tr("CameraView is an application for Laser Point Detecting."));
	QMessageBox::about(this,tr("About CameraView"),sAbout);
}