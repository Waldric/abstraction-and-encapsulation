#include <iostream> 
using namespace std;
// start --
class Account {
protected:
    double balance; // Encapsulated data member

public:
    Account() : balance() {} 
    
    // Method to deposit money
    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful!" << endl;
        } else {
            cout << "Invalid input. Please input a positive number." << endl;
        }
    }

    virtual void withdraw(double amount) = 0;  // pure virtual function (abstraction)

    // Metodo para ma check ang balanse
    void checkBalance() const {
        cout << "Current Balance: P" << balance << endl;
    }

    double getBalance() const { // Encapsulation - getter method para ma access and encapsulated data member
        return balance;
    }
};

// Savings Account class
class savingsAccount : public Account {
private:
    const double minimumBalance = 1000.00;  // Encapsulated data member
public:
    savingsAccount() : Account() {} // Constructor

    void withdraw(double amount) override {  // Abstraction
        if (amount <= 0) {
            cout << "Invalid input. Please input a positive number." << endl; // mga validation
        } else if (balance - amount < minimumBalance) {
            cout << "Cannot withdraw! Minimum balance of P1000 must be maintained / Withdrawal amount should not be greater than the balance! " << endl;
        } else if (amount > balance) {
            cout << "Insufficient balance!" << endl;
        } else {
            balance -= amount;
            cout << "Withdrawal successful!" << endl;
        }
    }

    ~savingsAccount() {  // Destructor
        cout << "Cleaning savings account data..." << endl;
    }
};

// Current Account class
class currentAccount : public Account {
public:
    currentAccount() : Account() {}  // Constructor

    void withdraw(double amount) override { // Abstraction
        if (amount <= 0) {
            cout << "Invalid input. Please input a positive number." << endl;  // validation part
        } else if (amount > balance) {
            cout << "Insufficient balance!" << endl;
        } else {
            balance -= amount;
            cout << "Withdrawal successful!" << endl;
        }
    }

    ~currentAccount() {  // Destructor
        cout << "Cleaning current account data..." << endl;
    }
};

// Function for Savings Account Menu
void savingsAccountMenu(savingsAccount &Account) {
    int savingsChoice;
    double amount = 0;
    bool submenu = true;

    // Ensure initial deposit is at least 1000
    if (Account.getBalance() == 0) {
        cout << "To proceed on your Savings Account. You need to deposit a minimum of P1000 first." << endl; // setting up savings account
        do {
            cout << "Input Deposit Amount: P";
            cin >> amount;
            if (cin.fail()) {  // validation para sa iba't ibang characters (&,A,b,+, etc...)
                cin.clear();
                cin.ignore(512, '\n');
                cout << "Invalid Input! Please Try Again." << endl;
            } else if (amount < 1000) {
                cout << "Invalid Input! Enter a minimum amount of P1000." << endl;
            }
        } while (amount < 1000);
        Account.deposit(amount);
    }

    do {
        cout << "\nSub Menu " << endl;
        cout << "1 - Deposit " << endl;
        cout << "2 - Withdraw " << endl;
        cout << "3 - Check Balance " << endl;
        cout << "4 - Back " << endl;
        cout << "Select an option: ";
        cin >> savingsChoice;

        if (cin.fail() || savingsChoice < 1 || savingsChoice > 4) {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "Invalid Input! Please Try Again." << endl;
        } else {
            switch (savingsChoice) {
                case 1:
                    cout << "Input Deposit Amount: P";
                    cin >> amount;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(512, '\n');
                        cout << "Invalid Input! Please Try Again." << endl;
                    } else {
                        Account.deposit(amount);
                    }
                    break;
                case 2:
                    cout << "Enter Withdrawal Amount: P";
                    cin >> amount;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(512, '\n');
                        cout << "Invalid Input! Please Try Again." << endl;
                    } else {
                        Account.withdraw(amount);
                    }
                    break;
                case 3:
                    Account.checkBalance();
                    break;
                case 4:
                    submenu = false;  // Exit the submenu
                    break;
            }
        }
    } while (submenu);
}

// Function for Current Account Menu
void currentAccountMenu(currentAccount &Account) {
    int currentChoice;
    double amount = 0;
    bool submenu = true;

    do {
        cout << "\nSub Menu " << endl;
        cout << "1 - Deposit " << endl;
        cout << "2 - Withdraw " << endl;
        cout << "3 - Check Balance " << endl;
        cout << "4 - Back " << endl;
        cout << "Select an option: ";
        cin >> currentChoice;
           if (cin.fail() || currentChoice > 4 || currentChoice < 1) {
 					cin.clear(); cin.ignore(512, '\n');
  					cout << "== NOT AN OPTION ==" << endl;
					}

        switch (currentChoice) {
            case 1:
                cout << "Input Deposit Amount: P";
                cin >> amount;
                if (cin.fail()) {
 					cin.clear(); cin.ignore(512, '\n');
  					cout << "Invalid Input! Please Try Again" << endl;
					}
                Account.deposit(amount);
                break;
            case 2:
                cout << "Enter Withdrawal Amount: P";
                cin >> amount;
                if (cin.fail()) {
 					cin.clear(); cin.ignore(512, '\n');
  					cout << "Invalid Input! Please Try Again" << endl;
					}
                Account.withdraw(amount);
                break;
            case 3:
                Account.checkBalance();
                break;
            case 4:
                submenu = false;  
                break;
            default:
                cout << "Please Try Again: " << endl;
                break;
        }
    } while (submenu);  
}

// Main function
int main() {
    savingsAccount savings;
    currentAccount current;

    int choice;
    char exitChoice;
    bool mainMenu = true;  

    do {
        cout << "\nMain Menu" << endl;
        cout << "1 - Savings Account" << endl;
        cout << "2 - Current Account" << endl;
        cout << "3 - Exit" << endl;
        cout << "Select your option: ";
        cin >> choice;
           if (cin.fail() || choice > 3 || choice < 1) {
 					cin.clear(); cin.ignore(512, '\n');
  					cout << "== NOT AN OPTION ==" << endl;
					}

        switch (choice) {
            case 1:
                savingsAccountMenu(savings);
                break;
            case 2:
                currentAccountMenu(current);
                break;
            case 3:
                do {
                cout << "Are you sure you want to Exit? (Y/N): ";  // may chance ang user na pagisipan ang kanyang desisyon
                cin >> exitChoice;
                if (exitChoice == 'Y' || exitChoice == 'y') {
                    mainMenu = false;  
                } else if (exitChoice != 'Y' && exitChoice != 'y' && exitChoice != 'n' && exitChoice != 'N')
                    cout << "Invalid Input! Please Try again " << endl;
                } while (exitChoice != 'Y' && exitChoice != 'y' && exitChoice != 'n' && exitChoice != 'N');         
                break;
            default:
                cout << "Please try again: " << endl;
                break;
        }
    } while (mainMenu);  

    return 0;
}

// -- end
