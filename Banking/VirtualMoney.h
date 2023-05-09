#pragma once

using namespace std;

class VirtualMoney {
protected:
	double amount{};
public:

	// ����������
	double GetAmount() const {
		return amount;
	}

	virtual char* GetLast4Digits() const = 0;

	// ������������
	virtual bool ReduceAmount(double amount) = 0;
	virtual void AddAmount(double amount) = 0;
};