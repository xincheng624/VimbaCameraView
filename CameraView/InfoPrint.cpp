#include "APIController.h"
#include "InfoPrint.h"

#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

#include <locale>

//#include "VimbaCPP/Include/VimbaCPP.h"
//#include "Common/StreamSystemInfo.h" // <<ÔËËã·ûÖØÔØ£¡£¡
#include "Common/ErrorCodeToMessage.h"




namespace AVT{
namespace VmbAPI{



InfoPrint::InfoPrint()
{
}

InfoPrint::~InfoPrint()
{
}

std::string InfoPrint::PrintCameraInfo(const CameraPtr& camera)
{
	std::string strID;
	std::string strName;
    std::string strModelName; 
    std::string strInterfaceID;

	std::ostringstream ErrorStream;

	VmbErrorType err = camera->GetID(strID);
	if(VmbErrorSuccess != err)
	{
		ErrorStream << "[Error in getting camera ID.Error Code:" << err<<"-";
		std::wcout<<ErrorCodeToMessage(err)<<std::endl;
		strID = ErrorStream.str();
	}

	err = camera->GetName(strName);
	if(VmbErrorSuccess != err)
	{
		ErrorStream << "[Error in getting camera name.Error Code:" << err<<"-";
		std::wcout<<ErrorCodeToMessage(err)<<std::endl;
		strID = ErrorStream.str();
	}

	err = camera->GetModel(strModelName);
	if(VmbErrorSuccess != err)
	{
		ErrorStream << "[Error in getting camera model name.Error Code:" << err<<"-";
		std::wcout<<ErrorCodeToMessage(err)<<std::endl;
		strID = ErrorStream.str();
	}

	err = camera->GetInterfaceID(strInterfaceID);
	if(VmbErrorSuccess != err)
	{
		ErrorStream << "[Error in getting camera interface ID.Error Code:" << err<<"-";
		std::wcout<<ErrorCodeToMessage(err)<<std::endl;
		strID = ErrorStream.str();
	}

	std::cout << "Camera ID:"  << strID << std::endl;
	std::cout << "Camera Name:"  << strName << std::endl;
	std::cout << "Camera Model Name:"  << strModelName << std::endl;
	std::cout << "Camera InterfaceID:"  << strInterfaceID << std::endl;
}

}}