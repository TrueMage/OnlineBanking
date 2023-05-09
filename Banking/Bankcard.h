#pragma once

#include "VirtualMoney.h"
#include <string>

class BankCard : public VirtualMoney
{
protected:
	string PAN{};
	string CardHolder{};
	string ServiceCode{};
public:
	char* GetLast4Digits() const{
		char* digits = new char[5] {'*', '0', '0', '0', '\0'};

		for (size_t i = PAN.length() - 3, j = 1; i < PAN.length(); i++, j++)
		{
			digits[j] = PAN[i];
		}

		return digits;
	}

	void AddAmount(double amount) {
		this->amount += amount;
	}


};

