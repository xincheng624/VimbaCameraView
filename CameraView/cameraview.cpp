#include "cameraview.h"
#include <iostream>
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
	, m_pcontroller( new APIController() )
	, imgCount( 0 ) 
	//, m_pviewer(NULL)
{
	ui.setupUi(this);

	//m_pscene = QSharedPointer<QGraphicsScene>( new QGraphicsScene() );
	//m_pviewer = new QGraphicsView();

	createConnects();
	
	if ( m_pcontroller != NULL)
	{
		VmbErrorType err = m_pcontroller->StartUp();
		if ( err == VmbErrorSuccess )
		{
			InfoWindowDisplay( QString::fromLocal8Bit("����ɹ�����.") );
			connect(m_pcontroller->GetObserverCamera(),SIGNAL(CameraListChangedSignal(int)),
				this,SLOT(onCamChange(int)));
			CamOpen();
		}
		else
		{
			ErrorWindowDisplay( QString::fromStdWString( ErrorCodeToMessage(err) ) );
		}
	}
	


	
}

CameraView::~CameraView()
{
	m_pcontroller->ShutDown();
	delete m_pcontroller;
	m_pcontroller = NULL;
}


void CameraView::CamStart( void )
{
	timeRecord.start();//��ʱ��ʼ

	if ( bIsCamOpen  && bIsStreaming )
	{
		//InfoWindowDisplay( "Frame Observer." );

		imgCount = 0; 
		emit FrameCountChange( imgCount );

		VmbErrorType res = m_pcontroller->GetAsyPic();
		
		if ( res == VmbErrorSuccess )
		{
			int height = m_pcontroller->GetHeight();
			int width = m_pcontroller->GetWidth();
			double exposureTime = m_pcontroller->GetExposureTime();
			
			ui.lineEditHeight->setText( QString::number(height) );
			ui.lineEditWidth->setText( QString::number(width) );
			ui.lineEditExposureTime->setText( QString::number(exposureTime) );
			
			m_image = QImage( width,height,QImage::Format_Indexed8 );//ע���ߵ�λ�ã���Ū����


			
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

	m_pcontroller->ClearObserverFrames();//��ջ���֡

	timeRecord.end();
	ui.lineEditFramePerSecond->setText( QString::number( imgCount/timeRecord.time() ) );

#ifndef NDEBUG
	std::cout<<"Cost time:"<<timeRecord.time()<<"s"<<std::endl;
#endif

	
	//������һ��ͼƬ,����Ա���ͼ��
	ui.pushButtonSave->setEnabled( imgCount >= 1 );
	

	bIsCamRun =  ( res == VmbErrorSuccess )? false:true;
	setPushButtonStopEnabled( bIsCamRun );

	if( ui.checkBoxProcess->isChecked() )
	{
		std::vector<double> Data;
		Data = m_pcontroller->CirclePoint();
		if ( Data.size() == 4 )//4������ x��y��r1�� r2
		{
			//std::vector<double>::iterator it = Data.begin();
			ui.lineEditX->setText( QString::number(Data[0], 'f', 1) );
			ui.lineEditY->setText( QString::number(Data[1], 'f', 1) );
			ui.lineEditRadius1->setText( QString::number(Data[2], 'f', 1) );
			ui.lineEditRadius2->setText( QString::number(Data[3], 'f', 1) );
			ui.lineEditRadiusError->setText( QString::number(Data[3] - Data[2], 'f', 1) );
		}
	}
	//m_image = QImage();//���Բ������Բ��ͼ

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
	connect(this,SIGNAL(FrameCountChange(int)),this,SLOT(onImgCountChange(int)));
	connect(this,SIGNAL(CenterChange(cv::Point2f)),this,SLOT(onCenterChange(cv::Point2f)));//Բ��λ��ʵʱ������ʾ
	connect(ui.actionTest,SIGNAL(triggered()),this,SLOT(testStart()));
	connect(ui.actionAbout,SIGNAL(triggered()),this,SLOT(About()));
}

void CameraView::InfoWindowDisplay( const QString str )
{
	ui.textBrowserInfo->append(str);
}

void CameraView::ErrorWindowDisplay( const QString str )
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

	

}

void CameraView::PictureWindowDisplay(QImage image)
{


	/*m_pscene->setSceneRect(0,0,image.width(),image.height());//Scene��View�����ʾͼ��ķ���
	m_pixmap = m_pixmap.fromImage(image);
	m_pscene->addPixmap(m_pixmap);

	m_pviewer->setScene( m_pscene.data() );
	m_pviewer->show();*/

	//Pixmap(0,0,sWidth,sHeight,m_pixmap);*/


	//ui.labelPicShow->resize( image.width(), image.height() );//label��ʾͼ�񷽷�
	const QSize s = ui.labelPicShow->size();

#ifndef NDEBUG
	std::cout<<s.width()<<"X"<<s.height()<<std::endl; 
#endif

	ui.labelPicShow->setPixmap( QPixmap::fromImage( image ).scaled(s.width(),
		s.height(),Qt::KeepAspectRatioByExpanding ) );

}

void CameraView::onFrameReady(int status)//ͼ��ʵʱ������ʾ
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
			 m_pcontroller->SaveFrame( frame );//�洢ͼ��FramePtrVector;

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
				 
				 if ( ui.checkBoxProcess->isChecked() )//����ѡͼ������
				 {
					 cv::Point2f tmpCenter(-1,-1);
					 cv::Mat tmp = m_pcontroller->cvQImage2Mat( m_image );
					 tmpCenter = m_pcontroller->LaserPoint( tmp );   //����ͼ����,��ȡ���ĵ�
					 m_image = m_pcontroller->cvMat2QImage( tmp );

					 std::cout<< tmpCenter.x<<" "<<tmpCenter.y<<std::endl;
					 if ( tmpCenter.x != -1 && tmpCenter.y != -1 )
						 emit CenterChange( tmpCenter );

				 }

				 PictureWindowDisplay( m_image );

				 if ( imgCount == m_pcontroller->GetImgNum() ) //����m_ImgNum����Ƭֹͣ�����ע�ͼ��ϣ�1������ʵ����������
					 emit CamStop();
				
				
			}
		 }

		 //m_pcontroller->QueueFrame( frame );//(1),�������㹦�ܣ���֡�����Ŷ�
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
	DestImage.Data = image.bits(); //��ȡͼ����׵�ַ
	                               //byteCount()ͼ�����ֽڣ�bytePerLine()ͼ��ÿ�����ֽ�

	if ( VmbErrorSuccess != err )
	{
		ErrorWindowDisplay( tr("could not set info from string :")
			+QString::fromStdWString( ErrorCodeToMessage(err) ) );
		//return;
	}

	//if (SourceImage.Data != NULL)
	//	std::cout<<"SourceImage is not NULL.\n";

	err = VmbImageTransform(&SourceImage, &DestImage,NULL,0 );//ͼ��ת��
	//VmbImageTransform( convertedImage, m_pFrame.data(), m_nWidth, m_nHeight, m_Format);�ô˺���

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
	m_pcontroller->WriteToFile();//����ͼ��

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
		//��Ҫ�����жϣ��Դ�������������еĹ������ɶ������
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
		InfoWindowDisplay("Camera is connected.");
		VmbErrorType err = m_pcontroller->OpenCamera();
		m_OpenError = err;
	}
		
	if ( m_OpenError != VmbErrorSuccess )
	{
		ErrorWindowDisplay( QString::fromStdWString( ErrorCodeToMessage(m_OpenError) ) );
	}
	else
	{
		InfoWindowDisplay("Camera Start set.");
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

void CameraView::setBasicInfo( CameraPtr Cam )
{
	//ui.lineEditHeight->setText( QString::number( m_pcontroller->GetHeight()) );
	//ui.lineEditWidth->setText( QString::number( m_pcontroller->GetWidth()) );
}

void CameraView::onImgCountChange( int count)
{
	//std::cout<<count<<"////"<<std::endl;
	ui.lineEditFrame->setText( QString::number(count,10) ); //10������ʾ
}

void CameraView::onCenterChange( cv::Point2f p )
{
	ui.lineEditX->setText( QString::number(p.x, 'f', 1) );//��1λС����ʾ
	ui.lineEditY->setText( QString::number(p.y, 'f', 1) );
}


void CameraView::testStart()
{
	QString str = QFileDialog::getOpenFileName(this,
		"open image file",".","Image files(*.bmp *.jpg)" );
	
	QImage image(str);

	cv::Point2f tmpCenter(-1,-1);
	
	cv::Mat tmp = m_pcontroller->cvQImage2Mat( image );
	tmpCenter = m_pcontroller->LaserPoint( tmp );   //����ͼ����,��ȡ���ĵ�
	image = m_pcontroller->cvMat2QImage( tmp );
	
	PictureWindowDisplay(image);
	std::cout<< tmpCenter.x<<" "<<tmpCenter.y<<std::endl;

	if ( tmpCenter.x != -1 && tmpCenter.y != -1 )
		emit CenterChange( tmpCenter );

}

void CameraView::About()
{
	QString sAbout(tr("CameraView is an application for Laser Point Detecting."));
	QMessageBox::about(this,tr("About CameraView"),sAbout);
}