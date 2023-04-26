#pragma once

#include <iostream>
#include <Windows.h>
#include <string>

#include "VirtualMoney.h"
#include "CreditCard.h"
#include "DebitCard.h"

using namespace std;

class OnlineBank {
private:
	VirtualMoney** accounts;
	int countAccounts{};

	void AddAccountToArray(VirtualMoney* account) {
		VirtualMoney** newaccounts = new VirtualMoney*[countAccounts+1];
		for (int i = 0; i < countAccounts; i++)
		{
			newaccounts[i] = accounts[i];
		}
		newaccounts[countAccounts] = account;
		
		accounts = newaccounts;
		newaccounts = nullptr;
		countAccounts += 1;
	}
public:
	long int GetFullBudget() const{
		long double budget = 0;
		for (int i = 0; i < countAccounts; i++)
		{
			budget += accounts[i]->GetAmount();
		}
		return budget;
	}
	
	void PrintMainMenu() const{
		cout << "\n\t����";

		cout << "\n(0) ������ ����������� ��������� � ����";
		cout << "\n(1) �������� ����� ������� ��� �����";
		cout << "\n(2) ���������� �������� ��� �����";

		cout << "\n(3) �������� ��������";
		cout << "\n(4) ������������ ����� �� ��������";

		cout << "\n(5) �����\n";
		//cout << "\n (5) ��������� ����� � ������� � ����";
	}

	void PrintAllAccounts(bool showbudget = false) const{
		system("cls");

		if(showbudget) cout << "����� ������ $" << GetFullBudget() << "\n";

		for (int i = 0; i < countAccounts; i++)
		{
			cout << "#" << i << " " << " " << accounts[i]->GetLast4Digits() << " $" << accounts[i]->GetAmount() << "\n";
		}
	}

	void AddNewAccount() {
		while (true) {
			system("cls");

			cout << "(0) �����\n";
			cout << "(1) ����������� �������\n";
			cout << "(2) ���������� ��������\n";

			int selected;
			cin >> selected;

			switch (selected) {
				case 0: return;

				case 1:

					break;

				case 2:
					while (true) {
						system("cls");

						cout << "(0) �����\n";
						cout << "(1) ��������� ��������\n";
						cout << "(2) ��������� ��������\n";

						cin >> selected;

						int limit = -1;
						int amount;
						string num;
						string name;
						unsigned int CVV;

						switch (selected) {
							case 0:
								return;

							case 1:
								system("cls");
								cout << "������� ��������� �����: ";
								cin >> limit;

							case 2:
								system("cls");
								cout << "������� �-���� ����� �� ��������: ";
								cin >> amount;

								cout << "������� CVV: ";
								cin >> CVV;

								cin.ignore(1);
								cout << "������� ����� ��������: ";
								getline(cin,num);

								cout << "������� ��� ���������: ";
								getline(cin, name);

								if (limit > 0) AddAccountToArray(new CreditCard(amount, num, name, limit, CVV));
								else AddAccountToArray(new DebitCard(amount, num, name, CVV));
								// limit ? new CreditCard(amount, num, name, limit, CVV) : new DebitCard(amount, num, name, CVV) ��������� �������� ������ �����������, �� ���������� ��-����� �������? 

								system("cls");
								cout << "�������� ���� ������� ���������\n";
								return;

							default:
								cout << "������: ������������ ����\n";
						}
					}
					break;
				default:
					cout << "������: ������������ ����\n";
			}
		}
	}

	void TopUpAccount() {
		PrintAllAccounts();

		int selected;

		while (true) {
			cout << "\n������� ����� � ������ ��������: ";
			cin >> selected;

			if (selected < 0 || selected >> countAccounts - 1) cout << "������: ������������ ����\n";
			else break;
		}
		
		int amount;

		while (true) {
			cout << "\n������� ������� ����� ��������: ";
			cin >> amount;

			if (amount < 0) cout << "������: ������������ ����\n";
			else break;
		}

		accounts[selected]->AddAmount(amount);

		system("cls");
		cout << "������ ��� ������� ��������\n";
		return;
	}
};