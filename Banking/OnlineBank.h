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
		cout << "\n\tМЕНЮ";

		cout << "\n(0) Список добавленных кошельков и карт";
		cout << "\n(1) Добавить новый кошелек или карту";
		cout << "\n(2) Пополнение кошелька или карты";

		cout << "\n(3) Внесение затратов";
		cout << "\n(4) Сформировать отчет по затратам";
		cout << "\n(5) Сформировать рейтинг по затратам";

		cout << "\n(6) Выход\n";
		//cout << "\n (5) Сохранить отчет и рейтинг в файл";
	}

	void PrintAllAccounts(bool showbudget = false) const{
		system("cls");

		if(showbudget) cout << "ОБЩИЙ БЮДЖЕТ $" << GetFullBudget() << "\n";

		for (int i = 0; i < accounts.size(); i++)
		{
			cout << "#" << i << " " << " " << accounts[i]->GetLast4Digits() << " $" << accounts[i]->GetAmount() << "\n";
		}
	}

	void AddNewAccount() {
		while (true) {
			system("cls");

			cout << "(0) Выход\n";
			cout << "(1) Электронный кошелек\n";
			cout << "(2) Банковская карточка\n";

			int selected;
			cin >> selected;

			switch (selected) {
				case 0: return;

				case 1:
					while (true) {
						system("cls");

						cout << "(0) Выход\n";
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
								cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
								continue;
						}
						cout << "Введите к-ство денег на кошельке: ";
						cin >> amount;
						cin.ignore(1);

						cout << "Введите ключ разрешение: ";
						getline(cin, AuthToken);

						cout << "Введите номер кошелька: ";
						getline(cin, WalletID);

						accounts.push_back(new EWallet(amount, AuthToken, WalletID, PaySystem));
						return;
					}
					break;

				case 2:
					while (true) {
						system("cls");

						cout << "(0) Выход\n";
						cout << "(1) Кредитная карточка\n";
						cout << "(2) Дебетовая карточка\n";

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
								cout << "Введите кредитный лимит: ";
								cin >> limit;

							case 2:
								system("cls");
								cout << "Введите к-ство денег на карточке: ";
								cin >> amount;

								cout << "Введите CVV: ";
								cin >> CVV;

								cin.ignore(1);
								cout << "Введите номер карточки: ";
								getline(cin,num);

								// https://www.geeksforgeeks.org/luhn-algorithm/
								cout << "Введите имя владельца: ";
								getline(cin, name);

								if (limit > 0) accounts.push_back(new CreditCard(amount, num, name, limit, CVV));
								else accounts.push_back(new DebitCard(amount, num, name, CVV));

								// limit ? new CreditCard(amount, num, name, limit, CVV) : new DebitCard(amount, num, name, CVV)
								// Тернарный оператор нельзя перегружать, но компилятор всё-равно требует? 

								system("cls");
								cout << "Карточка была успешна добавлена\n";
								return;

							default:
								cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
						}
					}
					break;
				default:
					cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
			}
		}
	}

	void TopUpAccount() {
		system("cls");

		PrintAllAccounts();

		int selected;
		while (true) {
			cout << "\nВведите номер в списке аккаунта: ";
			cin >> selected;

			if (selected < 0 || selected > accounts.size() - 1) cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
			else break;
		}
		
		int amount;

		while (true) {
			cout << "\nВведите сколько денег положить: ";
			cin >> amount;

			if (amount < 0) cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
			else break;
		}

		accounts[selected]->AddAmount(amount);

		system("cls");
		cout << "Баланс был успешно пополнен\n";
		return;
	}

	void CreateExpense() {
		system("cls");

		VirtualMoney* paidWith = nullptr;
		CategoryCodes category;
		string date;
		unsigned int amount;
		cout << "Введите сумму расхода: ";
		cin >> amount;

		while (true) {
			system("cls");
			cout << "Каким образом оплатить расход?\n";

			cout << "(0) Выход\n";
			cout << "(1) Разделить между всеми счетами\n";
			cout << "(2) Оплатить конкретным счётом\n";

			int selected;
			cin >> selected;

			system("cls");
			switch (selected) {
				case 0: return;

				case 1:
					bool avoidableDebts = true;

					int count = 0;
					for (VirtualMoney* current : accounts) {
						if (dynamic_cast<CreditCard*>(current)) continue;
						count++;
					}

					double amountPerAcc = amount / count;
					for (VirtualMoney* current : accounts) {
						if (dynamic_cast<CreditCard*>(current)) continue;
						if (!current->isAmountOnBalance(amountPerAcc)) avoidableDebts = false;
					}

					if (avoidableDebts) {
						for (VirtualMoney* current : accounts) {
							if (dynamic_cast<CreditCard*>(current)) continue;
							current->ReduceAmount(amountPerAcc);
						}
					}
					else {

					}
					break;

				case 2:
					while (true) {
						PrintAllAccounts();
						while (true) {
							cout << "\nВведите номер в списке аккаунта: ";
							cin >> selected;

							if (selected < 0 || selected > accounts.size() - 1) cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
							else break;
						}

						if (accounts[selected]->ReduceAmount(amount)) {
							paidWith = accounts[selected];
							break;
						}
						else {
							system("cls");
							cout << "ОШИБКА: На выбранном счёту недостаточно денег";
						}
					}
					break;

				default:
					system("cls");
					cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
					continue;
			}
			break;
		}

		while (true) {
			system("cls");
			cout << "Выберите категорию расходов: \n";

			cout << "(1) Продукты\n";
			cout << "(2) Развлечения\n";
			cout << "(3) Коммунальные услуги\n";
			cout << "(4) Уход за машиной\n";

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
				cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
				continue;
			}
			break;
		}
		cin.ignore(1);

		system("cls");
		cout << "Введите дату в формате(31/05/2023): ";
		getline(cin, date);

		system("cls");

		expenses.push_back(new Expense(amount, date, category, paidWith));
		cout << "Расход был успешно добавлен\n";
	}

	void CreateReport() {
		time_t now = time(0);
		tm dt;
		localtime_s(&dt, &now);

		while (true) {
			system("cls");

			cout << "(0) Выход\n";
			cout << "(1) За день\n";
			cout << "(2) За неделю\n";
			cout << "(3) За месяць\n";

			int selected;
			cin >> selected;

			switch (selected) {
				case 0:return;

				case 1:
					system("cls");
					cout << "РАСХОДЫ ЗА ДЕНЬ\n";
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
					cout << "РАСХОДЫ ЗА НЕДЕЛЮ\n";

					break;

				case 3:
					system("cls");
					cout << "РАСХОДЫ ЗА МЕСЯЦЬ\n";
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
					cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
					continue;
			}
			break;
		}	
	}

	void CreateRating() {
		while (true) {
			system("cls");

			cout << "(0) Выход\n";
			cout << "(1) ТОП-3 затрат\n";
			cout << "(2) ТОП-3 категорий\n";

			int selected;
			cin >> selected;

			switch (selected)
			{
				case 0: return;

				case 1:
					while (true) {
						cout << "(0) Выход\n";
						cout << "(1) За неделю\n";
						cout << "(2) За месяць\n";

						cin >> selected;

						switch (selected) {
						case 0: return;
						case 1:
							break;
						case 2:
							break;
						default:
							cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
							continue;
						}
					}
					break;

				case 2:
					while (true) {
						cout << "(0) Выход\n";
						cout << "(1) За неделю\n";
						cout << "(2) За месяць\n";

						cin >> selected;

						switch (selected) {
						case 0: return;
						case 1:
							break;
						case 2:
							break;
						default:
							cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
							continue;
						}
					}
					break;

				default:
					cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
					continue;
			}
		break;
		}
	}
};