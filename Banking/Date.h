#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>

using namespace std;

class Date {
private:
	unsigned int year{};
	unsigned int month{};
	unsigned int day{};
public:
	Date(string unform) {
		stringstream ss(unform);
		string temp;

		// Сплит даты 
		getline(ss, temp, '/');
		day = stoi(temp, NULL, 10);
		getline(ss, temp, '/');
		month = stoi(temp, NULL, 10);
		getline(ss, temp, '\0');
		year = stoi(temp, NULL, 10) - 1900;
	}

	void PrintDate() const {
		cout << day << '/' << month << '/'<< year + 1900;
	}
	
	bool isToday() const{
		time_t now = time(0);
		tm dt;
		localtime_s(&dt, &now);

		if (dt.tm_mday == day && dt.tm_mon == month && dt.tm_year == year) return true;
		else false;
	}

	bool isCurrentWeek() const {
		time_t now = time(0);
		tm dt;
		localtime_s(&dt, &now);
	}

	bool isCurrentMonth() const {
		time_t now = time(0);
		tm dt;
		localtime_s(&dt, &now);

		if (dt.tm_mon == month && dt.tm_year == year) return true;
		else false;
	}

	bool SameMonthYear(Date* d) const {
		if (d->month == month && d->year == year) return true;
		else false;
	}

	int GetDay() const{
		return day;
	}

	int GetMonth() const {
		return month;
	}

	int GetYear() const {
		return year;
	}

	// Перегрузки
	bool operator == (const Date& d) {
		if (d.day == day && d.month == month && d.year == d.year) return true;
		else return false;
	}
};