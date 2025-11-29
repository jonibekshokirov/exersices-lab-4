#include "Functions.h"
#include <iostream>
#include <limits>
#include <string>

// Теперь можно использовать using namespace std; в .cpp файлах
using namespace std;

// Функции для валидации ввода
double getValidatedDouble(const string& prompt) {
    double value;
    cout << prompt;
    cin >> value;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw InvalidInputException();
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

int getValidatedInt(const string& prompt) {
    int value;
    cout << prompt;
    cin >> value;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw InvalidInputException();
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// Функции меню
void displayMenu() {
    cout << "\n=== МЕНЮ АТС ===" << endl;
    cout << "1. Добавить обычный тариф" << endl;
    cout << "2. Добавить льготный тариф" << endl;
    cout << "3. Показать все тарифы" << endl;
    cout << "4. Рассчитать среднюю стоимость" << endl;
    cout << "5. Показать статистику" << endl;
    cout << "6. Выход" << endl;
    cout << "Выберите действие: ";
}

void addRegularTariffMenu(ATS& ats) {
    double price;
    string name;
    int minutes;

    cout << "\n--- Добавление обычного тарифа ---" << endl;
    cout << "Введите название тарифа: ";
    cin.ignore();
    getline(cin, name);

    try {
        price = getValidatedDouble("Введите цену за минуту (руб): ");
        minutes = getValidatedInt("Введите количество минут: ");

        ats.addRegularTariff(price, name, minutes);
        cout << " Тариф '" << name << "' успешно добавлен!" << endl;
    }
    catch (const InvalidInputException& e) {
        cout << " Ошибка ввода: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cout << " Ошибка: " << e.what() << endl;
    }
}

void addPreferentialTariffMenu(ATS& ats) {
    double price, discount;
    string name;
    int minutes;

    cout << "\n--- Добавление льготного тарифа ---" << endl;
    cout << "Введите название тарифа: ";
    cin.ignore();
    getline(cin, name);

    try {
        price = getValidatedDouble("Введите цену за минуту (руб): ");
        discount = getValidatedDouble("Введите размер скидки (0.1 для 10%, 0.2 для 20% и т.д.): ");
        minutes = getValidatedInt("Введите количество минут: ");

        ats.addPreferentialTariff(price, discount, name, minutes);
        cout << " Льготный тариф '" << name << "' успешно добавлен!" << endl;
    }
    catch (const InvalidInputException& e) {
        cout << " Ошибка ввода: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cout << " Ошибка: " << e.what() << endl;
    }
}

void showStatistics(const ATS& ats) {
    cout << "\n=== СТАТИСТИКА АТС ===" << endl;
    cout << "Количество тарифов: " << ats.getTariffCount() << endl;

    try {
        double average = ats.calculateAverageCost();
        double total = ats.getTotalCost();
        cout << "Общая стоимость всех тарифов: " << total << " руб." << endl;
        cout << "Средняя стоимость тарифа: " << average << " руб." << endl;
    }
    catch (const std::exception& e) {
        cout << "Невозможно рассчитать стоимость: " << e.what() << endl;
    }
}