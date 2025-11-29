#include "Class.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

// Реализация исключений
TariffException::TariffException(const string& msg) : message(msg) {}

const char* TariffException::what() const noexcept {
    return message.c_str();
}

NegativePriceException::NegativePriceException() : TariffException("Цена не может быть отрицательной") {}

InvalidDiscountException::InvalidDiscountException() : TariffException("Скидка должна быть от 0 до 1") {}

EmptyTariffListException::EmptyTariffListException() : TariffException("Список тарифов пуст") {}

InvalidInputException::InvalidInputException() : TariffException("Неверный формат ввода. Введите число.") {}

// Реализация RegularTariff
RegularTariff::RegularTariff(double price, const string& tariffName, int min)
    : basePrice(price), name(tariffName), minutes(min) {
    if (price < 0) throw NegativePriceException();
}

double RegularTariff::calculateCost() const {
    return basePrice * minutes;
}

double RegularTariff::getBasePrice() const {
    return basePrice;
}

string RegularTariff::getName() const {
    return name;
}

string RegularTariff::getType() const {
    return "Обычный";
}

int RegularTariff::getMinutes() const {
    return minutes;
}

// Реализация PreferentialTariff
PreferentialTariff::PreferentialTariff(double price, double disc, const string& tariffName, int min)
    : basePrice(price), discount(disc), name(tariffName), minutes(min) {
    if (price < 0) throw NegativePriceException();
    if (disc < 0 || disc > 1) throw InvalidDiscountException();
}

double PreferentialTariff::calculateCost() const {
    return basePrice * minutes * (1 - discount);
}

double PreferentialTariff::getBasePrice() const {
    return basePrice;
}

string PreferentialTariff::getName() const {
    return name;
}

string PreferentialTariff::getType() const {
    return "Льготный (" + to_string((int)(discount * 100)) + "%)";
}

int PreferentialTariff::getMinutes() const {
    return minutes;
}

// Реализация ATS
ATS::ATS() {
    // Добавляем тарифы по умолчанию
    tariffs.push_back(new RegularTariff(2.0, "Стандартный", 60));
    tariffs.push_back(new PreferentialTariff(2.0, 0.25, "Пенсионный", 60));
}

void ATS::addRegularTariff(double price, const string& name, int minutes) {
    tariffs.push_back(new RegularTariff(price, name, minutes));
}

void ATS::addPreferentialTariff(double price, double discount, const string& name, int minutes) {
    tariffs.push_back(new PreferentialTariff(price, discount, name, minutes));
}

double ATS::calculateAverageCost() const {
    if (tariffs.empty()) throw EmptyTariffListException();

    double total = 0.0;
    for (const auto& tariff : tariffs) {
        total += tariff->calculateCost();
    }
    return total / tariffs.size();
}

void ATS::displayAllTariffs() const {
    if (tariffs.empty()) {
        cout << "Тарифов нет" << endl;
        return;
    }

    cout << "\n=== СПИСОК ТАРИФОВ ===" << endl;
    for (size_t i = 0; i < tariffs.size(); i++) {
        cout << i + 1 << ". " << tariffs[i]->getName()
            << " | Тип: " << tariffs[i]->getType()
            << " | Цена: " << tariffs[i]->getBasePrice() << " руб/мин"
            << " | Минуты: " << tariffs[i]->getMinutes()
            << " | Итого: " << tariffs[i]->calculateCost() << " руб" << endl;
    }
}

size_t ATS::getTariffCount() const {
    return tariffs.size();
}

double ATS::getTotalCost() const {
    double total = 0.0;
    for (const auto& tariff : tariffs) {
        total += tariff->calculateCost();
    }
    return total;
}

ATS::~ATS() {
    for (auto tariff : tariffs) {
        delete tariff;
    }
}