#pragma once

using namespace std;

class VirtualMoney {
protected:
	double amount{};
public:
	int GetAmount() const {
		return amount;
	};
	virtual bool ReduceAmount() = 0;
	virtual void AddAmount(double amount) = 0;
	virtual char* GetLast4Digits() = 0;
};