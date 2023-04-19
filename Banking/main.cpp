#include <iostream>
#include <Windows.h>
#include <string>

#include "Functions.h"
#include "OnlineBank.h"

using namespace std;

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	OnlineBank sys();

	while (true) {
		PrintMainMenu();

		int selected;
		cin >> selected;

		if (selected == 5) break;

		switch (selected){
			case 0:

				system("cls");
				break;

			case 1:

				system("cls");
				break;

			case 2:

				system("cls");
				break;

			case 3:

				system("cls");
				break;

			case 4:

				system("cls");
				break;

			default:
				cout << "ÎØÈÁÊÀ: ÍÅÊÎÐÐÅÊÒÍÛÉ ÂÂÎÄ";
		}
	}
}
