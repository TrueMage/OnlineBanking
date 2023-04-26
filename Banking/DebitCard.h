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

	bool ReduceAmount() {
		return true;
	}
};