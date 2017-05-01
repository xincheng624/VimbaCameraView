#include "ImageProcess.h"
#include <iostream>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\imgproc\imgproc_c.h>
using namespace cv;

Point2f ImageProcess::center(Mat& img)
{
	//cvtColor(img,img,CV_BGR2GRAY);
	Mat dst=Mat(img.size(),img.type());
	threshold(img,dst,0,255,CV_THRESH_TOZERO|CV_THRESH_OTSU);
	/*threshold(img,img,0,255,CV_THRESH_TOZERO|CV_THRESH_OTSU);
	Moments m = moments(img);*/

	Moments m = moments(dst);
	Point2d cen;
	cen.x = m.m10/m.m00;//求重心
	cen.y = m.m01/m.m00;

	//std::cout<<"x:"<<cen.x<<std::endl;
	//std::cout<<"y:"<<cen.y<<std::endl;

	return cen;
}

void ImageProcess::DrawCross(Mat& img,Point2f xy)
{
	line(img,Point2f(xy.x-30,xy.y),Point2f(xy.x+30,xy.y),Scalar(125),2,8);//画横线
	line(img,Point2f(xy.x,xy.y-30),Point2f(xy.x,xy.y+30),Scalar(125),2,8);//画竖线
}

double dist(TPoint p1,TPoint p2)//两点的距离，std里面也有distance函数,因此改成dist
	                            //，其实可以封装一下的
{
	TPoint res;
	res.x = p1.x - p2.x;
	res.y = p1.y - p2.y;
	return sqrt(res.x*res.x+res.y*res.y);
}

double TriArea(TTriangle t)
{
	TPoint res1,res2;
	res1 = t.t[1]-t.t[0];
	res2 = t.t[2]-t.t[0];
	return fabs(res1.x*res2.y-res2.x*res1.y);//叉乘求三角形面积
}

TCircle circumcircle(TTriangle t)//三角形外接圆
{
	TCircle res;
	double a,b,c,c1,c2;
	double xA,yA,xB,yB,xC,yC;
	a = dist(t.t[0],t.t[1]);
	b = dist(t.t[1],t.t[2]);
	c = dist(t.t[2],t.t[0]);

	xA = t.t[0].x;
	yA = t.t[0].y;
	xB = t.t[1].x;
	yB = t.t[1].y;
	xC = t.t[2].x;
	yC = t.t[2].y;

	c1 = (xA * xA + yA * yA - xB * xB - yB * yB) / 2;  
    c2 = (xA * xA + yA * yA - xC * xC - yC * yC) / 2; 

	res.center.x = (c1 * (yA - yC) - c2 * (yA - yB)) / ((xA - xB) * (yA - yC) - (xA - xC) * (yA - yB));  
    res.center.y = (c1 * (xA - xC) - c2 * (xA - xB)) / ((yA - yB) * (xA - xC) - (yA - yC) * (xA - xB));
	return res;
}

const int MaxN = 250;
TCircle refreshCir;
TPoint XY[MaxN];

TCircle CircleCase(int PointNum,TTriangle p)
{
	TCircle res;
	if (PointNum == 0)
		res.r = -1;
	else if (PointNum == 1)
	{
		res.center = p.t[0];
		res.r = 0;
	}
	else if (PointNum == 2)
	{
		res.center.x = (p.t[0].x+p.t[1].x)/2;
		res.center.y = (p.t[0].y+p.t[1].y)/2;
		res.r = dist(p.t[0],p.t[1])/2;
	}
	else if (PointNum == 3)
	{
		res = circumcircle(p);
	}

	return res;
}

void MinimalCircle(int num,int PointNum,TTriangle Cir)
{
	refreshCir = CircleCase(PointNum,Cir);
	if (PointNum == 3)
		return;
	for(int i=1;i<num;i++)
	{
		if( dist(XY[i],refreshCir.center) > refreshCir.r )
		{
			Cir.t[PointNum] = XY[i]; 
			MinimalCircle(num-1,PointNum+1,Cir);
		}
	}
}

void ImageProcess::CirclePoint(std::vector<cv::Point2f> point)
{
	int num=0;
	XY[0].x = 0;
	XY[0].y = 0;
	for(std::vector<cv::Point2f>::iterator iter=point.begin();iter != point.end();++iter)
	{
		++num;
		XY[num].x = (*iter).x;
		XY[num].y = (*iter).y;
	}
	TTriangle cir ={};
	MinimalCircle(num,0,cir);

	//std::cout<<"圆心X: "<<refreshCir.center.x<<"   圆心Y: "<<refreshCir.center.y<<std::endl;
	//std::cout<<"最大半径R: "<<refreshCir.r<<std::endl;
	//CCenter.x = refreshCir.center.x;
	//CCenter.y = refreshCir.center.y;
	//rminmax.y = refreshCir.r;
	CircleData.push_back(refreshCir.center.x);
	CircleData.push_back(refreshCir.center.y);


	double r;
	double min = 10000;
	double max = -1;
	TPoint cen = refreshCir.center;
	for (int i=1;i<=num;i++)
	{
		r = sqrt((XY[i].x-cen.x)*(XY[i].x-cen.x)+(XY[i].y-cen.y)*(XY[i].y-cen.y));
		if ( r < min )
			min = r;
		//if (r>max)
		//	max = r;
	}
	//std::cout<<"最小半径： "<<min<<std::endl<<"回转误差："<<refreshCir.r-min<<std::endl;
	//rminmax.x = min;
	CircleData.push_back(min);
	CircleData.push_back( refreshCir.r );
	//CircleData.push_back( refreshCir.r - min );
/*	for (int i=1;i<=num;i++)
	{
		r = sqrt((XY[i].x-cen.x)*(XY[i].x-cen.x)+(XY[i].y-cen.y)*(XY[i].y-cen.y));
		if (abs(r-min)<0.1)
			std::cout<<"min- a["<<i<<"]:"<<"x"<<XY[i].x<<" y:"<<XY[i].y<<" r:"<<r<<std::endl;
		if (abs(r-max)<0.1)
			std::cout<<"max- a["<<i<<"]:"<<"x"<<XY[i].x<<" y:"<<XY[i].y<<" r:"<<r<<std::endl;
	}*/
}

std::vector<double> ImageProcess::GetCircleData()
{
	return CircleData;
}
