#ifndef AVT_VMBAPI_FEATUREPRINT_H
#define AVT_VMBAPI_FEATUREPRINT_H
#include <string>
#include "VimbaCPP/Include/VimbaCPP.h"

namespace AVT{
namespace VmbAPI{

class FeaturePrint
{
private:
	VimbaSystem &sys;
	CameraPtr pCamera;
public:
	FeaturePrint();
	~FeaturePrint();
	void GetCamera(const CameraPtr &Camera);
	void Print(std::string CameraID);
	void Print(std::vector<const char*> features);
	void PrintFeatureValueByName(const char* FeatureName);
};

}}

#endif