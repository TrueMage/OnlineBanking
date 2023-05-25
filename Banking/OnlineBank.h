#pragma once

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <map>

#include "VirtualMoney.h"
#include "Expense.h"

#include "CreditCard.h"
#include "DebitCard.h"
#include "EWallet.h"

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

		if (accounts.size() == 0) {
			cout << "ОШИБКА: В системе нет добавленных счетов";
			return;
		}

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

		if(accounts.size() == 0) {
			cout << "ОШИБКА: В системе нет добавленных счетов";
			return;
		}

		VirtualMoney* paidWith = nullptr;
		CategoryCodes category;
		string date;
		unsigned int amount;
		cout << "Введите сумму расхода: ";
		cin >> amount;

		if (amount > GetFullBudget()) {
			cout << "ОШИБКА: В БЮДЖЕТЕ НЕДОСТАТОЧНО ДЕНЕГ\n";
			return;
		}
		while (true) {
			system("cls");
			cout << "Каким образом оплатить расход?\n";

			cout << "(0) Выход\n";
			cout << "(1) Разделить между всеми счетами\n";
			cout << "(2) Оплатить конкретным счётом\n";

			int selected;
			cin >> selected;

			system("cls");

			bool avoidableDebts = true;
			int count = 0;
			double amountPerAcc = 0;

			switch (selected) {
				case 0: return;

				case 1:

					for (VirtualMoney* current : accounts) {
						CreditCard* check = dynamic_cast<CreditCard*>(current);
						if (check) {
							if (check->isInDebt()) continue;
							else count++;
						}
						count++;
					}

					amountPerAcc = amount / count;
					for (VirtualMoney* current : accounts) {
						CreditCard* check = dynamic_cast<CreditCard*>(current);
						if (check) {
							if (check->isInDebt()) continue;
							else {
								if (!current->isAmountOnBalance(amountPerAcc)) avoidableDebts = false;
							}
						}
						if (!current->isAmountOnBalance(amountPerAcc)) avoidableDebts = false;
					}

					if (avoidableDebts) {
						for (VirtualMoney* current : accounts) {
							if (dynamic_cast<CreditCard*>(current)) continue;
							current->ReduceAmount(amountPerAcc);
						}
						cout << "Удалось разделить затрату между счетами без использование кредита\nПродоложаем\n";
					}
					else {
						cout << "Не удалось разделить затрату между счетами без использование кредита.\nПопробовать с использованием кредитов?(0 - Да / 1 - Нет)\n";
						cin >> selected;

						if (selected == 0) {
							avoidableDebts = true;

							amountPerAcc = amount / accounts.size();
							for (VirtualMoney* current : accounts) {
								CreditCard* check = dynamic_cast<CreditCard*>(current);
								if (check) {
									if (check->isAmountOnBalanceWCredit(amountPerAcc))
									{
										avoidableDebts = false;
									}
								}
								
							}

							if (avoidableDebts) {
								for (VirtualMoney* current : accounts) {
									if (dynamic_cast<CreditCard*>(current)) continue;
									current->ReduceAmount(amountPerAcc);
								}
								cout << "Удалось разделить затрату между счетами с использованием кредита\nПродоложаем\n";
							}
							else {
								cout << "Не удалось разделить затрату между счетами.\n";
								continue;
							}
						}
						else continue;
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
		while (true) {
			system("cls");

			cout << "(0) Выход\n";
			cout << "(1) За день\n";
			cout << "(2) За неделю\n";
			cout << "(3) За месяц\n";

			int selected;
			cin >> selected;

			system("cls");
			string date;
			switch (selected) {
				case 0:return;

				case 1:
					while (true) {
						cout << "(0) Выход\n";
						cout << "(1) За текущий день\n";
						cout << "(2) Выбрать конкретный день\n";

						cin >> selected;

						system("cls");
						Date* searched;
						switch (selected) {
							case 0: return;

							case 1:
								cout << "РАСХОДЫ ЗА ТЕКУЩИЙ ДЕНЬ\n";

								for (Expense* current : expenses)
									if (current->getDate()->isToday()) current->PrintInfo();

								cout << "\n";
								break;
							case 2:
								cout << "Введите дату в формате(31/05/2023)";
								cin >> date;

								system("cls");
								cout << "РАСХОДЫ ЗА " << date << " \n";

								searched = new Date(date);
								for (Expense* current : expenses)
									if (*current->getDate() == *searched) current->PrintInfo();

								cout << "\n";
								break;

							default:
								cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
								continue;
						}
						break;
					}
					break;

				case 2:
					Date * searched;
					while (true) {
						cout << "(0) Выход\n";
						cout << "(1) За текущую неделю\n";
						cout << "(2) Выбрать конкретную неделю\n";

						cin >> selected;

						system("cls");
						switch (selected) {
						case 0: return;

						case 1:
							cout << "РАСХОДЫ ЗА ТЕКУЩУЮ НЕДЕЛЮ\n";

							for (Expense* current : expenses)
								if (current->getDate()->isCurrentWeek()) current->PrintInfo();

							cout << "\n";
							break;
						case 2:
							cout << "Введите дату в формате(31/05/2023)";
							cin >> date;

							system("cls");
							cout << "РАСХОДЫ ЗА НЕДЕЛЮ (" << date << ")\n";

							searched = new Date(date);
							for (Expense* current : expenses)
								if (current->getDate()->SameWeekMonthYear(searched)) current->PrintInfo();

							break;

						default:
							cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
							continue;
						}
						break;
					}
					break;

				case 3:
					while (true) {
						cout << "(0) Выход\n";
						cout << "(1) За текущий месяц\n";
						cout << "(2) Выбрать конкретный месяц\n";

						cin >> selected;

						Date* searched;
						system("cls");
						switch (selected) {
						case 0: return;

						case 1:
							cout << "РАСХОДЫ ЗА ТЕКУЩИЙ МЕСЯЦ\n";

							for (Expense* current : expenses)
								if (current->getDate()->isCurrentMonth()) current->PrintInfo();

							cout << "\n";
							break;

						case 2:
							cout << "Введите номер в месяца(1-12/2023)";
							cin >> date;

							cout << "РАСХОДЫ ЗА " << date << " \n";
							searched = new Date("01/" + date);
							for (Expense* current : expenses)
								if (current->getDate()->SameMonthYear(searched)) current->PrintInfo();
							
							cout << "\n";
							break;

						default:
							cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
							continue;
						}
						break;
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

		if (expenses.size() < 3) {
			cout << "ОШИБКА: НЕОБХОДИМО КАК МИНИМУМ 3 РАСХОДА, ЧТОБ СГЕНЕРИРОВАТЬ РЕЙТИНГ\n";
			return;
		}

		while (true) {
			system("cls");

			cout << "(0) Выход\n";
			cout << "(1) ТОП-3 затрат\n";
			cout << "(2) ТОП-3 категорий\n";

			int selected;
			cin >> selected;

			system("cls");
			switch (selected)
			{
				case 0: return;

				case 1:

					while (true) {
						cout << "(0) Выход\n";
						cout << "(1) За неделю\n";
						cout << "(2) За месяц\n";

						cin >> selected;

						vector<Expense*> top;

						switch (selected) {
							case 0: return;
							case 1:
								top.push_back(expenses[0]);
								top.push_back(expenses[1]);
								top.push_back(expenses[2]);

								for (int i = 2; i < expenses.size(); i++)
								{
									if (!expenses[i]->getDate()->isCurrentWeek()) continue;

									if(top[0]->getAmount() < expenses[i]->getAmount()) {
										Expense* temp1 = top[0];
										Expense* temp2;
										top[0] = expenses[i];
										temp2 = top[1];
										top[1] = temp1;
										top[2] = temp2;
										continue;
									}
									else if (top[1]->getAmount() < expenses[i]->getAmount()) {
										Expense* temp1 = top[1];
										top[1] = expenses[i];
										top[2] = temp1;
										continue;
									}
									else if (top[2]->getAmount() < expenses[i]->getAmount()) {
										top[2] = expenses[i];
									}
								}

								cout << "\nТОП-3 ЗАТРАТ ЗА НЕДЕЛЮ\n";

								for (Expense* current : top)
									current->PrintInfo();

								break;
							case 2:
								top.push_back(expenses[0]);
								top.push_back(expenses[1]);
								top.push_back(expenses[2]);

								for (int i = 2; i < expenses.size(); i++)
								{
									if (!expenses[i]->getDate()->isCurrentMonth()) continue;

									if (top[0]->getAmount() < expenses[i]->getAmount()) {
										Expense* temp1 = top[0];
										Expense* temp2;
										top[0] = expenses[i];
										temp2 = top[1];
										top[1] = temp1;
										top[2] = temp2;
										continue;
									}
									else if (top[1]->getAmount() < expenses[i]->getAmount()) {
										Expense* temp1 = top[1];
										top[1] = expenses[i];
										top[2] = temp1;
										continue;
									}
									else if (top[2]->getAmount() < expenses[i]->getAmount()) {
										top[2] = expenses[i];
									}
								}

								cout << "\nТОП-3 ЗАТРАТ ЗА МЕСЯЦ\n";

								for (Expense* current : top)
									current->PrintInfo();
								break;
							default:
								cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
								continue;
						}
						break;
					}
					break;

				case 2:
					while (true) {
						cout << "(0) Выход\n";
						cout << "(1) За неделю\n";
						cout << "(2) За месяц\n";

						cin >> selected;

						map<CategoryCodes, double> spendEach;

						spendEach[Grocery] = 0;
						spendEach[Entertainment] = 0;
						spendEach[Rent] = 0;
						spendEach[CarMaintenance] = 0;

						map<CategoryCodes, double>::iterator it = spendEach.begin();
						pair<CategoryCodes, double> highest = *spendEach.rbegin();
						int i = 1;

						system("cls");
						switch (selected) {
							case 0: return;
							case 1:
								for (Expense* current : expenses)
								{
									if (!current->getDate()->isCurrentWeek()) continue;
									spendEach[current->getCategory()] += current->getAmount();
								}

								cout << "ТОП - 3 КАТЕГОРИЙ ЗА НЕДЕЛЮ\n";
								do {
									cout << "#" << i << " Категория " << it->first << " $" << it->second << '\n';
									i++;
								} while (spendEach.value_comp()(*it++, highest));

								break;
							case 2:
								for (Expense* current : expenses)
								{
									if (!current->getDate()->isCurrentMonth()) continue;
									spendEach[current->getCategory()] += current->getAmount();
								}

								cout << "ТОП - 3 КАТЕГОРИЙ ЗА МЕСЯЦ\n";
								do {
									cout << "#" << i << " Категория " << it->first << " $" << it->second << '\n';
									i++;
								} while (spendEach.value_comp()(*it++, highest));

								break;
							default:
								cout << "ОШИБКА: НЕКОРРЕКТНЫЙ ВВОД\n";
								continue;
						}
						break; 
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