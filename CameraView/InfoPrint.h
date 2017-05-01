#ifndef AVT_VMBAPI_INFOPRINT_H
#define AVT_VMBAPI_INFOPRINT_H

//#include "VimbaCPP/Include/VimbaCPP.h"

namespace AVT{
namespace VmbAPI{

class InfoPrint
{	
public:
	InfoPrint();
	~InfoPrint();
	//void Print(CameraPtrVector cameras) const;
	std::string PrintCameraInfo (const CameraPtr & camera);
//private:
	//CameraPtrVector cameras;
};

}}

#endif