#pragma once

#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

enum CategoryCodes{
	Grocery = 11,
	Book = 22,
	Cafe = 33,
	Cars = 44
};

class Expense
{
private:
	unsigned int amount{};
	string date{};
	unsigned int category{};
public:
	Expense(unsigned int amount, string date, int category) {
		this->amount = amount;
		this->date = date;
		this->category = category;
	}
};

