#pragma once
#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

#include <string>
#include <queue>
#include "Schedule.h"
using namespace std;

class DataProcessing
{
public:
	DataProcessing(queue <string>);
	queue <string> MakeSchedule();

private:
	const string POSH = "Posh";
	queue <Schedule> schedule;
	string* Split(string str, string delimiter);

	void MakePreliminarySchedule(queue <string>);
	int TripDuration(Schedule line);
	queue<Schedule> SortSchedule();
	string ScheduleToString(Schedule);
	string TimeStandard(int);
};

#endif