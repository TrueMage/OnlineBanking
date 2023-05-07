#pragma once

using namespace std;

class VirtualMoney {
protected:
	double amount{};
public:

	// Инспекторы
	int GetAmount() const {
		return amount;
	}

	virtual char* GetLast4Digits() const = 0;

	// Модификаторы
	virtual bool ReduceAmount(double amount) = 0;
	virtual void AddAmount(double amount) = 0;
};