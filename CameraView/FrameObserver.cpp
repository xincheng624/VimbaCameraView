#include "FrameObserver.h"
#include <iostream>
#include "Qt\qimage.h"

namespace AVT{
namespace VmbAPI{


void FrameObserver::FrameReceived(const FramePtr pFrame)
{
	if(pFrame != NULL)
	{
		std::cout<<"FrameReceived constructor."<<std::endl;
		bool bQueueMark = true;
		VmbFrameStatusType eReceiveStatus;
		//static int count = 0;
		
		if( VmbErrorSuccess == pFrame->GetReceiveStatus( eReceiveStatus ) 
			&&	eReceiveStatus == VmbFrameStatusComplete  )
		{
			
			m_FramesMutex.lock();

			if ( pFrame != NULL )
				std::cout<< "pFrame is filled."<<std::endl;
			
			m_Frames.push( pFrame );

			std::cout<<"After Push m_Frames size is :"<< m_Frames.size() <<std::endl;

			m_FramesMutex.unlock();
			
			emit FrameReceivedSignal( eReceiveStatus );

			bQueueMark = false; //放在emit的后面是万一信号未发出，则将该帧继续排队
			
		}
		
		if( true == bQueueMark )
		{
			m_pCamera->QueueFrame(pFrame);
		}
	}
	
}

/*void FrameObserver::SetFrame()
{	
	std::cout<<"SetFrame constructor."<<std::endl;
	FeaturePtr pfeature;
	VmbInt64_t nPLS;
	if(m_pCamera != NULL)
	{
		VmbErrorType res = m_pCamera->GetFeatureByName("PayloadSize",pfeature); 
		pfeature->GetValue(nPLS);
		//Frame* payloadsize = new Frame(nPLS);//1,1和2有什么不同，为什么2正确，1则在return 0前报错， 原因，Frame是共享指针，因此，不需要自己回收。
		for(FramePtrVector::iterator iter = Frames.begin();iter!=Frames.end();iter++)
		{
			(*iter).reset(new Frame(nPLS));//2
			//(*iter).reset(payloadsize);//1 
			//res = m_pCamera->AnnounceFrame(*iter);//不确定此种方法需要遵循该流程吗？不需要。
		}
		//delete payloadsize;//1因不需要初始化图像，暂时未用到此函数
	}

}*/


FramePtr FrameObserver::GetFrames()
{
	m_FramesMutex.lock();

	FramePtr tmp;
	
	if( !m_Frames.empty())
	{
		std::cout<<"m_Frames size:"<< m_Frames.size() <<std::endl;
		tmp = m_Frames.front();
		m_Frames.pop();
	}
	m_FramesMutex.unlock();

	return tmp;
}

void FrameObserver::ClearFrames()
{
	m_FramesMutex.lock();
	//std::cout<<"ClearFrames constructor."<<std::endl; 
	std::queue<FramePtr> empty;

	swap(m_Frames, empty);

	m_FramesMutex.unlock();
}

}}