#ifndef VIEWER_H
#define VIEWER_H

#include <QGraphicsView.h>

class Viewer: public QGraphicsView
{
	Q_OBJECT
public:
	Viewer(QWidget * parent = NULL):QGraphicsView(parent) 
	{
		setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);  
	}
	~Viewer(){}


private:
	 QGraphicsScene     *m_Scene;
	 QGraphicsView      *m_View;


};


#endif