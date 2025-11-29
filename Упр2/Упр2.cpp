#include <iostream>
#include <string>

using namespace std;

class BankAccount {
private:
    string owner;
    double balance;

public:
    BankAccount(const string& name, double initialBalance)
        : owner(name), balance(initialBalance) {
    }

    // Переопределение оператора  =
    BankAccount& operator=(const BankAccount& other) {
        if (this != &other) {  
            owner = other.owner;
            balance = other.balance;
            cout << "Вызван оператор присваивания" << endl;
        }
        return *this;
    }

    // Перегрузка оператора += 
    BankAccount& operator+=(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Пополнение на " << amount << endl;
        }
        return *this;
    }

    
    friend ostream& operator<<(ostream& os, const BankAccount& account) {
        os << "Владелец: " << account.owner << ", Баланс: " << account.balance;
        return os;
    }

    string getOwner() const { return owner; }
    double getBalance() const { return balance; }
};

int main() {
    setlocale(LC_ALL, "ru");

    cout << "=== ПЕРЕГРУЗКА И ПЕРЕОПРЕДЕЛЕНИЕ ОПЕРАТОРОВ ===" << endl;


    BankAccount account1("Иван", 1000.0);
    BankAccount account2("Мария", 1500.0);

    cout << "\n1. Исходные счета:" << endl;
    cout << account1 << endl;
    cout << account2 << endl;

    cout << "\n2. Перегрузка оператора +=:" << endl;
    account1 += 500.0;
    cout << "После пополнения: " << account1 << endl;

    cout << "\n3. Переопределение оператора =:" << endl;
    BankAccount account3("Петр", 0.0);
    cout << "До присваивания: " << account3 << endl;

    account3 = account1;  // Вызов переопределенного оператора =
    cout << "После присваивания: " << account3 << endl;

    // Демонстрация цепочки операций
    cout << "\n4. Цепочка операций:" << endl;
    account2 += 300.0;
    account2 += 200.0;  // Цепочка вызовов +=
    cout << "После цепочки пополнений: " << account2 << endl;

    return 0;
}