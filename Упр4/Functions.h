#pragma once
#include <iostream>
#include <string>
#include "Class.h"

// Не используем using namespace std; в заголовочных файлах
// using namespace std;

// Функции для валидации ввода
double getValidatedDouble(const std::string& prompt);
int getValidatedInt(const std::string& prompt);

// Функции меню
void displayMenu();
void addRegularTariffMenu(ATS& ats);
void addPreferentialTariffMenu(ATS& ats);
void showStatistics(const ATS& ats);