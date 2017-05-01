#include "CameraObserver.h"

namespace AVT{
namespace VmbAPI{

void CameraObserver::CameraListChanged( CameraPtr camera, UpdateTriggerType reason )
{
	if ( UpdateTriggerPluggedIn == reason || UpdateTriggerPluggedOut == reason)
	{
		emit CameraListChangedSignal(reason);
	}
}

}}