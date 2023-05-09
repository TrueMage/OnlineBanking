#pragma once

#include "Bankcard.h"
#include <string>
#include <time.h>

class CreditCard : public BankCard
{
private:
	unsigned int CreditLimit{};
public:
	CreditCard(double amount, string CardNumber, string CardHolder, unsigned int CreditLimit, unsigned int CVV){
		srand((unsigned int)time(NULL));
		this->amount = amount;
		this->PAN = CardNumber;
		this->CardHolder = CardHolder;
		this->CreditLimit = CreditLimit;
		this->ServiceCode = rand() % CVV;
	}

	bool ReduceAmount(double amount) {
		if (abs(this->amount - amount) <= CreditLimit) {
			this->amount -= amount;
			return true;
		}
		else return false;
	}
};

