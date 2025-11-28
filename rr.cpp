#include <iostream>
using namespace std;
class BankAccount {
protected:
    int accountNumber;
    string accountHolderName;
private:
    double balance;   
public:
    BankAccount(int accNo, string name, double bal) {
        accountNumber = accNo;
        accountHolderName = name;
        balance = bal;
    }

    virtual void deposit(double amount) {
        balance += amount;
        cout << "Amount Deposited Successfully!\n";
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Amount Withdrawn Successfully!\n";
        } else {
            cout << "Insufficient Balance!\n";
        }
    }

    double getBalance() const {
        return balance;
    }

    virtual void displayAccountInfo() const {
        cout << "\nAccount Number: " << accountNumber
             << "\nAccount Holder: " << accountHolderName
             << "\nBalance: " << balance << endl;
    }

    virtual void calculateInterest() {
        cout << "Interest calculation not available for this account type.\n";
    }

    virtual ~BankAccount() {}
};


class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(int accNo, string name, double bal, double rate)
        : BankAccount(accNo, name, bal) {
        interestRate = rate;
    }

    void calculateInterest() override {
        double interest = getBalance() * interestRate / 100.0;
        cout << "Savings Interest: " << interest << endl;
    }
};

// =========== Derived Class: Checking Account ===========
class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(int accNo, string name, double bal, double limit)
        : BankAccount(accNo, name, bal) {
        overdraftLimit = limit;
    }

    void withdraw(double amount) override {
        if (amount <= getBalance() + overdraftLimit) {
            cout << "Amount Withdrawn Using Overdraft (If required)\n";
            BankAccount::deposit(-amount);
        } else {
            cout << "Withdrawal exceeds overdraft limit!\n";
        }
    }

    void calculateInterest() override {
        cout << "No interest for Checking Account.\n";
    }
};


class FixedDepositAccount : public BankAccount {
private:
    int term;
    double interestRate;

public:
    FixedDepositAccount(int accNo, string name, double bal, int t, double rate)
        : BankAccount(accNo, name, bal) {
        term = t;
        interestRate = rate;
    }

    void calculateInterest() override {
        double interest = (getBalance() * interestRate * term) / (12 * 100.0);
        cout << "Fixed Deposit Interest: " << interest << endl;
    }
};


int main() {
    BankAccount* account = nullptr;
    int choice;

    while (true) {
        cout << "\n==== BANK ACCOUNT MENU ====\n";
        cout << "1. Create Savings Account\n";
        cout << "2. Create Checking Account\n";
        cout << "3. Create Fixed Deposit Account\n";
        cout << "4. Deposit Money\n";
        cout << "5. Withdraw Money\n";
        cout << "6. Display Account Info\n";
        cout << "7. Calculate Interest\n";
        cout << "8. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 8) break;

        switch (choice) {
        case 1:
            account = new SavingsAccount(101, "Dharm Maradiya", 15000, 5.5);
            cout << "Savings Account Created!\n";
            break;

        case 2:
            account = new CheckingAccount(202, "Dharm Maradiya", 10000, 5000);
            cout << "Checking Account Created!\n";
            break;

        case 3:
            account = new FixedDepositAccount(303, "Dharm Maradiya", 50000, 12, 7.2);
            cout << "Fixed Deposit Account Created!\n";
            break;

        case 4: {
            double amount;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            account->deposit(amount);
            break;
        }

        case 5: {
            double amount;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            account->withdraw(amount);
            break;
        }

        case 6:
            account->displayAccountInfo();
            break;

        case 7:
            account->calculateInterest();
            break;

        default:
            cout << "Invalid Option!\n";
        }
    }

    delete account;
    return 0;
}
