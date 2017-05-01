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