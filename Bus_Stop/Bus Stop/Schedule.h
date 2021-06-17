#pragma once
#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>
using namespace std;

struct Schedule
{
	string company;
	int hour_start;
	int minute_start;
	int hour_end;
	int minute_end;
};

#endif