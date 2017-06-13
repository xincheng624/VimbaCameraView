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

			bQueueMark = false; //����emit�ĺ�������һ�ź�δ�������򽫸�֡�����Ŷ�
			
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
		//Frame* payloadsize = new Frame(nPLS);//1,1��2��ʲô��ͬ��Ϊʲô2��ȷ��1����return 0ǰ���� ԭ��Frame�ǹ���ָ�룬��ˣ�����Ҫ�Լ����ա�
		for(FramePtrVector::iterator iter = Frames.begin();iter!=Frames.end();iter++)
		{
			(*iter).reset(new Frame(nPLS));//2
			//(*iter).reset(payloadsize);//1 
			//res = m_pCamera->AnnounceFrame(*iter);//��ȷ�����ַ�����Ҫ��ѭ�������𣿲���Ҫ��
		}
		//delete payloadsize;//1����Ҫ��ʼ��ͼ����ʱδ�õ��˺���
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