#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Item {
public:
  string name;
  int quantity;

  void saveToFile() {
      
    ofstream out("item.txt");
    
    if (out.is_open()) {
        
      out << name << "," << quantity << endl;
      out.close();
      cout << "Data saved to item.txt" << endl;
      
    } else {
      cout << "Error: Unable to open file for writing" << endl;
    }
  }

};

int main() {

  Item fruit;

  fruit.name = "Apple";
  fruit.quantity = 25;

  cout << "Item created:" << endl;
  cout << "Name: " << fruit.name << ", Quantity: " << fruit.quantity << endl;
  cout << endl;

  fruit.saveToFile();
  cout << endl;

  return 0;
}
