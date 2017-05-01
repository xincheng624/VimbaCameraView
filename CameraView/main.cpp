#include "cameraview.h"
#include <QtGui/QApplication>

using namespace AVT::VmbAPI;


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CameraView w;
	w.show();
	return a.exec();
}


