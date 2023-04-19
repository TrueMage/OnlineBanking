#pragma once

using namespace std;

class VirtualMoney {
protected:
	int amount;
public:
	virtual void GetAmount() const = 0;
	virtual void ReduceAmount() const = 0;
};