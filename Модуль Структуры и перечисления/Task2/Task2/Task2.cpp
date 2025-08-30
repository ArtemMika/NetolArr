#include <iostream>
#include <string>

struct BankAccount {
    int accountNumber;
    std::string ownerName;
    double balance;    
};

void updateBalance(BankAccount& account, double newBalance) {
    account.balance = newBalance;
}

int main() 
{
    setlocale(LC_ALL, "rus");
    BankAccount account;

    std::cout << "Введите номер счёта: ";
    std::cin >> account.accountNumber;

    std::cout << "Введите имя владельца: ";
    std::cin.ignore();
    std::getline(std::cin, account.ownerName);

    std::cout << "Введите баланс: ";
    std::cin >> account.balance;

    double newBalance;
    std::cout << "Введите новый баланс: ";
    std::cin >> newBalance;

    // Обновляем баланс счёта
    updateBalance(account, newBalance);

    // Выводим обновлённую информацию
    std::cout << "Ваш счёт: "
        << account.ownerName << ", "
        << account.accountNumber << ", "
        << account.balance << std::endl;

    return 0;
}
