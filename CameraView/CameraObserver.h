#ifndef CAMERAOBSERVER_H
#define CAMERAOBSERVER_H

#include "VimbaCPP\Include\VimbaCPP.h"
#include "QObject.h"

namespace AVT{
namespace VmbAPI{

class CameraObserver:public QObject, public ICameraListObserver
{
	Q_OBJECT
public:
	virtual void CameraListChanged( CameraPtr camera, UpdateTriggerType reason );
	
signals:
	void CameraListChangedSignal( int reason );

};

}}

#endif