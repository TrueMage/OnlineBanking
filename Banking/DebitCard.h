#pragma once

#include "Bankcard.h"
#include <string>

class DebitCard : public BankCard
{
public:
	DebitCard(double amount, string CardNumber, string CardHolder) {
		this->amount = amount;
		this->CardNumber = CardNumber;
		this->CardHolder = CardHolder;
	}

	bool ReduceAmount() {
		return true;
	}
};