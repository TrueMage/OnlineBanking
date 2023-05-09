#pragma once

#include <iostream>
#include <Windows.h>
#include <string>

#include "VirtualMoney.h"

using namespace std;

enum CategoryCodes{
	Grocery = 11,
	Entertainment = 22,
	Rent = 33,
	CarMaintenance = 44
};

class Expense
{
private:
	unsigned int amount{};
	string date{};
	CategoryCodes category{};
	VirtualMoney* paidWith;
public:
	Expense(unsigned int amount, string date, CategoryCodes category, VirtualMoney* paidWith) {
		this->amount = amount;
		this->date = date;
		this->category = category;
		this->paidWith = paidWith;
	}

	string getDate() const{
		return date;
	}

	unsigned int getAmount() const {
		return amount;
	}

	CategoryCodes getCategory() const {
		return category;
	}

	VirtualMoney* GetPaidWith() const {
		return paidWith;
	}

	void PrintInfo() const {
		string cat;

		switch (category) {
		case Grocery:
			cat = "��������";
			break;

		case Entertainment:
			cat = "�����������";
			break;

		case Rent:
			cat = "������������ ������";
			break;

		case CarMaintenance:
			cat = "���� �� �������";
			break;
		}
		cout << date << " $" << amount << " " << cat << " �������� " << paidWith->GetLast4Digits();
	}
};
