#include <iostream>
#include <Windows.h>
#include <string>

#include "OnlineBank.h"

using namespace std;

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	OnlineBank sys;

	while (true) {
		sys.PrintMainMenu();

		int selected;
		cin >> selected;

		if (selected == 6) break;

		switch (selected){
			case 0:				
				sys.PrintAllAccounts(true);
				break;

			case 1:
				sys.AddNewAccount();
				break;

			case 2:
				sys.TopUpAccount();
				break;

			case 3:
				sys.CreateExpense();
				break;

			case 4:
				sys.CreateReport();
				break;

			case 5:
				break;
			default:
				cout << "ÎØÈÁÊÀ: ÍÅÊÎÐÐÅÊÒÍÛÉ ÂÂÎÄ";
		}
	}
}
