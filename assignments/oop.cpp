#include <iostream>
using namespace std;

// Base class
class Item {
public:
  string name;
  int quantity;

  Item(string n, int q) {
    name = n;
    quantity = q;
  }

  virtual void display() = 0; // Pure virtual function
};

// Perishable item
class Perishable : public Item {
public:
  Perishable(string n, int q) : Item(n, q) {}

  void display() override {
    cout << name << " (Perishable), Qty: " << quantity << endl;
  }
};

// Non-Perishable item
class NonPerishable : public Item {
public:
  NonPerishable(string n, int q) : Item(n, q) {}

  void display() override {
    cout << name << " (Non-Perishable), Qty: " << quantity << endl;
  }
};

int main() {

  Perishable perishableItem("Milk", 5);
  NonPerishable nonPerishableItem("Canned beans", 10);


  Item *item1 = &perishableItem;
  Item *item2 = &nonPerishableItem;

  item1->display();
  item2->display(); 

  
  return 0;
}
