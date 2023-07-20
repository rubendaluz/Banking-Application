#include <iostream>
#include <string>
#include <vector>

class Transaction {
private:
    std::string type; // "deposit" or "withdraw"
    double amount;

public:
    Transaction(const std::string& type, double amount)
        : type(type), amount(amount) {}

    double getAmount() const {
        return amount;
    }

    std::string getType() const {
        return type;
    }
};

class Account {
private:
    std::string accountNumber;
    double balance;
    std::vector<Transaction> transactions;

public:
    Account(const std::string& accountNumber)
        : accountNumber(accountNumber), balance(0.0) {}

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction("deposit", amount));
    }

    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            transactions.push_back(Transaction("withdraw", amount));
            return true;
        }
        return false;
    }

    double getBalance() const {
        return balance;
    }

    std::string getAccountNumber() const {
        return accountNumber;
    }

    void displayTransactions() const {
        std::cout << "Account Number: " << accountNumber << std::endl;
        for (const Transaction& transaction : transactions) {
            std::cout << "Type: " << transaction.getType() << ", Amount: $" << transaction.getAmount() << std::endl;
        }
    }
};

class Customer {
private:
    std::string name;
    std::vector<Account> accounts;

public:
    Customer(const std::string& name) : name(name) {}

    void addAccount(const std::string& accountNumber) {
        accounts.push_back(Account(accountNumber));
    }

    Account* findAccount(const std::string& accountNumber) {
        for (Account& account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }

    void displayAccounts() const {
        std::cout << "Customer Name: " << name << std::endl;
        for (const Account& account : accounts) {
            std::cout << "Account Number: " << account.getAccountNumber() << ", Balance: $" << account.getBalance() << std::endl;
        }
    }
};

int main() {
    // Criando um cliente
    Customer customer("John Doe");

    // Adicionando duas contas ao cliente
    customer.addAccount("123456");
    customer.addAccount("789012");

    // Realizando transações nas contas
    Account* account1 = customer.findAccount("123456");
    if (account1) {
        account1->deposit(1000);
        account1->withdraw(500);
    }

    Account* account2 = customer.findAccount("789012");
    if (account2) {
        account2->deposit(2000);
    }

    // Exibindo as contas e transações do cliente
    customer.displayAccounts();

    std::cout << std::endl;

    if (account1) {
        account1->displayTransactions();
    }

    return 0;
}
