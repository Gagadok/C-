#include "DataProcessing.h"

DataProcessing::DataProcessing(queue <string> data)
{
	MakePreliminarySchedule(data);
}

void DataProcessing::MakePreliminarySchedule(queue <string> data)
{
	Schedule line;
	string* split_string;
	string* time;

	while (!data.empty())
	{
		split_string = Split(data.front(), " ");
		data.pop();
		line.company = split_string[0];
		time = Split(split_string[1], ":");
		line.hour_start = stoi(time[0]);
		line.minute_start = stoi(time[1]);
		delete[] time;
		time = Split(split_string[2], ":");
		line.hour_end = stoi(time[0]);
		line.minute_end = stoi(time[1]);
		delete[] split_string;
		delete[] time;

		if (TripDuration(line) < 61)
		{
			schedule.push(line);
		}
	}
}

string* DataProcessing::Split(string str, string delimiter)
{
	int prev_pos = 0;
	int pos = 0;
	queue <string> split;
	string token;
	str = str + delimiter;
	while ((pos = str.find(delimiter, prev_pos)) != string::npos) {
		token = str.substr(prev_pos, pos - prev_pos);
		split.push(token);
		prev_pos = pos + delimiter.length();
	}

	int split_size = split.size();
	string* split_string = new string[split_size];
	for (int i = 0; i < split_size; i++)
	{
		split_string[i] = split.front();
		split.pop();
	}

	return split_string;
}

int DataProcessing::TripDuration(Schedule line)
{
	int min = 0;
	min = (line.hour_end * 60 + line.minute_end) - (line.hour_start * 60 + line.minute_start);

	return min;
}

queue<string> DataProcessing::MakeSchedule()
{
	queue <string> data;
	queue <string> grotty;
	queue<Schedule> sort_schedule = SortSchedule();
	Schedule tmp;
	while (!sort_schedule.empty())
	{
		tmp = sort_schedule.front();
		sort_schedule.pop();
		if (!sort_schedule.empty()) {
			if ((tmp.hour_start == sort_schedule.front().hour_start) && //Start at the same time
				(tmp.minute_start == sort_schedule.front().minute_start))
			{
				if (TripDuration(tmp) == TripDuration(sort_schedule.front())) //Start and duration are the same
				{
					if (tmp.company == POSH)
					{
						data.push(ScheduleToString(tmp));
						sort_schedule.pop();
					}
					else
					{
						if (sort_schedule.front().company == POSH)
						{
							data.push(ScheduleToString(sort_schedule.front()));
							sort_schedule.pop();
						}
						else
						{
							grotty.push(ScheduleToString(sort_schedule.front()));
							sort_schedule.pop();
						}
					}
				}
				else //The start is the same, the duration is different
				{
					if (TripDuration(tmp) > TripDuration(sort_schedule.front()))
					{
						if (sort_schedule.front().company == POSH)
						{
							data.push(ScheduleToString(sort_schedule.front()));
							sort_schedule.pop();
						}
						else
						{
							grotty.push(ScheduleToString(sort_schedule.front()));
							sort_schedule.pop();
						}
					}
					else
					{
						if (tmp.company == POSH)
						{
							data.push(ScheduleToString(tmp));
							sort_schedule.pop();
						}
						else
						{
							grotty.push(ScheduleToString(tmp));
							sort_schedule.pop();
						}
					}
				}
			}
			else //Start at different times
			{
				if ((tmp.hour_end == sort_schedule.front().hour_end) &&
					(tmp.minute_end == sort_schedule.front().minute_end)) //Start at different times, but arrival is the same
				{
					if (TripDuration(tmp) > TripDuration(sort_schedule.front()))
					{
						if (sort_schedule.front().company == POSH)
						{
							data.push(ScheduleToString(sort_schedule.front()));
							sort_schedule.pop();
						}
						else
						{
							grotty.push(ScheduleToString(sort_schedule.front()));
							sort_schedule.pop();
						}
					}
					else
					{
						if (tmp.company == POSH)
						{
							data.push(ScheduleToString(tmp));
							sort_schedule.pop();
						}
						else
						{
							grotty.push(ScheduleToString(tmp));
							sort_schedule.pop();
						}
					}
				}
				else //Start and arrival miscellaneous
				{
					if ((tmp.hour_end * 60 + tmp.minute_end) >
						(sort_schedule.front().hour_end * 60 + sort_schedule.front().minute_end))
					{
						if (sort_schedule.front().company == POSH)
						{
							data.push(ScheduleToString(sort_schedule.front()));
							sort_schedule.pop();
						}
						else
						{
							grotty.push(ScheduleToString(sort_schedule.front()));
							sort_schedule.pop();
						}
					}
					else
					{
						if (tmp.company == POSH)
						{
							data.push(ScheduleToString(tmp));
						}
						else
						{
							grotty.push(ScheduleToString(tmp));
						}
					}
				}
			}
		}
		else
		{
			if (tmp.company == POSH)
			{
				data.push(ScheduleToString(tmp));
			}
			else
			{
				grotty.push(ScheduleToString(tmp));
			}
		}
	}
	data.push("");
	while (!grotty.empty())
	{
		data.push(grotty.front());
		grotty.pop();
	}

	return data;
}

queue<Schedule> DataProcessing::SortSchedule()
{
	int schedule_size = schedule.size();
	vector<Schedule> sort_schedule;
	queue<Schedule> sort;
	for (int i = 0; i < schedule_size; i++)
	{
		sort_schedule.push_back(schedule.front());
		schedule.pop();
	}

	Schedule tmp;
	for (int i = 0; i < schedule_size - 1; i++) {
		for (int j = i + 1; j < schedule_size; j++) {
			if ((sort_schedule[i].hour_start > sort_schedule[j].hour_start) ||
				((sort_schedule[i].hour_start == sort_schedule[j].hour_start) &&
					(sort_schedule[i].minute_start > sort_schedule[j].minute_start)))
			{
				tmp = sort_schedule[i];
				sort_schedule[i] = sort_schedule[j];
				sort_schedule[j] = tmp;
			}
		}
	}
	for (Schedule var : sort_schedule)
	{
		sort.push(var);
	}

	return sort;
}

string DataProcessing::ScheduleToString(Schedule line)
{
	string str = line.company + " " + TimeStandard(line.hour_start) + ":" + TimeStandard(line.minute_start)
		+ " " + TimeStandard(line.hour_end) + ":" + TimeStandard(line.minute_end);
	return str;
}

string DataProcessing::TimeStandard(int num)
{
	if (num < 10)
	{
		return "0" + to_string(num);
	}
	else
	{
		return to_string(num);
	}
}