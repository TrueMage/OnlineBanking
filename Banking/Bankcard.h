#pragma once

#include "VirtualMoney.h"
#include <string>

class BankCard : public VirtualMoney
{
protected:
	string CardNumber;
	string CardHolder;

public:
	char* GetLast4Digits() override{
		char* digits = new char[5] {'*', '0', '0', '0', '\0'};

		for (size_t i = CardNumber.length() - 3, j = 1; i < CardNumber.length(); i++, j++)
		{
			digits[j] = CardNumber[i];
		}

		return digits;
	}

	void AddAmount(double amount) {
		this->amount += amount;
	}
};

