#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H
#include <opencv2\core\core.hpp>
#include <vector>
using cv::Point2f;
class ImageProcess
{
	//Point2f CCenter;
	//Point2f rminmax;
	//float roundness;
	std::vector<double> CircleData;
	//可以补充一些数据用于存储计算后的数据，用于OpenCVshow画点和最小环的图
public:
	ImageProcess(){};
	cv::Point2f center(cv::Mat& img);

	void DrawCross(cv::Mat& img,cv::Point2f xy);
	void CirclePoint(std::vector<cv::Point2f> point);
	std::vector<double> GetCircleData();
	//Point2f GetCenter();
	//Point2f GetR();
	//float GetRoundness();
};


class TPoint
{
public:
	double x,y;
	TPoint operator-(TPoint& a)
	{
		TPoint p1;
		p1.x = x - a.x;
		p1.y = y - a.y;
		return p1;
	}
};

class TCircle
{
public:
	TPoint center;
	double r;
};

class TTriangle
{
public:
	TPoint t[3];
};





#endif