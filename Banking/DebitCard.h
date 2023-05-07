#pragma once

#include "Bankcard.h"
#include <string>
#include <time.h>

class DebitCard : public BankCard
{
public:
	DebitCard(double amount, string CardNumber, string CardHolder, int CVV) {
		srand(time(NULL));
		this->amount = amount;
		this->PAN = CardNumber;
		this->CardHolder = CardHolder;
		this->ServiceCode = rand() % CVV;
	}

	bool ReduceAmount(double amount) {
		if (this->amount - amount >= 0) {
			this->amount -= amount;
			return true;
		}
		else return false;
	}
};