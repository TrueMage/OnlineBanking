#pragma once

#include "Bankcard.h"
#include <string>

class CreditCard : public BankCard
{
private:
	unsigned int CreditLimit;
public:
	CreditCard() {

	}
};

