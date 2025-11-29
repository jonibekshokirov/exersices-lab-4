#define NOMINMAX
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <Windows.h>
#include <limits>
#include "Functions.h"
#include "Class.h"

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ATS ats;
    int choice;

    cout << "=== СИСТЕМА УПРАВЛЕНИЯ АТС ===" << endl;

    do {
        displayMenu();
        cin >> choice;

        // Проверка ввода для самого меню
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Неверный ввод! Введите число от 1 до 6." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            addRegularTariffMenu(ats);
            break;
        case 2:
            addPreferentialTariffMenu(ats);
            break;
        case 3:
            ats.displayAllTariffs();
            break;
        case 4:
            try {
                double average = ats.calculateAverageCost();
                cout << "\nСредняя стоимость всех тарифов: " << average << " руб." << endl;
            }
            catch (const exception& e) {
                cout << " Ошибка: " << e.what() << endl;
            }
            break;
        case 5:
            showStatistics(ats);
            break;
        case 6:
            cout << "Выход из программы..." << endl;
            break;
        default:
            cout << " Неверный выбор! Попробуйте снова." << endl;
            break;
        }

    } while (choice != 6);

    return 0;
}