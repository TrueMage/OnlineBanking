#pragma once

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>

#include "VirtualMoney.h"
#include "Expense.h"

#include "CreditCard.h"
#include "DebitCard.h"
#include "EWallet.h"

#include <ctime>

using namespace std;

class OnlineBank {
private:
	vector<VirtualMoney*> accounts;
	vector<Expense*> expenses;
public:
	long double GetFullBudget() const{
		long double budget = 0;
		for (int i = 0; i < accounts.size(); i++)
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
		cout << "\n(5) ������������ ������� �� ��������";

		cout << "\n(6) �����\n";
		//cout << "\n (5) ��������� ����� � ������� � ����";
	}

	void PrintAllAccounts(bool showbudget = false) const{
		system("cls");

		if(showbudget) cout << "����� ������ $" << GetFullBudget() << "\n";

		for (int i = 0; i < accounts.size(); i++)
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
					while (true) {
						system("cls");

						cout << "(0) �����\n";
						cout << "(1) PayPal\n";
						cout << "(2) Payoneer\n";
						cout << "(3) Alipay\n";

						cin >> selected;

						unsigned int amount;
						string AuthToken;
						string WalletID{};
						PaySystems PaySystem{};

						switch (selected) {
							case 0: return;

							case 1:
								PaySystem = PayPal;
								break;

							case 2:
								PaySystem = Payoneer;
								break;

							case 3:
								PaySystem = Alipay;
								break;

							default:
								cout << "������: ������������ ����\n";
								continue;
						}
						cout << "������� �-���� ����� �� ��������: ";
						cin >> amount;
						cin.ignore(1);

						cout << "������� ���� ����������: ";
						getline(cin, AuthToken);

						cout << "������� ����� ��������: ";
						getline(cin, WalletID);

						accounts.push_back(new EWallet(amount, AuthToken, WalletID, PaySystem));
						return;
					}
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
							case 0:return;

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

								// https://www.geeksforgeeks.org/luhn-algorithm/
								cout << "������� ��� ���������: ";
								getline(cin, name);

								if (limit > 0) accounts.push_back(new CreditCard(amount, num, name, limit, CVV));
								else accounts.push_back(new DebitCard(amount, num, name, CVV));

								// limit ? new CreditCard(amount, num, name, limit, CVV) : new DebitCard(amount, num, name, CVV)
								// ��������� �������� ������ �����������, �� ���������� ��-����� �������? 

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
		system("cls");

		PrintAllAccounts();

		int selected;
		while (true) {
			cout << "\n������� ����� � ������ ��������: ";
			cin >> selected;

			if (selected < 0 || selected > accounts.size() - 1) cout << "������: ������������ ����\n";
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

	void CreateExpense() {
		system("cls");

		VirtualMoney* paidWith = nullptr;
		CategoryCodes category;
		string date;
		unsigned int amount;
		cout << "������� ����� �������: ";
		cin >> amount;

		while (true) {
			system("cls");
			cout << "����� ������� �������� ������?\n";

			cout << "(0) �����\n";
			cout << "(1) ��������� ����� ����� �������\n";
			cout << "(2) �������� ���������� ������\n";

			int selected;
			cin >> selected;

			system("cls");
			switch (selected) {
				case 0: return;

				case 1:
					//double amountPerAcc = amount / accounts.size();
					//bool avoidableDebts = true;

					for (int i = 0; i < accounts.size(); i++) {
						//cout << typeid(accounts[i]).name() << '\n';
					}

					//if(avoidableDebts)

					break;

				case 2:
					while (true) {
						PrintAllAccounts();
						while (true) {
							cout << "\n������� ����� � ������ ��������: ";
							cin >> selected;

							if (selected < 0 || selected > accounts.size() - 1) cout << "������: ������������ ����\n";
							else break;
						}

						if (accounts[selected]->ReduceAmount(amount)) {
							paidWith = accounts[selected];
							break;
						}
						else {
							system("cls");
							cout << "������: �� ��������� ����� ������������ �����";
						}
					}
					break;

				default:
					system("cls");
					cout << "������: ������������ ����\n";
					continue;
			}
			break;
		}

		while (true) {
			system("cls");
			cout << "�������� ��������� ��������: \n";

			cout << "(1) ��������\n";
			cout << "(2) �����������\n";
			cout << "(3) ������������ ������\n";
			cout << "(4) ���� �� �������\n";

			int selected;
			cin >> selected;

			switch (selected)
			{
				case 1:
					category = Grocery;
					break;

				case 2:
					category = Entertainment;
					break;

				case 3:
					category = Rent;
					break;

				case 4:
					category = CarMaintenance;
					break;
			default:
				cout << "������: ������������ ����\n";
				continue;
			}
			break;
		}
		cin.ignore(1);

		system("cls");
		cout << "������� ���� � �������(31/05/2023): ";
		getline(cin, date);

		system("cls");

		expenses.push_back(new Expense(amount, date, category, paidWith));
		cout << "������ ��� ������� ��������\n";
	}

	void CreateReport() {
		time_t now = time(0);
		tm dt;
		localtime_s(&dt, &now);

		while (true) {
			system("cls");

			cout << "(0) �����\n";
			cout << "(1) �� ����\n";
			cout << "(2) �� ������\n";
			cout << "(3) �� ������\n";

			int selected;
			cin >> selected;

			switch (selected) {
				case 0:return;

				case 1:
					system("cls");
					cout << "������� �� ����\n";
					for (Expense* current : expenses)
					{
						string date = current->getDate();

						int day = strtol(new char[2] {date[0], date[1]}, NULL, 10);
						int month = strtol(new char[2] {date[3], date[4]}, NULL, 10) - 1;
						int year = strtol(new char[4] {date[6], date[7], date[8], date[9]}, NULL, 10) - 1900;

						if (dt.tm_mday == day && dt.tm_mon == month && dt.tm_year == year) current->PrintInfo();
					}
					cout << "\n";
					break;

				case 2:
					system("cls");
					cout << "������� �� ������\n";

					break;

				case 3:
					system("cls");
					cout << "������� �� ������\n";
					for (Expense* current : expenses)
					{
						string date = current->getDate();

						int month = strtol(new char[2] {date[3], date[4]}, NULL, 10) - 1;
						int year = strtol(new char[4] {date[6], date[7], date[8], date[9]}, NULL, 10) - 1900;

						if (dt.tm_mon == month && dt.tm_year == year) current->PrintInfo();
					}
					cout << "\n";
					break;

				default:
					cout << "������: ������������ ����\n";
			}
			break;
		}	
	}
};