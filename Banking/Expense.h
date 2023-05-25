#pragma once

#include <iostream>
#include <Windows.h>
#include <string>

#include "VirtualMoney.h"
#include "Date.h"

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
	CategoryCodes category{};
	VirtualMoney* paidWith;
	Date* date;
public:
	Expense(unsigned int amount, string date, CategoryCodes category, VirtualMoney* paidWith){
		this->amount = amount;
		this->date = new Date(date);
		this->category = category;
		this->paidWith = paidWith;
	}

	Date* getDate() const{
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
		date->PrintDate();
		if (paidWith) cout << " $" << amount << " " << cat << " �������� " << paidWith->GetLast4Digits() << '\n';
		else cout << " $" << amount << " " << cat << " �������� ALL" << '\n';
	}
};
