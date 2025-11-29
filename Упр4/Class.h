#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

// ÕÂ ËÒÔÓÎ¸ÁÛÂÏ using namespace std; ‚ Á‡„ÓÎÓ‚Ó˜Ì˚ı Ù‡ÈÎ‡ı

// »— Àﬁ◊≈Õ»ﬂ
class TariffException : public std::exception {
private:
    std::string message;
public:
    TariffException(const std::string& msg);
    const char* what() const noexcept override;
};

class NegativePriceException : public TariffException {
public:
    NegativePriceException();
};

class InvalidDiscountException : public TariffException {
public:
    InvalidDiscountException();
};

class EmptyTariffListException : public TariffException {
public:
    EmptyTariffListException();
};

class InvalidInputException : public TariffException {
public:
    InvalidInputException();
};

// »Õ“≈–‘≈…— TARIFF 
class Tariff {
public:
    virtual double calculateCost() const = 0;
    virtual double getBasePrice() const = 0;
    virtual std::string getName() const = 0;
    virtual std::string getType() const = 0;
    virtual int getMinutes() const = 0;
    virtual ~Tariff() {}
};

// Œ¡€◊Õ€… “¿–»‘ 
class RegularTariff : public Tariff {
private:
    double basePrice;
    std::string name;
    int minutes;

public:
    RegularTariff(double price, const std::string& tariffName, int min);
    double calculateCost() const override;
    double getBasePrice() const override;
    std::string getName() const override;
    std::string getType() const override;
    int getMinutes() const override;
};

// À‹√Œ“Õ€… “¿–»‘ 
class PreferentialTariff : public Tariff {
private:
    double basePrice;
    double discount;
    std::string name;
    int minutes;

public:
    PreferentialTariff(double price, double disc, const std::string& tariffName, int min);
    double calculateCost() const override;
    double getBasePrice() const override;
    std::string getName() const override;
    std::string getType() const override;
    int getMinutes() const override;
};

//  À¿—— ATS
class ATS {
private:
    std::vector<Tariff*> tariffs;

public:
    ATS();
    void addRegularTariff(double price, const std::string& name, int minutes);
    void addPreferentialTariff(double price, double discount, const std::string& name, int minutes);
    double calculateAverageCost() const;
    void displayAllTariffs() const;
    std::size_t getTariffCount() const;
    double getTotalCost() const;
    ~ATS();
};