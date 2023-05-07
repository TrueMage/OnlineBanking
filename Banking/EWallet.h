#pragma once

#include "VirtualMoney.h"
#include <string>

using namespace std;

enum PaySystems {
	PayPal = 0,
	Payoneer = 1,
	Alipay = 2
};

class EWallet : public VirtualMoney
{
private:
	string AuthToken{};
	string WalletID{};
	PaySystems PaySystem{};
public:

	EWallet(double amount, string WalletID, string AuthToken, PaySystems PaySystem) {
		this->amount = amount;
		this->WalletID = WalletID;
		this->AuthToken = AuthToken;
		this->PaySystem = PaySystem;
	}

	char* GetLast4Digits() const {
		char* digits = new char[5] {'*', '0', '0', '0', '\0'};

		for (size_t i = WalletID.length() - 3, j = 1; i < WalletID.length(); i++, j++)
		{
			digits[j] = WalletID[i];
		}

		return digits;
	}

	void AddAmount(double amount) {
		this->amount += amount;
	}

	bool ReduceAmount(double amount) {
		if (this->amount - amount >= 0) {
			this->amount -= amount;
			return true;
		}
		else return false;
	}
};

