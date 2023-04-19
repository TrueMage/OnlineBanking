#pragma once

#include "VirtualMoney.h"
#include <string>

class BankCard : public VirtualMoney
{
protected:
	string CardNumber;
	string CardHolder;
};

