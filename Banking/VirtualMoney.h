#pragma once

constexpr auto CHECK = 1;

using namespace std;

class VirtualMoney {
protected:
	double amount{};
public:

	// Инспекторы
	virtual double GetAmount() const {
		return amount;
	}

	virtual bool isAmountOnBalance(unsigned int request) {
		if (amount < request) return false;
		else return true;
	}

	virtual char* GetLast4Digits() const = 0;

	// Модификаторы
	virtual bool ReduceAmount(double amount) = 0;
	virtual void AddAmount(double amount) = 0;
};