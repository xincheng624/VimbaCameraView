#ifndef TIMERECORD_H
#define TIMERECORD_H

#include <time.h>

class TimeRecord
{
	clock_t startTime;
	clock_t endTime;
	double sumTime;
public:
	TimeRecord():startTime(0),endTime(0){}
	~TimeRecord(){}
	void start()
	{
		startTime = clock();
	}
	void end()
	{
		endTime = clock();
		sumTime = static_cast<double>(( endTime - startTime )) / CLOCKS_PER_SEC;
	}
	
	double time()
	{
		return sumTime;
	}
};



#endif