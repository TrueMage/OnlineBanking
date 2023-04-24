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
		cout << "\n\tМЕНЮ";

		cout << "\n(0) Список добавленных кошельков и карт";
		cout << "\n(1) Добавить новый кошелек или карту";
		cout << "\n(2) Пополнение кошелька или карты";

		cout << "\n(3) Внесение затратов";
		cout << "\n(4) Сформировать отчет по затратам";

		cout << "\n(5) Выход\n";
		//cout << "\n (5) Сохранить отчет и рейтинг в файл";
	}

	void PrintAllAccounts(bool showbudget = false) const{
		system("cls");

		if(showbudget) cout << "ОБЩИЙ БЮДЖЕТ $" << GetFullBudget() << "\n";

		for (int i = 0; i < countAccounts; i++)
		{
			cout << "#" << i << " " << typeid(this).name() << " " << accounts[i]->GetLast4Digits() << " $" << accounts[i]->GetAmount() << "\n";
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

						switch (selected) {
							case 0:
								return;

							case 1:
								system("cls");
								cout << "Введите кредитный лимит: ";
								cin >> limit;

							case 2:
								system("cls");
								cout << "Введите к-ство денег на карточке: ";
								cin >> amount;

								cin.ignore(1);
								cout << "Введите номер карточки: ";
								getline(cin,num);

								cout << "Введите имя владельца: ";
								getline(cin,name);

								if (limit > 0) AddAccountToArray(new CreditCard(amount, num, name, limit));
								else AddAccountToArray(new DebitCard(amount, num, name));
								// limit ? new CreditCard(amount, num, name, limit) : new DebitCard(amount, num, name) Тернарный оператор нельзя перегружать, но компилятор всё-равно требует? 

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
		PrintAllAccounts();

		int selected;

		while (true) {
			cout << "\nВведите номер в списке аккаунта: ";
			cin >> selected;

			if (selected < 0 || selected >> countAccounts - 1) cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
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
};