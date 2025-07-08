#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
  double balance;

public:
  BankAccount() { balance = 0.0; }

  void deposit(double amount) {
    if (amount <= 0) {
        
      cout << "Invalid deposit amount. Please enter a positive value." << endl;
      return;
    }
    balance += amount;
    saveTransaction("Deposit", amount);
  }

  void makePurchase(string item, double cost) {
    if (cost <= 0) {
        
      cout << "Invalid purchase amount. Please enter a positive value." << endl;
      return;
    }
    if (cost > balance) {
      cout << "Insufficient funds for " << item << ". Current balance: $"
           << balance << endl;
    } else {
        
      balance -= cost;
      saveTransaction("Purchase - " + item, cost);
      cout << "Purchase successful: " << item << " for $" << cost << endl;
    }
  }

  void displayBalance() { cout << "Current Balance: $" << balance << endl; }

  void saveTransaction(string type, double amount) {
    ofstream file("transactions.txt", ios::app);
    if (file.is_open()) {
        
        
      file << type << ": $" << amount << " | New Balance: $" << balance << endl;
      file.close();
    } else {
      cout << "Error: Unable to save transaction to file." << endl;
    }
  }
};

int main() {
  BankAccount myAccount;

  cout << "=== Bank Account Test ===" << endl;

  myAccount.deposit(100.00);
  myAccount.makePurchase("Coffee", 4.50);
  myAccount.makePurchase("Book", 25.00);
  myAccount.makePurchase("Expensive Watch", 150.00); 
  
  myAccount.deposit(-10.00);                         
  myAccount.displayBalance();

  cout << "Check transactions.txt for transaction history." << endl;

  return 0;
}
