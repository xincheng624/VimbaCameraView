#ifndef FRAMEOBSERVER_H
#define FRAMEOBSERVER_H

#include "VimbaCPP\Include\VimbaCPP.h"
#include <QObject.h>
#include <QMutex.h>
#include <queue>


namespace AVT{
namespace VmbAPI{
class FrameObserver:public QObject,virtual public IFrameObserver
{
	Q_OBJECT
public:
	FrameObserver::FrameObserver( CameraPtr pCamera ):IFrameObserver(pCamera)
	{
		//std::cout<<"FrameObserver constructor."<<std::endl;
		//std::cout<<"FrameSet start."<<std::endl;
	}

	virtual void FrameReceived( const FramePtr pFrame);
	//void SetFrame();
	FramePtr GetFrames();
	void ClearFrames();
	

signals:
	void FrameReceivedSignal( int status );

private:
	std::queue<FramePtr> m_Frames;  //先进先出
	//std::queue<FramePtr> Frames;
	//VmbUint32_t Imagesize;

	QMutex m_FramesMutex;
};



}}

#endif