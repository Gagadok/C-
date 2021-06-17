#pragma once
#ifndef WORKING_WITH_FILES_H
#define WORKING_WITH_FILES_H

#include <string>
#include <queue>
#include <fstream>
#include <iostream>
using namespace std;

class WorkingWithFiles
{
public:
	queue <string> GetData();
	bool Loading(string);
	bool Write(string, queue <string>);

private:
	queue <string> data;
};

#endif