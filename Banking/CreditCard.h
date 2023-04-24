#pragma once

#include "Bankcard.h"
#include <string>

class CreditCard : public BankCard
{
private:
	unsigned int CreditLimit;
public:
	CreditCard(double amount, string CardNumber, string CardHolder, unsigned int CreditLimit){
		this->amount = amount;
		this->CardNumber = CardNumber;
		this->CardHolder = CardHolder;
		this->CreditLimit = CreditLimit;
	}
	bool ReduceAmount() {
		return true;
	}
};

