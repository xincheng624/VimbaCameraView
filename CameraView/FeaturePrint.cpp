#include "FeaturePrint.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
//#include <locale>//wcout

#include "Common/ErrorCodeToMessage.h"



namespace AVT{
namespace VmbAPI{

FeaturePrint::FeaturePrint():sys(VimbaSystem::GetInstance())
{
}

FeaturePrint::~FeaturePrint()
{
}

void FeaturePrint::GetCamera(const CameraPtr &Camera)
{
	if(Camera != NULL)
		pCamera = Camera;
}

std::ofstream out;

VmbErrorType PrintGetValueErrorMessage ( const VmbErrorType err )
{
    if ( VmbErrorSuccess != err )
    {
        std::cout << "Could not get feature value.Error code: " << err << " (";
		std::wcout<<ErrorCodeToMessage( err ) << ")" << "\n";
    }

    return err;
}

void PrintFeatureValue(const FeaturePtr &feature)
{
	VmbFeatureDataType  eType;
    VmbErrorType err = feature->GetDataType( eType );
	//std::ofstream out("Features.txt",std::ios::app);//ios::app尾部追加,2次打开导致先输出Num，再输出Value，Type，最后输出依次输出Feature Name等参数？具体机理不明，为改正问题将out改成全局变量了。
	if( VmbErrorSuccess != err )
    {
        std::cout << "[Could not get feature Data Type. Error code: " << err << "-";
		std::wcout<<ErrorCodeToMessage( err ) << "]"<<std::endl;
    }
	else
    {
        out << "/// Value          : ";
        switch( eType )
        {
            case VmbFeatureDataBool:
                {
                    VmbBool_t bValue;
                    err = feature->GetValue( bValue );
                    if ( VmbErrorSuccess == PrintGetValueErrorMessage( err ) )
                    {
                        out << bValue << "\n";
                    }
                    out << "/// Type           : Boolean\n";
                }
                break;
            case VmbFeatureDataEnum:
                {
                    std::string strValue;
                    err = feature->GetValue( strValue );
                    if ( VmbErrorSuccess == PrintGetValueErrorMessage( err ) )
                    {
                        out << strValue << "\n";
                    }
                    out << "/// Type           : Enumeration\n";
                }
                break;
            case VmbFeatureDataFloat:
                {
                    double fValue;
                    double fMin, fMax;
                    err = feature->GetValue( fValue );
                    if( VmbErrorSuccess == PrintGetValueErrorMessage( err ) )
                    {
                        out << fValue << "\n";
                    }

                    out << "/// Minimum        : ";
                    err = feature->GetRange( fMin, fMax );
                    if( VmbErrorSuccess == PrintGetValueErrorMessage( err ) )
                    {
						out << fMin << "\n";
                        out << "/// Maximum        : " << fMax << "\n";
                    }
                    out << "\n/// Type           : Double precision floating point\n";
                }
                break;
            case VmbFeatureDataInt:
                {
                    VmbInt64_t nValue;
                    VmbInt64_t nMin, nMax;
                    err = feature->GetValue( nValue );
                    if( VmbErrorSuccess == PrintGetValueErrorMessage( err ) )
                    {
                       out << nValue << "\n";
                    }

                    out << "/// Minimum        : ";
                    err = feature->GetRange( nMin, nMax );
                    if( VmbErrorSuccess == PrintGetValueErrorMessage( err ) )
                    {
                        out << nMin << "\n";
                        out << "/// Maximum        : " << nMax << "\n";
                    }
                    out << "/// Type           : Long long integer\n";
                }
                break;
            case VmbFeatureDataString:
                {
                    std::string strValue;
                    
                    err = feature->GetValue( strValue );
                    if( VmbErrorSuccess == PrintGetValueErrorMessage( err ) )
                    {
                        out << strValue << "\n";
                    }
                    out << "/// Type           : String\n";
                }
                break;
            case VmbFeatureDataCommand:
            default:
                {
                    out << "[None]" << "\n";
                    out << "/// Type           : Command feature\n";
                }
                break;
        }
	}

}

void PrintFeatures(const FeaturePtr &feature)
{
	std::string strName;  
	std::string strDisplayName; 
	std::string strToolTip; 
	std::string strDescription;
	std::string strCategory;
	std::string strSFNCNamespace; 
	std::string strUnit; 
		
	//std::ofstream out("Features.txt",std::ios::app);
	std::ostringstream ErrorStream;

	VmbErrorType err = feature->GetName( strName );
    if( VmbErrorSuccess != err )
    {
        ErrorStream << "[Could not get feature Name. Error code: " << err << "-";
		std::wcout<< ErrorCodeToMessage( err ) << "]";
        strName = ErrorStream.str();                 
    }

	err = feature->GetDisplayName( strDisplayName );
    if( VmbErrorSuccess != err )
    {
        ErrorStream << "[Could not get feature Display Name. Error code: " << err << "-";
		std::wcout<< ErrorCodeToMessage( err )  << "]"<<std::endl;
        strDisplayName = ErrorStream.str();
    }

	err = feature->GetToolTip( strToolTip );
    if( VmbErrorSuccess != err )
    {
        ErrorStream << "[Could not get feature Tooltip. Error code: " << err << "-";
		std::wcout<< ErrorCodeToMessage( err ) << "]"<<std::endl;
        strToolTip = ErrorStream.str();
    }

	err = feature->GetDescription( strDescription );
    if( VmbErrorSuccess != err )
    {
        ErrorStream << "[Could not get feature Description. Error code: " << err << " (";
		std::wcout<< ErrorCodeToMessage( err ) << "]"<<std::endl;
        strDescription = ErrorStream.str();
    }

	err = feature->GetCategory( strCategory );
    if( VmbErrorSuccess != err )
    {
        ErrorStream << "[Could not get feature Category. Error code: " << err << "-";
		std::wcout<< ErrorCodeToMessage( err )  << "]"<<std::endl;
        strCategory = ErrorStream.str();
    }

	err = feature->GetSFNCNamespace( strSFNCNamespace );
    if( VmbErrorSuccess != err )
    {
        ErrorStream << "[Could not get feature SNFC Namespace. Error code: " << err << "-";
		std::wcout<< ErrorCodeToMessage( err )  << "]"<<std::endl;
        strSFNCNamespace = ErrorStream.str();
    }

	err = feature->GetUnit( strUnit );
    if( VmbErrorSuccess != err )
    {
        ErrorStream << "[Could not get feature Unit. Error code: " << err << " (";
		std::wcout<< ErrorCodeToMessage( err ) << ")" << "]"<<std::endl;
        strUnit = ErrorStream.str();
    }
	static int count = 0;
	out <<"Num:"<<++count<<std::endl;
	out << "/// Feature Name   : " << strName             << "\n";
    out << "/// Display Name   : " << strDisplayName      << "\n";
    out << "/// Tooltip        : " << strToolTip          << "\n";
    out << "/// Description    : " << strDescription      << "\n";
    out << "/// SNFC Namespace : " << strSFNCNamespace    << "\n";
    out << "/// Unit           : " << strUnit             << "\n";
    
    PrintFeatureValue( feature );

}
void FeaturePrint::Print(std::string CameraID)
{
	FeaturePtrVector features;

	//VmbErrorType err = pCamera->Open(VmbAccessModeFull);
	//if(VmbErrorSuccess == err)
	//{
	std::cout<<"Printing all features of camera with ID:"<< CameraID<<std::endl;
	if(NULL != pCamera)
	{
		VmbErrorType err = pCamera->GetFeatures(features);
		if(VmbErrorSuccess == err)
		{
			std::cout<<"Features Number:"<<features.size()<<std::endl;
			std::for_each(features.begin(),features.end(),PrintFeatures);
		}
		//pCamera->Close();
	}
	else
	{
		std::cout<<"No Camera for FeaturePrint."<<std::endl;
	}
//}
}

void FeaturePrint::Print(std::vector<const char*> featuresname)
{
	if(featuresname.size() != 0)
	{
		out.open("Features.txt",std::ios::app);
		for(std::vector<const char*>::const_iterator iter=featuresname.begin();iter!=featuresname.end();iter++)
		{
			PrintFeatureValueByName(*iter);
		}
		out.close();
	}
	else
		std::cout<<"No feature names for print value by name."<<std::endl;
}

void FeaturePrint::PrintFeatureValueByName(const char* FeatureName)
{
	FeaturePtr pFeature;
	if(FeatureName != NULL)
	{
		if(pCamera != NULL)
		{
			VmbErrorType err = pCamera->GetFeatureByName(FeatureName,pFeature);
			if (VmbErrorSuccess == err)
			{
				out<<FeatureName <<":"<<std::endl;
				PrintFeatureValue(pFeature);
			}
			else
			{
				std::cout<< "Error in GetFeatureByName.Error Code:"<<err;
				std::wcout<<ErrorCodeToMessage(err)<<std::endl;
			}
		}
		else
			std::cout<<"No Camera for getting feature by name."<<std::endl;
	}
	else
	{
		std::cout<<"No FeatureName for getting feature by name."<<std::endl;
	}
}

}}